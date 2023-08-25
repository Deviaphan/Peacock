// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "pch.h"
#include "PeacockSettingsDlg.h"
#include "resource.h"


IMPLEMENT_DYNAMIC(PeacockSettingsDlg, CDialog)

PeacockSettingsDlg::PeacockSettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SETTINGS, pParent)
	, time( nullptr )
	, changeDirection( nullptr )
	, brightness( nullptr )
{

}

PeacockSettingsDlg::~PeacockSettingsDlg()
{
}

void PeacockSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange( pDX );

	DDX_Text( pDX, IDC_TIME, *time );
	DDV_MinMaxInt( pDX, *time, 1, 600 );
	DDX_Check( pDX, IDC_ORIENTATION, *changeDirection );
	DDX_Text( pDX, IDC_BRIGHTNESS, *brightness );
	DDV_MinMaxInt(pDX, *brightness, 1, 255);
}

BEGIN_MESSAGE_MAP(PeacockSettingsDlg, CDialog)
	ON_BN_CLICKED( IDC_ORIENTATION, OnBnClickedOrientation )
	ON_EN_UPDATE( IDC_TIME, OnEnUpdateTime )
	ON_EN_UPDATE( IDC_BRIGHTNESS, OnEnUpdateTime )
END_MESSAGE_MAP()



void PeacockSettingsDlg::OnBnClickedOrientation()
{
	UpdateData();
}

void PeacockSettingsDlg::OnEnUpdateTime()
{
	UpdateData();
}
