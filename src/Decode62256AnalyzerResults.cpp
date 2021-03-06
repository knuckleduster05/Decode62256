#include "Decode62256AnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "Decode62256Analyzer.h"
#include "Decode62256AnalyzerSettings.h"
#include <iostream>
#include <fstream>

Decode62256AnalyzerResults::Decode62256AnalyzerResults( Decode62256Analyzer* analyzer, Decode62256AnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}

Decode62256AnalyzerResults::~Decode62256AnalyzerResults()
{
}

void Decode62256AnalyzerResults::GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base )
{
	ClearResultStrings();
	Frame frame = GetFrame( frame_index );

	char number_str[128];
	switch(frame.mData1) {
		case 'W':
			number_str[0] = 'W';
			number_str[1] = 'r';
			number_str[2] = 'i';
			number_str[3] = 't';
			number_str[4] = 'e';
			break;
		case 'R':
			number_str[0] = 'R';
			number_str[1] = 'e';
			number_str[2] = 'a';
			number_str[3] = 'd';
			break;
		case 'S':
			number_str[0] = 'S';
			number_str[1] = 't';
			number_str[2] = 'a';
			number_str[3] = 'n';
			number_str[4] = 'd';
			number_str[5] = 'b';
			number_str[6] = 'y';
			break;
		case 'X':
			number_str[0] = 'O';
			number_str[1] = 'u';
			number_str[2] = 't';
			number_str[3] = 'p';
			number_str[4] = 'u';
			number_str[5] = 't';
			number_str[6] = ' ';
			number_str[7] = 'D';
			number_str[8] = 'i';
			number_str[9] = 's';
			number_str[10] = 'a';
			number_str[11] = 'b';
			number_str[12] = 'l';
			number_str[13] = 'e';
			number_str[14] = 'd';
			break;
		default:
			number_str[0] = 'E';
			number_str[1] = 'r';
			number_str[2] = 'r';
			break;
	}
	//AnalyzerHelpers::GetNumberString( frame.mData1, DisplayBase::ASCII, 8, number_str, 128 );
	AddResultString( number_str );
}

void Decode62256AnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
	std::ofstream file_stream( file, std::ios::out );

	U64 trigger_sample = mAnalyzer->GetTriggerSample();
	U32 sample_rate = mAnalyzer->GetSampleRate();

	file_stream << "Time [s],Value" << std::endl;

	U64 num_frames = GetNumFrames();
	for( U32 i=0; i < num_frames; i++ )
	{
		Frame frame = GetFrame( i );
		
		char time_str[128];
		AnalyzerHelpers::GetTimeString( frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128 );

		char number_str[128];
		AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );

		file_stream << time_str << "," << number_str << std::endl;

		if( UpdateExportProgressAndCheckForCancel( i, num_frames ) == true )
		{
			file_stream.close();
			return;
		}
	}

	file_stream.close();
}

void Decode62256AnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
#ifdef SUPPORTS_PROTOCOL_SEARCH
	Frame frame = GetFrame( frame_index );
	ClearTabularText();

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
	AddTabularText( number_str );
#endif
}

void Decode62256AnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void Decode62256AnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}