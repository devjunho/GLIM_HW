#include "pch.h"
#include "framework.h"
#include "GLIM.h"
#include "GLIMDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <atlstr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()





CGLIMDlg::CGLIMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_DIALOG, pParent)
	, strStartX(_T("0"))
	, strStartY(_T("0"))
	, strEndX(_T("0"))
	, strEndY(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_strStartX, strStartX);
	DDX_Text(pDX, IDC_EDIT_strStartY, strStartY);
	DDX_Text(pDX, IDC_EDIT_strEndX, strEndX);
	DDX_Text(pDX, IDC_EDIT_strEndY, strEndY);
}

BEGIN_MESSAGE_MAP(CGLIMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CGLIMDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGLIMDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGLIMDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGLIMDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()



BOOL CGLIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CGLIMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CGLIMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CGLIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGLIMDlg::OnBnClickedBtnImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;
	flag = FALSE;

	destoryImage();

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
	}
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	UpdateDisplay();
}

void CGLIMDlg::OnBnClickedBtnDraw()
{
	UpdateData(TRUE);
	StartX = _ttoi(strStartX);
	StartY = _ttoi(strStartY);
	if (flag || m_image == NULL)
	{
		MessageBox(L"Image 버튼을 눌러주세요", L"알림", MB_OK | MB_ICONQUESTION);
	}
	else if (strStartX.GetLength() > 3 || strStartY.GetLength() > 3)
	{
		MessageBox(L"올바른 좌표 값을 설정해주세요.\n가로 폭 = 640 / 세로 폭 = 480", L"알림", MB_OK | MB_ICONQUESTION);
	}
	else
	{
		nRadius = (rand() % 21) + 10;

		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();

		StartX = excessPoint(StartX, nWidth, 100);
		StartY = excessPoint(StartY, nHeight, 200);

		int nGray = 80;
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		memset(fm, 0xff, nWidth * nHeight);

		drawCircle(fm, StartX, StartY, nRadius, nGray);

		UpdateDisplay();
	}
	UpdateData(FALSE);
}

void CGLIMDlg::OnBnClickedBtnAction()
{
	UpdateData(TRUE);
	if (flag || m_image == NULL)
	{
		MessageBox(L"Image 버튼을 눌러주세요", L"알림", MB_OK | MB_ICONQUESTION);
	}
	else
	{
		StartX = _ttoi(strStartX);
		StartY = _ttoi(strStartY);
		EndX = _ttoi(strEndX);
		EndY = _ttoi(strEndY);

		if (StartX == 0 && StartY == 0 && EndX == 0 && EndY == 0)
		{
			MessageBox(L"좌표 값을 설정해주세요.", L"알림", MB_OK | MB_ICONQUESTION);
		}
		else if (strStartX.GetLength() > 3 || strStartY.GetLength() > 3 || strEndX.GetLength() > 3 || strEndY.GetLength() > 3)
		{
			MessageBox(L"올바른 좌표 값을 설정해주세요.\n가로 폭 = 640 / 세로 폭 = 480", L"알림", MB_OK | MB_ICONQUESTION);
		}
		else
		{
			static int gapX;
			static int gapY;
			int nWidth = m_image.GetWidth();
			int nHeight = m_image.GetHeight();

			if (nRadius == 0)
			{
				nRadius = (rand() % 21) + 10;
			}

			StartX = excessPoint(StartX, nWidth, 100);
			StartY = excessPoint(StartY, nHeight, 200);
			EndX = excessPoint(EndX, nWidth, 300);
			EndY = excessPoint(EndY, nHeight, 400);

			gapX = EndX - StartX;
			gapY = EndY - StartY;

			if (abs(gapX) >= abs(gapY))
			{
				for (int i = 0; i <= abs(gapX); i++)
				{
					moveRect(i, gapX, gapY);
					Sleep(1);
				}
			}
			else
			{
				for (int i = 0; i <= abs(gapY); i++)
				{
					moveRect(i, gapX, gapY);
					Sleep(1);
				}
			}
		}
	}
	UpdateData(FALSE);
}

void CGLIMDlg::OnBnClickedBtnOpen()
{
	TCHAR szFile[] = _T("모든파일(*.*)|*.*||");
	CString pathName;
	int PointX = 0;
	int PointY = 0;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFile);
	if (dlg.DoModal() == IDOK)
	{
		flag = TRUE;
		pathName = dlg.GetPathName();

		PointX = getPoint(pathName, 1);
		PointY = getPoint(pathName, 2);

		destoryImage();

		m_image.Load(pathName);

		drawX(PointX, PointY);

		SetDlgItemInt(IDC_EDIT_strStartX, 0);
		SetDlgItemInt(IDC_EDIT_strStartY, 0);
		SetDlgItemInt(IDC_EDIT_strEndX, 0);
		SetDlgItemInt(IDC_EDIT_strEndY, 0);

		UpdateDisplay();
	}
	else
	{
		MessageBox(L"파일 열기가 취소되었습니다.", L"알림", MB_OK | MB_ICONQUESTION);
	}
}


void CGLIMDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}


void CGLIMDlg::destoryImage()
{
	if (m_image != NULL)
	{
		m_image.Destroy();
	}
}

int CGLIMDlg::excessPoint(int Point, int compareSize, int count)
{
	CString Text;
	if (Point + (nRadius * 2) > compareSize)
	{
		Point = compareSize - (nRadius * 2);
		if (count == 100)
		{
			SetDlgItemInt(IDC_EDIT_strStartX, Point);
			Text.Format(L"%s 최대 좌표 값: %d", L"x1", Point);
		}
		else if (count == 200)
		{
			SetDlgItemInt(IDC_EDIT_strStartY, Point);
			Text.Format(L"%s 최대 좌표 값: %d", L"y1", Point);
		}
		else if (count == 300)
		{
			SetDlgItemInt(IDC_EDIT_strEndX, Point);
			Text.Format(L"%s 최대 좌표 값: %d", L"x2", Point);
		}
		else
		{
			SetDlgItemInt(IDC_EDIT_strEndY, Point);
			Text.Format(L"%s 최대 좌표 값: %d", L"y2", Point);
		}
		std::wstring Message(Text.GetString());
		MessageBox(Message.c_str(), L"알림", MB_OK | MB_ICONQUESTION);
	}
	return Point;
}

void CGLIMDlg::moveRect(int count, int gapX, int gapY)
{
	int calculateX = 0;
	int calculateY = 0;
	int nGray = 80;

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	calculateX = calculatePoint(gapX, count, StartX);
	calculateY = calculatePoint(gapY, count, StartY);

	memset(fm, 0xff, nWidth * nHeight);

	drawCircle(fm, calculateX, calculateY, nRadius, nGray);

	UpdateDisplay();

	CString strFile;
	strFile.Format(_T("C:\\GLIM\\image\\,%d,%d,.bmp"), calculateX + nRadius, calculateY + nRadius);
	m_image.Save(strFile);
}

void CGLIMDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	UpdateData(TRUE);
	SetDlgItemInt(IDC_STATIC_CTX, nCenterX);
	SetDlgItemInt(IDC_STATIC_CTY, nCenterY);
	UpdateData(FALSE);

	for (int j = y; j < y + nRadius * 2; j++)
	{
		for (int i = x; i < x + nRadius * 2;i++)
		{
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
			{
				fm[j * nPitch + i] = nGray;
			}
		}
	}
}

bool CGLIMDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;

	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}

	return bRet;
}

int CGLIMDlg::calculatePoint(int gap, int count, int StartPoint)
{
	int calculatePoint = 0;
	if (gap >= 0)
	{
		if (abs(count) > abs(gap))
		{
			calculatePoint = StartPoint + gap;
		}
		else
		{
			calculatePoint = StartPoint + 1 * abs(count);
		}
	}
	else
	{
		if (abs(count) > abs(gap))
		{
			calculatePoint = StartPoint + gap;
		}
		else
		{
			calculatePoint = StartPoint - 1 * abs(count);
		}
	}
	return calculatePoint;
}

int CGLIMDlg::getPoint(CString pathName, int count)
{
	CString Str;
	int nPoint = 0;
	AfxExtractSubString(Str, pathName, count, ',');
	nPoint = _ttoi(Str);
	return nPoint;
}

void CGLIMDlg::drawX(int x, int y)
{
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	UpdateData(TRUE);
	SetDlgItemInt(IDC_STATIC_CTX, x);
	SetDlgItemInt(IDC_STATIC_CTY, y);
	UpdateData(FALSE);

	fm[y * nPitch + x] = 255;

	for (int i = 1; i < 3; i++)
		fm[(y - i) * nPitch + (x - i)] = 255;

	for (int i = 1; i < 3; i++)
		fm[(y - i) * nPitch + (x + i)] = 255;

	for (int i = 1; i < 3; i++)
		fm[(y + i) * nPitch + (x - i)] = 255;

	for (int i = 1; i < 3; i++)
		fm[(y + i) * nPitch + (x + i)] = 255;

	UpdateDisplay();
}