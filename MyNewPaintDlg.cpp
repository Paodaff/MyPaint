
// MyNewPaintDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyNewPaint.h"
#include "MyNewPaintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyNewPaintDlg dialog



CMyNewPaintDlg::CMyNewPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYNEWPAINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyNewPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, dragMe);
	DDX_Control(pDX, IDC_CHECK2, brushB);
	DDX_Control(pDX, IDC_CHECK3, deleteMe);
	
	DDX_Control(pDX, IDC_CHECK4, resize);
	DDX_Control(pDX, IDC_BUTTON3, colorChooseB);
	DDX_Control(pDX, IDC_BUTTONSave, saveB);
	DDX_Control(pDX, IDC_BUTTONLoad, loadB);
}

BEGIN_MESSAGE_MAP(CMyNewPaintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CMyNewPaintDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMyNewPaintDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTONLoad, &CMyNewPaintDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSave, &CMyNewPaintDlg::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_RADIO3, &CMyNewPaintDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyNewPaintDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO4, &CMyNewPaintDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMyNewPaintDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_CHECK1, &CMyNewPaintDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMyNewPaintDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMyNewPaintDlg::OnBnClickedCheck3)
	
	ON_BN_CLICKED(IDC_CHECK4, &CMyNewPaintDlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CMyNewPaintDlg message handlers

BOOL CMyNewPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	RefillColor = RGB(255, 255, 255);
	myMode = regular;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyNewPaintDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting
		for (int i = 0; i < figs.GetSize(); i++)
			figs[i]->Draw(&dc);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyNewPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyNewPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	isPressed = true;	

	if(isDragMode)
		{
			for (int k = 0; k < figs.GetSize(); k++)
			{
				if (figs[k]->isInside(point))
				{
					index = k;
					BPoint = point;
				}
			}
		}

	else if(isDelMode){
			for (int i = 0; i < figs.GetSize(); i++)
			{
				if (figs[i]->isInside(point))
				{
					figs.RemoveAt(i);

					Invalidate();

				}
			}
		}
	else if (IsResize) {
		for (int i = 0; i < figs.GetSize(); i++)
		{
			if (figs[i]->isInside(point)) {
				figs[i]->Resize(-5);
				Invalidate();
			}
		}
	}
	
	else
	{
		Figure* f = 0;
		start = point;
		switch (figType)
		{
		case -1: break;
		case 0: f = new MyLine(start, start, color, RefillColor); break;
		case 1: f = new MyRectangle(start, start, color, RefillColor); break;
		case 2: f = new MyTriangle(start, start, color, RefillColor); break;
		case 3: f = new MyEllipse(start, start, color, RefillColor); break;
		case 4: f = new MyCircle(start, start, color, RefillColor); break;
		}


		figs.Add(f);
	}	//f->setBg(color);
	
	CDialogEx::OnLButtonDown(nFlags, point);


}


void CMyNewPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (isPressed)
	{

			end = point;
			isPressed = false;
			if (myMode == regular)
				figs[figs.GetSize() - 1]->Redefine(start, end);
			
			Invalidate(); //simulates the WM_PAINT message to redraw window
			index = -1;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMyNewPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ((isPressed) && (!isDelMode))

		{

			if (isDragMode)
		{
			figs[index]->Shift(point.x - BPoint.x, point.y - BPoint.y);
			CClientDC dc(this);
			figs[index]->Draw(&dc);

			Invalidate();
			BPoint = point;
	
		}
			else
		{
			end = point;
			figs[figs.GetSize() - 1]->Redefine(start, end);
			Invalidate(); //simulates the WM_PAINT message to redraw window
		}
		}
	CDialogEx::OnMouseMove(nFlags, point);
}




void CMyNewPaintDlg::OnBnClickedButtonload()
{
 // TRUE to LOAD
	const TCHAR czFilter[] = _T("Shape files (*.shape)|*.shape|All Files (*.*)|*.*||");
	CFileDialog fDialog(TRUE, _T("shape"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, czFilter, this);

	if (fDialog.DoModal() == IDOK) {
		CString fileName = fDialog.GetPathName();
		CFile file(fileName, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}



void CMyNewPaintDlg::OnBnClickedButtonsave()
{
	// TODO: Add your control notification handler code here
	const TCHAR czFilter[] = _T("Shape files (*.shape)|*.shape|All Files (*.*)|*.*||");
	CFileDialog fDialog(FALSE, _T("shape"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, czFilter, this);

	if (fDialog.DoModal() == IDOK) {
		CString fileName = fDialog.GetPathName();
		CFile file(fileName, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CMyNewPaintDlg::OnBnClickedRadio1()// Line optinon
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_LINE));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	
	figType = 0;
}


void CMyNewPaintDlg::OnBnClickedRadio2()//rectangle option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_RECT));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);

		figType = 1;
}


void CMyNewPaintDlg::OnBnClickedRadio3()//triangle option
{
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
	figType = 2;
}


void CMyNewPaintDlg::OnBnClickedButton3()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (myMode == brush)
			RefillColor = dlg.GetColor();
		else
			color = dlg.GetColor();
	}
}


void CMyNewPaintDlg::OnBnClickedRadio4()////ellipse option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_ELLIPSE));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	figType = 3;
}


void CMyNewPaintDlg::OnBnClickedRadio5()// circle option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_ELLIPSE));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	figType = 4;
}


void CMyNewPaintDlg::OnBnClickedCheck1() //drag check
{
	if (dragMe.GetCheck() && figs.GetSize()>0)
	{
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_SIZEALL));
		isDragMode = true;
		myMode = drag;
		figType = -1;
		for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
		{
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
			pBtn->EnableWindow(FALSE);
		}
		CButton* pBtn = static_cast<CButton*>(GetDlgItem(IDC_CHECK3));
		pBtn->EnableWindow(FALSE);

	}
	else
	{ 
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
		{
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
			pBtn->SetCheck(BST_UNCHECKED);
			pBtn->EnableWindow(TRUE);
		}
		CButton* pBtn = static_cast<CButton*>(GetDlgItem(IDC_CHECK3));
		pBtn->EnableWindow(TRUE);
		isDragMode = false;
		myMode = regular;
	}
}


void CMyNewPaintDlg::OnBnClickedCheck2()
{
	if (brushB.GetCheck() )
	{
		myMode = brush;

	}
	else
	{
		myMode = regular;
	}
	
	
}





void CMyNewPaintDlg::OnBnClickedCheck3()//delete check
{
	if (deleteMe.GetCheck())
		{
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		isDelMode = true;
			myMode = del;
			for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
			{
				CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
				pBtn->EnableWindow(FALSE);
			}
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(IDC_CHECK1));
			pBtn->EnableWindow(FALSE);

		}
	else
	{
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
		{
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
			pBtn->SetCheck(BST_UNCHECKED);
			pBtn->EnableWindow(TRUE);
		}
		CButton* pBtn = static_cast<CButton*>(GetDlgItem(IDC_CHECK1));
		pBtn->EnableWindow(TRUE);
		isDelMode = false;
		myMode = regular;
	}
	}



void CMyNewPaintDlg::OnBnClickedCheck4() // resize 
{
	if (resize.GetCheck())
	{
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		IsResize = true;

		for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
		{
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
			pBtn->EnableWindow(FALSE);
		}
		CButton* pBtn1 = static_cast<CButton*>(GetDlgItem(IDC_CHECK1));
		pBtn1->EnableWindow(FALSE);
		CButton* pBtn3 = static_cast<CButton*>(GetDlgItem(IDC_CHECK3));
		pBtn3->EnableWindow(FALSE);

	}
	else
	{
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
		for (UINT nID = IDC_RADIO1; nID <= IDC_RADIO5; ++nID)
		{
			CButton* pBtn = static_cast<CButton*>(GetDlgItem(nID));
			pBtn->SetCheck(BST_UNCHECKED);
			pBtn->EnableWindow(TRUE);
		}
		CButton* pBtn = static_cast<CButton*>(GetDlgItem(IDC_CHECK1));
		pBtn->EnableWindow(TRUE);
		CButton* pBtn3 = static_cast<CButton*>(GetDlgItem(IDC_CHECK3));
		pBtn3->EnableWindow(TRUE);

		IsResize = false;

	}
}




