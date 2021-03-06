
// CanSIMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CanSIM.h"
#include "CanSIMDlg.h"
#include "afxdialogex.h"
#include <ntcore.h>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCanSIMDlg dialog



CCanSIMDlg::CCanSIMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CANSIM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCanSIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

   DDX_Control(pDX, IDC_GRABBER_CURRENT, m_grabberCurrentSlider);
   DDX_Control(pDX, IDC_GRABBER_CURENT_TEXT, m_grabberCurrentEdit);

   DDX_Control(pDX, IDC_LADDER_HEIGHT_SLIDER, m_ladderHeightSlider);
   DDX_Control(pDX, IDC_LADDER_HEIGHT_TEXT,   m_ladderHeightEdit);

}

BEGIN_MESSAGE_MAP(CCanSIMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CCanSIMDlg message handlers

BOOL CCanSIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

   m_hInstance = NT_CreateInstance();

   NT_StartClient(m_hInstance, "10.74.0.2", 1735);

   std::this_thread::sleep_for(std::chrono::seconds(2));

   m_grabberCurrentSlider.SetRange(0, 10000);
   m_ladderHeightSlider.SetRange(0, 800);

   m_grabberCurrentSlider.SetPos(1000);
   m_grabberCurrentEdit.SetWindowText(L"1.0000");

   m_ladderHeightSlider.SetPos(0);
   m_ladderHeightEdit.SetWindowText(L"0");

   return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCanSIMDlg::SetDouble(const char *pName, double value)
{
   NT_Entry hEntry = NT_GetEntry(m_hInstance, pName, strlen(pName));

   if (hEntry) {
      uint64_t lastChange = 0.0;

      NT_SetEntryDouble(hEntry, lastChange, value, true);
   }


   NT_Bool NT_GetValueDouble(const struct NT_Value* value, uint64_t* last_change,
      double* v_double);

}

void CCanSIMDlg::OnPaint()
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
HCURSOR CCanSIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCanSIMDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   CSliderCtrl *pSlider = (CSliderCtrl *)pScrollBar;
   int id = pSlider->GetDlgCtrlID();
   int pos = ((CSliderCtrl *)pScrollBar)->GetPos();

   UpdateData();

   CString strVal;
   double truePos;

   switch (id)
   {
      case IDC_GRABBER_CURRENT : 
         truePos = pos;
         truePos /= 1000.0;
         strVal.Format(L"%.4f", truePos);
         m_grabberCurrentEdit.SetWindowText(strVal);
         SetDouble("CANSim/GrabberCurrent", truePos);
         break;
      case IDC_LADDER_HEIGHT_SLIDER:
         strVal.Format(L"%d", pos);
         m_ladderHeightEdit.SetWindowText(strVal);
         SetDouble("CANSim/LadderHeight", pos);
         break;

   }
}

