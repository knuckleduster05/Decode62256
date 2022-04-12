#ifndef DECODE62256_ANALYZER_H
#define DECODE62256_ANALYZER_H

#include <Analyzer.h>
#include "Decode62256AnalyzerResults.h"
#include "Decode62256SimulationDataGenerator.h"

class Decode62256AnalyzerSettings;
class ANALYZER_EXPORT Decode62256Analyzer : public Analyzer2
{
public:
	Decode62256Analyzer();
	virtual ~Decode62256Analyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< Decode62256AnalyzerSettings > mSettings;
	std::auto_ptr< Decode62256AnalyzerResults > mResults;
	AnalyzerChannelData* mCE;
	AnalyzerChannelData* mWE;
	AnalyzerChannelData* mOE;

	Decode62256SimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
	U32 mCEA;
	U32 mWEA;
	U32 mOEA;
	U64 currentSample;
	U64 nextSample;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //DECODE62256_ANALYZER_H
