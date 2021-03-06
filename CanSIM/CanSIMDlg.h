
// CanSIMDlg.h : header file
//

#pragma once
#undef min
#undef max

#include "ntcore.h"

// CCanSIMDlg dialog
class CCanSIMDlg : public CDialogEx
{
// Construction
public:
	CCanSIMDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CANSIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   void SetDouble(const char *pName, double value);

// Implementation
protected:
	HICON m_hIcon;
   CSliderCtrl m_grabberCurrentSlider, m_ladderHeightSlider;
   CEdit       m_grabberCurrentEdit, m_ladderHeightEdit;
   NT_Inst     m_hInstance;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
