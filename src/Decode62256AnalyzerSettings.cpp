#include "Decode62256AnalyzerSettings.h"
#include <AnalyzerHelpers.h>


Decode62256AnalyzerSettings::Decode62256AnalyzerSettings()
:	mWriteEnableChannel( UNDEFINED_CHANNEL ),
	mOutputEnableChannel( UNDEFINED_CHANNEL ),
	mChipEnableChannel ( UNDEFINED_CHANNEL ),
	mWriteEnableActiveState ( ActiveLow ),
	mOutputEnableActiveState ( ActiveLow ),
	mChipEnableActiveState ( ActiveLow )
{
	mWriteEnableChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mWriteEnableChannelInterface->SetTitleAndTooltip( "WE", "Write Enable");
	mWriteEnableChannelInterface->SetChannel( mWriteEnableChannel );
	
	mWriteEnableActiveStateInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mWriteEnableActiveStateInterface->SetTitleAndTooltip("Active State", "Active State" );
	mWriteEnableActiveStateInterface->AddNumber(ActiveLow, "Active Low", "");
	mWriteEnableActiveStateInterface->AddNumber(ActiveHigh, "Active High", "");
	mWriteEnableActiveStateInterface->SetNumber( mWriteEnableActiveState );

	mOutputEnableChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mOutputEnableChannelInterface->SetTitleAndTooltip( "OE", "Output Enable");
	mOutputEnableChannelInterface->SetChannel( mOutputEnableChannel );
	
	mOutputEnableActiveStateInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mOutputEnableActiveStateInterface->SetTitleAndTooltip("Active State", "Active State" );
	mOutputEnableActiveStateInterface->AddNumber(ActiveLow, "Active Low", "");
	mOutputEnableActiveStateInterface->AddNumber(ActiveHigh, "Active High", "");
	mOutputEnableActiveStateInterface->SetNumber( mOutputEnableActiveState );
	
	mChipEnableChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mChipEnableChannelInterface->SetTitleAndTooltip( "CE", "Chip Enable");
	mChipEnableChannelInterface->SetChannel( mChipEnableChannel );
	
	mChipEnableActiveStateInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mChipEnableActiveStateInterface->SetTitleAndTooltip("Active State", "Active State" );
	mChipEnableActiveStateInterface->AddNumber(ActiveLow, "Active Low", "");
	mChipEnableActiveStateInterface->AddNumber(ActiveHigh, "Active High", "");
	mChipEnableActiveStateInterface->SetNumber( mChipEnableActiveState );
	
	AddInterface( mWriteEnableChannelInterface.get());
	AddInterface( mWriteEnableActiveStateInterface.get() );
	AddInterface( mOutputEnableChannelInterface.get() );
	AddInterface( mOutputEnableActiveStateInterface.get() );
	AddInterface( mChipEnableChannelInterface.get() );
	AddInterface( mChipEnableActiveStateInterface.get() );
	
	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	
	AddChannel( mWriteEnableChannel, "WE", false);
	AddChannel( mOutputEnableChannel, "OE", false);
	AddChannel( mChipEnableChannel, "CE", false);
	
}

Decode62256AnalyzerSettings::~Decode62256AnalyzerSettings()
{
}

bool Decode62256AnalyzerSettings::SetSettingsFromInterfaces()
{
	mWriteEnableChannel = mWriteEnableChannelInterface->GetChannel();
	mWriteEnableActiveState = ActiveState( U32( mWriteEnableActiveStateInterface->GetNumber() ) );
	mOutputEnableChannel = mOutputEnableChannelInterface->GetChannel();
	mOutputEnableActiveState = ActiveState( U32( mOutputEnableActiveStateInterface->GetNumber() ) );
	mChipEnableChannel = mChipEnableChannelInterface->GetChannel();
	mChipEnableActiveState = ActiveState( U32( mChipEnableActiveStateInterface->GetNumber() ) );

	ClearChannels();
	
	AddChannel( mWriteEnableChannel, "WE", true );
	AddChannel( mOutputEnableChannel, "OE", true);
	AddChannel( mChipEnableChannel, "CE", true);

	return true;
}

void Decode62256AnalyzerSettings::UpdateInterfacesFromSettings()
{
	mWriteEnableChannelInterface->SetChannel( mWriteEnableChannel );
	mWriteEnableActiveStateInterface->SetNumber( mWriteEnableActiveState );
	mOutputEnableChannelInterface->SetChannel( mOutputEnableChannel );
	mOutputEnableActiveStateInterface->SetNumber( mOutputEnableActiveState );
	mChipEnableChannelInterface->SetChannel( mChipEnableChannel );
	mChipEnableActiveStateInterface->SetNumber( mChipEnableActiveState );
}

void Decode62256AnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mWriteEnableChannel;
	text_archive >> *(U32*) mWriteEnableActiveState;
	text_archive >> mOutputEnableChannel;
	text_archive >> *(U32*) mOutputEnableActiveState;
	text_archive >> mChipEnableChannel;
	text_archive >> *(U32*) mChipEnableActiveState;

	ClearChannels();
	
	AddChannel( mWriteEnableChannel, "WE", true );
	AddChannel( mOutputEnableChannel, "OE", true);
	AddChannel( mChipEnableChannel, "CE", true);

	UpdateInterfacesFromSettings();
}

const char* Decode62256AnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mWriteEnableChannel;
	text_archive << mWriteEnableActiveState;
	text_archive << mOutputEnableChannel;
	text_archive << mOutputEnableActiveState;
	text_archive << mChipEnableChannel;
	text_archive << mChipEnableActiveState;

	return SetReturnString( text_archive.GetString() );
}
