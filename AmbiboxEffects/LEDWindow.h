// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#include "SIR_Plugins.h"
#include "PluginSettings.h"
#include "LED.h"
#include <vector>

// LEDWindow

class LEDWindow : public CWnd
{
	DECLARE_DYNAMIC(LEDWindow)

public:
	LEDWindow();
	virtual ~LEDWindow();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg UINT OnPowerBroadcast( UINT nPowerEvent, LPARAM nEventData );
	afx_msg void OnTimer( UINT_PTR nIDEvent );

public:
	void Load( BACKLIGHT_PLUGIN_SETTINGS & bs );
	void Save();

	void StartAnimation();
	void StopAnimation();

	void EditSettings();

private:
	BACKLIGHT_PLUGIN_SETTINGS _backlightSettings;
	PluginSettings _pluginSettings;

	std::vector<LED> _leds;
	std::vector<float> _ledsHue;

	UINT_PTR _timer;
	UINT _waitingTime;

};

void CreateLedWindow();
void DestroyLedWindow();
LEDWindow* GetLedWindow();

