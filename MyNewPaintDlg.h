
// MyNewPaintDlg.h : header file
//

#pragma once
#include "Figure.h"
#include "MyLine.h"
#include "MyRectangle.h"
#include "MyTriangle.h"
#include "MyEllipse.h"
#include "MyCircle.h"

// CMyNewPaintDlg dialog
class CMyNewPaintDlg : public CDialogEx
{
// Construction
public:
	CMyNewPaintDlg(CWnd* pParent = nullptr);	// standard constructor
	COLORREF RefillColor, color; //RefillColor = color for fill shape, color = color we choose to paint.
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYNEWPAINT_DIALOG };
#endif
	CPoint start, end;
	bool isPressed = false, isDelMode = false, isDragMode = false, IsResize = false;
	CTypedPtrArray< CObArray, Figure*> figs, temp;
	int figType;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedCheck1();
	//enum fType { line, rectangle, triangle, ellipse, circle};
	//fType figType;
	CButton  dragMe, deleteMe, colorChooseB, saveB, loadB, exitB, brushB, resize; //CButton for each button
	enum modeOf { regular, drag, del,  brush }; // our mode 
	modeOf myMode, lastMode;
	//BOOL myCheckBtn;
	int index;
	CPoint BPoint;
	afx_msg void OnBnClickedCheck2();
	
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
};
