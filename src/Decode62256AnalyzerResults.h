#ifndef DECODE62256_ANALYZER_RESULTS
#define DECODE62256_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class Decode62256Analyzer;
class Decode62256AnalyzerSettings;

class Decode62256AnalyzerResults : public AnalyzerResults
{
public:
	Decode62256AnalyzerResults( Decode62256Analyzer* analyzer, Decode62256AnalyzerSettings* settings );
	virtual ~Decode62256AnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	Decode62256AnalyzerSettings* mSettings;
	Decode62256Analyzer* mAnalyzer;
};

#endif //DECODE62256_ANALYZER_RESULTS
