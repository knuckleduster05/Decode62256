#ifndef DECODE62256_ANALYZER_SETTINGS
#define DECODE62256_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

enum ActiveState { ActiveHigh, ActiveLow };

class Decode62256AnalyzerSettings : public AnalyzerSettings
{
public:
	Decode62256AnalyzerSettings();
	virtual ~Decode62256AnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mWriteEnableChannel;
	ActiveState mWriteEnableActiveState;
	Channel mOutputEnableChannel;
	ActiveState mOutputEnableActiveState;
	Channel mChipEnableChannel;
	ActiveState mChipEnableActiveState;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mWriteEnableChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mWriteEnableActiveStateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mOutputEnableChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mOutputEnableActiveStateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mChipEnableChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mChipEnableActiveStateInterface;
};

#endif //DECODE62256_ANALYZER_SETTINGS
