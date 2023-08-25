// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#ifndef BACKLIGHT_PLUGINS_H
#define BACKLIGHT_PLUGINS_H

#include <windows.h>

typedef int (__stdcall *SIR_INPUTCALLBACK)(DWORD *InputData, DWORD dwLedsCount);

#pragma pack (push, 1)
typedef struct _BACKLIGHT_PLUGIN_SETTINGS
{
	DWORD dwPluginVersion;  	// ������ ������� � ����� ���������.
								// Versions and structure fields.

    // Start structure plugin version 1
	DWORD dwEventMethod;    	// Transmission method data to the main program.
								// ������ �������� ������ �������� ���������.
								// 0 - a callback function.
								// 0 - ����� ������� ��������� ������.
								// 1 - a message WM_SETPLUGINDATA.
								// 1 - ����� ��������� WM_SETPLUGINDATA.

	DWORD dwMinEventTime;    	// Minimal interval the call CallBack functions in milliseconds.
								// ����������� �������� ������ CallBack ������� � �������������.

	DWORD dwLedsCount;         	// Number of RGB LEDs (zones) supported by the device.
								// ���������� RGB LED ����������� (���) �������������� �����������.

	DWORD dwBitOfColor;        	// RGB space size in bits
								// ������ RGB ������������ � �����,
								// 8, 9, 10, 11, 12 - bits per color (��� �� ����).
								// InputData - data must be specified in bit dwBitOfColor.
								// InputData - ������ ������ ���� � �������� ��������� � dwBitOfColor.

	SIR_INPUTCALLBACK input_func; // The callback function is called by the plugin.
								  // ������� ��������� ������ ������� ���������� ��������.

	HWND hWndEvent;         	// Handle for transmit plugin data WM_SETPLUGINDATA
								// ����� ��� �������� ������ ������� ����� WM_SETPLUGINDATA

	DWORD dwMessageID;      	// message ID. WM_SETPLUGINDATA = dwMessageID
								// ������������� ���������. WM_SETPLUGINDATA = dwMessageID
								// SendMessage(hWndEvent, WM_SETPLUGINDATA, ....);
								// lParam = (LPARAM)InputData; wParam = (WPARAM)dwLedsCount;
								// InputData - array (a pointer to the buffer) with RGB data.
								// InputData - ������ (��������� �� ������) � RGB �������.
								// Order in an array of colors such a R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
								// ������� ������ � ������� ����� R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
								// Size of InputData = dwLedsCount * 3; (number of zones * 3 color).
								// ������ InputData = dwLedsCount * 3; (���������� ��� * �� 3 �����)

	wchar_t Language[100];  	// ��� ����� "English", "Deutsch", "Russian" � �.�.
								// Language name "English", "Deutsch", "Russian" and etc.

	DWORD	dwProfile;			// ����� �������
								// Profile number
	// End structure plugin version 1

} BACKLIGHT_PLUGIN_SETTINGS, *LPBACKLIGHT_PLUGIN_SETTINGS;
#pragma pack (pop)

typedef wchar_t *(__stdcall *SIR_DLL_FUNC_GETNAME)(void);
typedef wchar_t *(__stdcall *SIR_DLL_FUNC_GETVERSION)(void);
typedef wchar_t *(__stdcall *SIR_DLL_FUNC_GETDESCRIPTION)(void);
typedef int (__stdcall *SIR_DLL_FUNC_INIT)(void);
typedef int (__stdcall *SIR_DLL_FUNC_UNINIT)(void);
typedef int (__stdcall *SIR_DLL_FUNC_START)(void);
typedef int (__stdcall *SIR_DLL_FUNC_STOP)(void);
typedef int (__stdcall *SIR_DLL_FUNC_SHOWSETTINGS)(HWND);
typedef int (__stdcall *SIR_DLL_FUNC_SETBACKLIGHTSETTINGS)(LPBACKLIGHT_PLUGIN_SETTINGS settings);
typedef int (__stdcall *SIR_DLL_FUNC_SAVESETTINGS)(void);

/* �������������� ������� ������� */

extern "C" __declspec(dllexport) wchar_t * __stdcall SIR_GetName(void);
extern "C" __declspec(dllexport) wchar_t * __stdcall SIR_GetVersion(void);
extern "C" __declspec(dllexport) wchar_t * __stdcall SIR_GetDescription(void);
extern "C" __declspec(dllexport) int __stdcall SIR_Init(void);
extern "C" __declspec(dllexport) int __stdcall SIR_UnInit(void);
extern "C" __declspec(dllexport) int __stdcall SIR_Start(void);
extern "C" __declspec(dllexport) int __stdcall SIR_Stop(void);
extern "C" __declspec(dllexport) int __stdcall SIR_ShowSettings(HWND hWndParent);
extern "C" __declspec(dllexport) int __stdcall SIR_SetBacklightSettings(LPBACKLIGHT_PLUGIN_SETTINGS settings);
extern "C" __declspec(dllexport) int __stdcall SIR_SaveSettings(void);
/*
Examle:
//------------------------------------------------------------------------------
/**
 * @brief ��������� ����� ������.
 * @brief Getting name of the plugin.
 *
 * @detailed ������� �������� ��� ����������� �� ������������� �������.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� �������.
 * @return Plugin name.
 */
/*
wchar_t * __stdcall SIR_GetName(void)
{
	return L"ColorMusic";
}
//------------------------------------------------------------------------------
/**
 * @brief ��������� ������ �������.
 * @brief Getting version of the plugin.
 *
 * @detailed ������� �������� ��� ����������� �� ������������� �������.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ������ �������.
 * @return Plugin version.
 */
/*
wchar_t * __stdcall SIR_GetVersion(void)
{
	return L"2.0.3";
}
//------------------------------------------------------------------------------
/**
 * @brief ��������� �������������� ���������� � ������� (��� ������, ���� � ��.).
 * @brief Get additional information (author's name, website, etc.).
 *
 * @detailed ������� �������� ��� ����������� �� ������������� �������.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return �������������� ����������.
 * @return Additional information.
 */
/*
wchar_t * __stdcall SIR_GetDescription(void)
{
	return L"Plugin for Backlight\n\rDeveloper Maxim\n\r Web: http://www.ambibox.ru\n\rE-mail:AmbiBox@mail.ru";
}
//------------------------------------------------------------------------------
/**
 * @brief ������������� �������.
 * @brief Initialize the plugin.
 *
 * @detailed ��������� ������� ������� ��������� ���������.
 * @detailed Allows you to make the initial settings of the plugin.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_Init(void)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief ��������������� �������.
 * @brief UnInitialize the plugin.
 *
 * @detailed ������ ����� ���� ������� ������ ��������� ��������.
 * @detailed Plugin after this command plugin stops working.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_UnInit(void)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief ��������� ������.
 * @brief Runs the plugin.
 *
 * @detailed ����� ���� ������� ������� ����������� ���������� ������ � �������� ���������.
 *			 ������� �������� ������ ����� ������������� �������.
 * @detailed After this command, the plugin is allowed to transmit data to the main program.
 *			 This function works only when plugin initialization.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_Start(void)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief Stops plugin.
 * @brief ������������� ������
 *
 * @detailed ����� ���� ������� ������� ����������� ���������� ������ � �������� ���������.
			 ������� �������� ������ ����� ������������� �������.
 * @detailed After this command, the plugin must not transmit data to the main program.
			 This function works only when plugin initialization.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_Stop(void)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief ����� ���� ������� ��������� ���������� �������.
 * @brief Show settings plugin.
 *
 * @detailed ������� �������� ������ ����� ������������� �������.
 * @detailed This function works only when plugin initialization.
 *
 * @param ���� ���� AmbiBox.
 * @param HANDLE window of AmbiBox.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_ShowSettings(HWND hWndParent)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief �������� �������� �������.
 * @brief Transmit settings to a plugin.
 *
 * @detailed ������� �������� ������ ����� ������������� �������.
 * @detailed This function works only when plugin initialization.
 *
 * @param �������� ���������� � AmbiBox.
 * @param Parameters of device and AmbiBox.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_SetBacklightSettings(LPBACKLIGHT_PLUGIN_SETTINGS settings)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief ���������� ��������.
 * @brief Save settings.
 *
 * @detailed ������� �������� ������ ����� ������������� �������.
 * @detailed This function works only when plugin initialization.
 *
 * @param ��� ����������.
 * @param No params.
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
int __stdcall SIR_SaveSettings(void)
{
	int ErrorCode = 3;
	return 0; // Success, no errors
	return ErrorCode; // Error code > 0
}
//------------------------------------------------------------------------------
/**
 * @brief ������� ��������� ������.
 * @brief Callback function.
 *
 * @detailed ���������� �������� ��� �������� ������ �����������.
 *			 InputData - ������ (��������� �� ������) � RGB �������.
 *			 ������� ������ � ������� ����� R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
 *			 ������ InputData = dwLedsCount * 3; (���������� ��� * �� 3 �����).
 *			 dwLedsCount - ���������� ������ ������ ���������� ���.
 * @detailed Called by plugin for data transmission to LEDs.
 *			 InputData - array (a pointer to the buffer) with RGB data.
 *			 Order in an array of colors such a R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
 *			 Size of InputData = dwLedsCount * 3; (number of zones * 3 color).
 *			 dwLedsCount - quantity of data equal to the number of zones.
 *
 * @param ������ �������� ������, ���������� ���.
 * @param Array of colors, number of zones
 *
 * @return ��� ������.
 * @return Error code.
 */
/*
typedef int (__stdcall *SIR_INPUTCALLBACK)(DWORD *InputData, DWORD dwLedsCount);
*/


#endif
