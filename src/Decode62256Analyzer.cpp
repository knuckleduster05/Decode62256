#include "Decode62256Analyzer.h"
#include "Decode62256AnalyzerSettings.h"
#include <AnalyzerChannelData.h>

Decode62256Analyzer::Decode62256Analyzer()
:	Analyzer2(),  
	mSettings( new Decode62256AnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
	//UseFrameV2();
}

Decode62256Analyzer::~Decode62256Analyzer()
{
	KillThread();
}

void Decode62256Analyzer::SetupResults()
{
	mResults.reset( new Decode62256AnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mChipEnableChannel );
}

void Decode62256Analyzer::WorkerThread()
{
	//
	mSampleRateHz = GetSampleRate();
	
	mWE = GetAnalyzerChannelData( mSettings->mWriteEnableChannel );
	mOE = GetAnalyzerChannelData( mSettings->mOutputEnableChannel );
	mCE = GetAnalyzerChannelData( mSettings->mChipEnableChannel );
	
	if(mSettings->mWriteEnableActiveState == ActiveLow ) {
		mWEA = BIT_LOW;
	} else { //WE Active High
		mWEA = BIT_HIGH;
	}
	
	if(mSettings->mOutputEnableActiveState == ActiveLow ) {
		mOEA = BIT_LOW;
	} else { //OE Active High
		mOEA = BIT_HIGH;
	}
	
	if(mSettings->mChipEnableActiveState == ActiveLow ) {
		mCEA = BIT_LOW;
	} else { //CE Active High
		mCEA = BIT_HIGH;
	}
	
	if(mCE->GetBitState() != mCEA) {
		mCE->AdvanceToNextEdge();
	}
	
	currentSample = mCE->GetSampleNumber();
	
	for( ; ; ) {
		//FrameV2 = frame_v2;
		Frame frame;
		frame.mFlags = 0;
		
		if(mCE->GetBitState() == mCEA) { //CE is active, not in standby
			if(mWE->GetBitState() == mWEA) {
				frame.mData1 = 'W';
			} else {
				//Write Enable is not active
				if(mOE->GetBitState() == mOEA) {
					frame.mData1 = 'R';
				} else {
					frame.mData1 = 'X';
				}
			}
		} else { //Standby mode
			frame.mData1 = 'S';
		}
		
		//frame.mData1 = 'F';
		frame.mStartingSampleInclusive = currentSample;
		
		//get next sample or end of activity
		
		nextSample = mWE->GetSampleOfNextEdge()-1;
		if((mOE->GetSampleOfNextEdge()-1) < nextSample)
			nextSample = mOE->GetSampleOfNextEdge()-1;
		//if((mCE->GetSampleOfNextEdge()-1) < nextSample)
		//	nextSample = mCE->GetSampleOfNextEdge()-1;
		
		if(mCE->WouldAdvancingToAbsPositionCauseTransition(nextSample)) {
			//if next edge is after CE is disabled
			mCE->AdvanceToNextEdge();
			nextSample = mCE->GetSampleNumber();
		}
		
		frame.mEndingSampleInclusive = nextSample;
		
		/*
		frame.mEndingSampleInclusive = mCE->GetSampleOfNextEdge()-1;
		
		mCE->AdvanceToNextEdge();
		mOE->AdvanceToAbsPosition(mCE->GetSampleNumber());
		mWE->AdvanceToAbsPosition(mCE->GetSampleNumber());
		*/
		
		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
		
		//advance channels to next sample start
		
		if(mCE->GetBitState() != mCEA) {
			mCE->AdvanceToNextEdge();
			nextSample = mCE->GetSampleNumber();
		}
		
		currentSample = nextSample+1;
		mWE->AdvanceToAbsPosition(currentSample);
		mOE->AdvanceToAbsPosition(currentSample);
		mCE->AdvanceToAbsPosition(currentSample);
		
	}
}

bool Decode62256Analyzer::NeedsRerun()
{
	return false;
}

U32 Decode62256Analyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	//if( mSimulationInitilized == false )
	//{
		//mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		//mSimulationInitilized = true;
	//}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 Decode62256Analyzer::GetMinimumSampleRateHz()
{
	return 4;
}

const char* Decode62256Analyzer::GetAnalyzerName() const
{
	return "62256 Decoder";
}

const char* GetAnalyzerName()
{
	return "62256 Decoder";
}

Analyzer* CreateAnalyzer()
{
	return new Decode62256Analyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}