// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "pch.h"
#include "LEDWindow.h"
#include "PeacockSettingsDlg.h"

float CorrectValue( float v );
LED hsv2rgb( float h, float s, float v );

// LEDWindow
LEDWindow* g_led_wnd = nullptr;

enum
{
	TIMER_ID = 1234
};

void CreateLedWindow()
{
	if( !g_led_wnd )
	{
		g_led_wnd = new LEDWindow;

		DWORD exStyle = 0;
		DWORD style = 0;
		LPCTSTR wcn = AfxRegisterWndClass( 0 );

		g_led_wnd->CreateEx( exStyle, wcn, L"LED", style, 0, 0, 0, 0, HWND_MESSAGE, 0 );

		g_led_wnd->ShowWindow( SW_HIDE );
		g_led_wnd->UpdateWindow();
	}
}

void DestroyLedWindow()
{
	if( g_led_wnd )
	{
		g_led_wnd->DestroyWindow();
		delete g_led_wnd;
		g_led_wnd = nullptr;
	}
}

LEDWindow* GetLedWindow()
{
	return g_led_wnd;
}


IMPLEMENT_DYNAMIC( LEDWindow, CWnd )

LEDWindow::LEDWindow()
	: _backlightSettings{}
	, _timer( 0 )
	, _waitingTime( 0 )
{

}

LEDWindow::~LEDWindow()
{
}

void LEDWindow::StartAnimation()
{
	if( _backlightSettings.dwLedsCount == 0 )
	{
		AfxMessageBox( L"Не задано количество светодиодов", MB_OK | MB_TOPMOST | MB_ICONERROR );
		return;
	}

	_leds.resize( _backlightSettings.dwLedsCount );
	_ledsHue.resize( _leds.size() );

	const float hueStep = 360.0f / (float)_ledsHue.size();

	for( size_t i = 0; i < _ledsHue.size(); ++i )
	{
		_ledsHue[i] = static_cast<float>( i ) * hueStep;
	}

	// частота обновления ленты не более 25 раз в секунду
	_waitingTime = (std::max)(40u, (UINT)_backlightSettings.dwMinEventTime);
	_timer = SetTimer( TIMER_ID, _waitingTime, nullptr );
}

void LEDWindow::StopAnimation()
{
	if( _timer )
	{
		KillTimer( _timer );
		_timer = 0;
	}
}

void LEDWindow::Save()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	AfxGetApp()->WriteProfileInt( L"", L"time", _pluginSettings.rotateTime );
	AfxGetApp()->WriteProfileInt( L"", L"direction", _pluginSettings.changeDirection );
	AfxGetApp()->WriteProfileInt( L"", L"brightness", _pluginSettings.brightness );
}

void LEDWindow::Load( BACKLIGHT_PLUGIN_SETTINGS& bs )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	_pluginSettings.rotateTime = (int) AfxGetApp()->GetProfileInt( L"", L"time", 10 );
	_pluginSettings.changeDirection = (int)AfxGetApp()->GetProfileInt( L"", L"direction", 0 );
	_pluginSettings.brightness = (BOOL)AfxGetApp()->GetProfileInt( L"", L"brightness", 255 );

	memcpy( &_backlightSettings, &bs, sizeof( _backlightSettings ) );

	if( _backlightSettings.dwEventMethod == 0 )
	{
		if( _backlightSettings.input_func == nullptr )
		{
			;// AfxMessageBox( L"No callback" );
		}
	}
	else
	{
		if( _backlightSettings.hWndEvent == nullptr )
		{
			;// AfxMessageBox( L"No WINDOW handle" );
		}
	}
}

void LEDWindow::EditSettings()
{
	{
		AFX_MANAGE_STATE( AfxGetStaticModuleState() );

		PeacockSettingsDlg dlg;

		const int oldTime = _pluginSettings.rotateTime;
		const int oldBrightness = _pluginSettings.brightness;
		const BOOL oldDirection = _pluginSettings.changeDirection;

		dlg.time = &_pluginSettings.rotateTime;
		dlg.changeDirection = &_pluginSettings.changeDirection;
		dlg.brightness = &_pluginSettings.brightness;

		if( dlg.DoModal() != IDOK )
		{
			_pluginSettings.rotateTime = oldTime;
			_pluginSettings.changeDirection = oldDirection;
			_pluginSettings.brightness = oldBrightness;
		}
	}

	Save();
}

BEGIN_MESSAGE_MAP( LEDWindow, CWnd )
	ON_WM_POWERBROADCAST()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// LEDWindow message handlers


void LEDWindow::OnTimer( UINT_PTR nIDEvent )
{
	if( nIDEvent == TIMER_ID )
	{
		const float offset = (360.0f / (float)_pluginSettings.rotateTime) / (1000.0f / (float)_waitingTime) * (_pluginSettings.changeDirection ? -1.0f : 1.0f);
		
		const float b = (float)_pluginSettings.brightness / 255.0f;

		const size_t numLeds = _ledsHue.size();
		for( size_t i = 0; i < numLeds; ++i )
		{
			_ledsHue[i] = CorrectValue( _ledsHue[i] + offset );
			_leds[i] = hsv2rgb( _ledsHue[i], 1.0f, b );
		}

		if( _backlightSettings.dwEventMethod == 0 )
		{
			if( _backlightSettings.input_func )
			{
				_backlightSettings.input_func( (DWORD*)_leds.data(), ((DWORD)_leds.size()) * 3 );
			}
		}
		else
		{
			::SendMessage(
				_backlightSettings.hWndEvent,
				_backlightSettings.dwMessageID,
				(WPARAM)(_leds.size()) * 3,
				(LPARAM)(_leds.data())
			);
		}
	}

	CWnd::OnTimer( nIDEvent );
}



UINT LEDWindow::OnPowerBroadcast( UINT nPowerEvent, LPARAM nEventData )
{
	/*
	 wParam

PBT_APMPOWERSTATUSCHANGE
10 (0xA)

	Power status has changed.

PBT_APMRESUMEAUTOMATIC
18 (0x12)

	Operation is resuming automatically from a low-power state. This message is sent every time the system resumes.

PBT_APMRESUMESUSPEND
7 (0x7)

	Operation is resuming from a low-power state. This message is sent after PBT_APMRESUMEAUTOMATIC if the resume is triggered by user input, such as pressing a key.

PBT_APMSUSPEND
4 (0x4)

	System is suspending operation.

PBT_POWERSETTINGCHANGE
32787 (0x8013)

	A power setting change event has been received.
	 */
	return CWnd::OnPowerBroadcast( nPowerEvent, nEventData );
}


LED hsv2rgb( float h, float s, float v )
{
	LED out;

	if( s <= 0.0f )
	{
		out.rgb[0] = out.rgb[1] = out.rgb[2] = static_cast<DWORD>(v * 255.0f);
		return out;
	}

	float hh = h;
	if( hh >= 360.0f )
		hh -= 360.0f;

	hh /= 60.0f;

	const int i = static_cast<int>(hh);

	const float ff = hh - i;

	const float p = v * (1.0f - s);
	const float q = v * (1.0f - (s * ff));
	const float t = v * (1.0f - (s * (1.0f - ff)));

	switch( i )
	{
		case 0:
			out.rgb[0] = static_cast<DWORD>(v * 255.0f);
			out.rgb[1] = static_cast<DWORD>(t * 255.0);
			out.rgb[2] = static_cast<DWORD>(p * 255.0f);
			break;
		case 1:
			out.rgb[0] = static_cast<DWORD>(q * 255.0f);
			out.rgb[1] = static_cast<DWORD>(v * 255.0f);
			out.rgb[2] = static_cast<DWORD>(p * 255.0f);
			break;
		case 2:
			out.rgb[0] = static_cast<DWORD>(p * 255.0f);
			out.rgb[1] = static_cast<DWORD>(v * 255.0f);
			out.rgb[2] = static_cast<DWORD>(t * 255.0f);
			break;

		case 3:
			out.rgb[0] = static_cast<DWORD>(p * 255.0f);
			out.rgb[1] = static_cast<DWORD>(q * 255.0f);
			out.rgb[2] = static_cast<DWORD>(v * 255.0f);
			break;
		case 4:
			out.rgb[0] = static_cast<DWORD>(t * 255.0f);
			out.rgb[1] = static_cast<DWORD>(p * 255.0f);
			out.rgb[2] = static_cast<DWORD>(v * 255.0f);
			break;
		case 5:
		default:
			out.rgb[0] = static_cast<DWORD>(v * 255.0f);
			out.rgb[1] = static_cast<DWORD>(p * 255.0f);
			out.rgb[2] = static_cast<DWORD>(q * 255.0f);
			break;
	}

	return out;
}

float CorrectValue( float v )
{
	if( v >= 360.0f )
	{
		while( v >= 360.0f )
			v -= 360.0f;
	}
	else if( v < 0.0f )
	{
		while( v < 0.0f )
			v += 360.0f;
	}

	return v;
}

