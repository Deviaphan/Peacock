// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once


class PeacockSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(PeacockSettingsDlg)

public:
	PeacockSettingsDlg(CWnd* pParent = nullptr);
	virtual ~PeacockSettingsDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOrientation();
	afx_msg void OnEnUpdateTime();

public:
	int * time;
	BOOL * changeDirection;
	int * brightness;
};
