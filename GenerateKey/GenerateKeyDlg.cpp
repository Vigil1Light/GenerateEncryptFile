
// GenerateKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GenerateKey.h"
#include "GenerateKeyDlg.h"
#include "afxdialogex.h"
#include <wincrypt.h>
#include <iostream>
#include <sys/stat.h>

extern unsigned int crc32b(unsigned char *message);
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGenerateKeyDlg dialog




CGenerateKeyDlg::CGenerateKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGenerateKeyDlg::IDD, pParent)
	, m_strHDDSN(_T(""))
	, m_checkThisMachine(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenerateKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HDDSN, m_strHDDSN);
	DDX_Control(pDX, IDC_HDDSN, m_editHDDSN);
}

BEGIN_MESSAGE_MAP(CGenerateKeyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GENERATE, &CGenerateKeyDlg::OnBnClickedGenerate)
	ON_BN_CLICKED(IDC_DECRYPT, &CGenerateKeyDlg::OnBnClickedDecrypt)
END_MESSAGE_MAP()


// CGenerateKeyDlg message handlers

BOOL CGenerateKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGenerateKeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGenerateKeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGenerateKeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


extern bool MyEncryptString(
	CString strHDDSN, 
	LPTSTR pszDestinationFile, 
	LPTSTR pszPassword);
extern bool MyDecryptString(
	LPTSTR pszSourceFile, 
	LPTSTR strDecrypted, 
	LPTSTR pszPassword);

//  If exist file, delete. 
inline bool exists_file(const std::string& name) 
{
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}



void CGenerateKeyDlg::OnBnClickedGenerate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString str;
	str = m_strHDDSN;
	if(str.IsEmpty())
	{
		AfxMessageBox("Please input CRC32");
		return;
	}


	char pszDestinationFile[MAX_PATH] = { 0 };
	sprintf_s(pszDestinationFile, "%s", "config.lic");
	if(exists_file(pszDestinationFile))
	{
		DeleteFile(pszDestinationFile);
	}
	if(MyEncryptString(str, pszDestinationFile,	"!@#$hGGsUzMEoyMXj4Pq1eclEciopPHUq0qd%^&*"))
	{
		AfxMessageBox("\"config.lic\" file was made successfully.");
	}
}



void CGenerateKeyDlg::OnBnClickedDecrypt()
{
	// TODO: Add your control notification handler code here
	char pszSourceFile[MAX_PATH] = { 0 };
	sprintf_s(pszSourceFile, "%s", "config.lic");
	if(!exists_file(pszSourceFile))
	{
		AfxMessageBox("License file does not exist.");
		return;
	}

	char pszDecrypted[MAX_PATH] = { 0 };
	MyDecryptString(pszSourceFile, pszDecrypted, "!@#$hGGsUzMEoyMXj4Pq1eclEciopPHUq0qd%^&*");
	AfxMessageBox(pszDecrypted);
}

// ----------------------------- crc32b --------------------------------

/* This is the basic CRC-32 calculation with some optimization but no
table lookup. The the byte reversal is avoided by shifting the crc reg
right instead of left and by using a reversed 32-bit word to represent
the polynomial.
   When compiled to Cyclops with GCC, this function executes in 8 + 72n
instructions, where n is the number of bytes in the input message. It
should be doable in 4 + 61n instructions.
   If the inner loop is strung out (approx. 5*8 = 40 instructions),
it would take about 6 + 46n instructions. */

unsigned int crc32b(unsigned char *message) 
{
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (message[i] != 0) {
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}
