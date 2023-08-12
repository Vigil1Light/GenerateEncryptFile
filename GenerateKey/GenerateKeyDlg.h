
// GenerateKeyDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CGenerateKeyDlg dialog
class CGenerateKeyDlg : public CDialogEx
{
// Construction
public:
	CGenerateKeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GENERATEKEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strHDDSN;
	BOOL m_checkThisMachine;
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedCheck1();
	CEdit m_editHDDSN;
	afx_msg void OnBnClickedDecrypt();
};
