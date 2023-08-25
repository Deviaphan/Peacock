// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "pch.h"
#include "SIR_Plugins.h"
#include "LEDWindow.h"

extern "C"
{
	//---------------------------------------------------------------------------------------------------------------------------
	__declspec(dllexport) wchar_t* __stdcall SIR_GetName( void )
	{
		static wchar_t name[] = L"Peacock";
		return name;
	}

	__declspec(dllexport) wchar_t* __stdcall SIR_GetVersion( void )
	{
		static wchar_t version[] = L"2.0.0";
		return version;
	}

	__declspec(dllexport) wchar_t* __stdcall SIR_GetDescription( void )
	{
		static wchar_t description[] = L"Plugin for Backlight\n\rby maaGames\n\rhttps://vk.com/maagames";
		return description;
	}

	__declspec(dllexport) int __stdcall SIR_Init( void )
	{
		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}

	__declspec(dllexport) int __stdcall SIR_UnInit( void )
	{
		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}

	__declspec(dllexport) int __stdcall SIR_Start( void )
	{
		if( auto wnd = GetLedWindow() )
			wnd->StartAnimation();

		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}

	__declspec(dllexport) int __stdcall SIR_Stop( void )
	{
		if( auto wnd = GetLedWindow() )
			wnd->StopAnimation();

		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}

	__declspec(dllexport) int __stdcall SIR_SetBacklightSettings( LPBACKLIGHT_PLUGIN_SETTINGS settings )
	{
		if( auto wnd = GetLedWindow() )
			wnd->Load( *settings );

		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}

	__declspec(dllexport) int __stdcall SIR_ShowSettings( HWND hWndParent )
	{
		if( auto wnd = GetLedWindow() )
			wnd->EditSettings();

		return 0;
	}

	__declspec(dllexport) int __stdcall SIR_SaveSettings( void )
	{
		return 0; // Success, no errors
		//return ErrorCode; // Error code > 0
	}
}

