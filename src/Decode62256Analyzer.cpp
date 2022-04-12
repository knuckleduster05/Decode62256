#include "Decode62256Analyzer.h"
#include "Decode62256AnalyzerSettings.h"
#include <AnalyzerChannelData.h>

Decode62256Analyzer::Decode62256Analyzer()
:	Analyzer2(),  
	mSettings( new Decode62256AnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
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
/*
	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW )
		mSerial->AdvanceToNextEdge();

	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;
	U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz ) / double( mSettings->mBitRate ) );

	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1 << 7;
		
		mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		U64 starting_sample = mSerial->GetSampleNumber();

		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{
			//let's put a dot exactly where we sample this bit:
			mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

			if( mSerial->GetBitState() == BIT_HIGH )
				data |= mask;

			mSerial->Advance( samples_per_bit );

			mask = mask >> 1;
		}


		//we have a byte to save. 
		Frame frame;
		frame.mData1 = data;
		frame.mFlags = 0;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
	*/
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