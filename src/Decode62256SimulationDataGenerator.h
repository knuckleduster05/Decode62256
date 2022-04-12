#ifndef DECODE62256_SIMULATION_DATA_GENERATOR
#define DECODE62256_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class Decode62256AnalyzerSettings;

class Decode62256SimulationDataGenerator
{
public:
	Decode62256SimulationDataGenerator();
	~Decode62256SimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, Decode62256AnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	Decode62256AnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //DECODE62256_SIMULATION_DATA_GENERATOR