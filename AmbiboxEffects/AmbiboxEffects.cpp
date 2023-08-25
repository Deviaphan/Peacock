// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "pch.h"
#include "framework.h"
#include "AmbiboxEffects.h"

#include "LEDWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CAmbiboxEffectsApp

BEGIN_MESSAGE_MAP(CAmbiboxEffectsApp, CWinApp)
END_MESSAGE_MAP()


// CAmbiboxEffectsApp construction

CAmbiboxEffectsApp::CAmbiboxEffectsApp()
	:pShellManager( nullptr )
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAmbiboxEffectsApp object

CAmbiboxEffectsApp theApp;


// CAmbiboxEffectsApp initialization

BOOL CAmbiboxEffectsApp::InitInstance()
{
	// InitCommonControlsEx() требуютс€ дл€ Windows XP, если манифест
	// приложени€ использует ComCtl32.dll версии 6 или более поздней версии дл€ включени€
	// стилей отображени€.  ¬ противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwSize = sizeof( INITCOMMONCONTROLSEX );
	// ¬ыберите этот параметр дл€ включени€ всех общих классов управлени€, которые необходимо использовать
	// в вашем приложении.
	initCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &initCtrls );

	CWinApp::InitInstance();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	 pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerWindows ) );


	AfxEnableControlContainer();

	SetRegistryKey( _T( "maaGames" ) );

	CreateLedWindow();

	return TRUE;
}


int CAmbiboxEffectsApp::ExitInstance()
{
	DestroyLedWindow();

	delete pShellManager;

	return CWinApp::ExitInstance();
}
