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
	DWORD dwPluginVersion;  	// Версия плагина и полей структуры.
								// Versions and structure fields.

    // Start structure plugin version 1
	DWORD dwEventMethod;    	// Transmission method data to the main program.
								// Способ передачи данных основной программе.
								// 0 - a callback function.
								// 0 - через функцию обратного вызова.
								// 1 - a message WM_SETPLUGINDATA.
								// 1 - через сообщение WM_SETPLUGINDATA.

	DWORD dwMinEventTime;    	// Minimal interval the call CallBack functions in milliseconds.
								// Минимальный интервал вызова CallBack функции в миллисекундах.

	DWORD dwLedsCount;         	// Number of RGB LEDs (zones) supported by the device.
								// Количество RGB LED светодиодов (зон) поддерживаемых устройством.

	DWORD dwBitOfColor;        	// RGB space size in bits
								// Размер RGB пространства в битах,
								// 8, 9, 10, 11, 12 - bits per color (бит на цвет).
								// InputData - data must be specified in bit dwBitOfColor.
								// InputData - данные должны быть в битности указанной в dwBitOfColor.

	SIR_INPUTCALLBACK input_func; // The callback function is called by the plugin.
								  // Функция обратного вызова которая вызывается плагином.

	HWND hWndEvent;         	// Handle for transmit plugin data WM_SETPLUGINDATA
								// Хэндл для передачи данных плагина через WM_SETPLUGINDATA

	DWORD dwMessageID;      	// message ID. WM_SETPLUGINDATA = dwMessageID
								// идентификатор сообщения. WM_SETPLUGINDATA = dwMessageID
								// SendMessage(hWndEvent, WM_SETPLUGINDATA, ....);
								// lParam = (LPARAM)InputData; wParam = (WPARAM)dwLedsCount;
								// InputData - array (a pointer to the buffer) with RGB data.
								// InputData - массив (указатель на буффер) с RGB данными.
								// Order in an array of colors such a R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
								// Порядок цветов в массиве такой R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
								// Size of InputData = dwLedsCount * 3; (number of zones * 3 color).
								// Размер InputData = dwLedsCount * 3; (количество зон * на 3 цвета)

	wchar_t Language[100];  	// Имя языка "English", "Deutsch", "Russian" и т.д.
								// Language name "English", "Deutsch", "Russian" and etc.

	DWORD	dwProfile;			// Номер профиля
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

/* Экспортируемые функции плагина */

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
 * @brief Получение имени пагина.
 * @brief Getting name of the plugin.
 *
 * @detailed Функция работает вне зависимости от инициализации плагина.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Имя плагина.
 * @return Plugin name.
 */
/*
wchar_t * __stdcall SIR_GetName(void)
{
	return L"ColorMusic";
}
//------------------------------------------------------------------------------
/**
 * @brief Получение версии плагина.
 * @brief Getting version of the plugin.
 *
 * @detailed Функция работает вне зависимости от инициализации плагина.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Версия плагина.
 * @return Plugin version.
 */
/*
wchar_t * __stdcall SIR_GetVersion(void)
{
	return L"2.0.3";
}
//------------------------------------------------------------------------------
/**
 * @brief Получение дополнительной информации о плагине (имя автора, сайт и др.).
 * @brief Get additional information (author's name, website, etc.).
 *
 * @detailed Функция работает вне зависимости от инициализации плагина.
 * @detailed The function works regardless of initialization plugin.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Дополнительная информация.
 * @return Additional information.
 */
/*
wchar_t * __stdcall SIR_GetDescription(void)
{
	return L"Plugin for Backlight\n\rDeveloper Maxim\n\r Web: http://www.ambibox.ru\n\rE-mail:AmbiBox@mail.ru";
}
//------------------------------------------------------------------------------
/**
 * @brief Инициализация плагина.
 * @brief Initialize the plugin.
 *
 * @detailed Позволяет сделать плагину начальные настройки.
 * @detailed Allows you to make the initial settings of the plugin.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Код ошибки.
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
 * @brief Деинициализация плагина.
 * @brief UnInitialize the plugin.
 *
 * @detailed Плагин после этой команды плагин перестает работать.
 * @detailed Plugin after this command plugin stops working.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Код ошибки.
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
 * @brief Запускает плагин.
 * @brief Runs the plugin.
 *
 * @detailed После этой команды плагину разрешается передавать данные в основную программу.
 *			 Функция работает только после инициализации плагина.
 * @detailed After this command, the plugin is allowed to transmit data to the main program.
 *			 This function works only when plugin initialization.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Код ошибки.
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
 * @brief Останавливает плагин
 *
 * @detailed После этой команды плагину запрещается передавать данные в основную программу.
			 Функция работает только после инициализации плагина.
 * @detailed After this command, the plugin must not transmit data to the main program.
			 This function works only when plugin initialization.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Код ошибки.
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
 * @brief Вызов окна диалога настройки параметров плагина.
 * @brief Show settings plugin.
 *
 * @detailed Функция работает только после инициализации плагина.
 * @detailed This function works only when plugin initialization.
 *
 * @param Хэнл окна AmbiBox.
 * @param HANDLE window of AmbiBox.
 *
 * @return Код ошибки.
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
 * @brief Передача настроек плагину.
 * @brief Transmit settings to a plugin.
 *
 * @detailed Функция работает только после инициализации плагина.
 * @detailed This function works only when plugin initialization.
 *
 * @param Парметры устройства и AmbiBox.
 * @param Parameters of device and AmbiBox.
 *
 * @return Код ошибки.
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
 * @brief Сохранение настроек.
 * @brief Save settings.
 *
 * @detailed Функция работает только после инициализации плагина.
 * @detailed This function works only when plugin initialization.
 *
 * @param Нет параметров.
 * @param No params.
 *
 * @return Код ошибки.
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
 * @brief Функция обратного вызова.
 * @brief Callback function.
 *
 * @detailed Вызывается плагином для передачи данных светодиодам.
 *			 InputData - массив (указатель на буффер) с RGB данными.
 *			 Порядок цветов в массиве такой R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
 *			 Размер InputData = dwLedsCount * 3; (количество зон * на 3 цвета).
 *			 dwLedsCount - количество данных равное количеству зон.
 * @detailed Called by plugin for data transmission to LEDs.
 *			 InputData - array (a pointer to the buffer) with RGB data.
 *			 Order in an array of colors such a R0, G0, B0, R1, G1, B1, ...., Rn, Gn, Bn.
 *			 Size of InputData = dwLedsCount * 3; (number of zones * 3 color).
 *			 dwLedsCount - quantity of data equal to the number of zones.
 *
 * @param Массив цветовых данных, количество зон.
 * @param Array of colors, number of zones
 *
 * @return Код ошибки.
 * @return Error code.
 */
/*
typedef int (__stdcall *SIR_INPUTCALLBACK)(DWORD *InputData, DWORD dwLedsCount);
*/


#endif
