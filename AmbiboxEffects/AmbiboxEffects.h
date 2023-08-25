// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAmbiboxEffectsApp
// See AmbiboxEffects.cpp for the implementation of this class
//

class CAmbiboxEffectsApp : public CWinApp
{
public:
	CAmbiboxEffectsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

private:
	CShellManager * pShellManager;
};
