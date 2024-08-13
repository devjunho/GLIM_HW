#pragma once


class CGLIMDlg : public CDialogEx
{
private:
	CImage m_image;
	int StartX = 0;
	int StartY = 0;
	int EndX = 0;
	int EndY = 0;
	int nRadius = 0;
	bool flag = FALSE;
public:
	CGLIMDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


// 구현입니다.
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strStartX;
	CString strStartY;
	CString strEndX;
	CString strEndY;
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	void UpdateDisplay();
	void destoryImage();
	int excessPoint(int Point, int compareSize, int count);
	void moveRect(int count, int gapX, int gapY);
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	int calculatePoint(int gap, int count, int StartPoint);
	int getPoint(CString pathName, int count);
	void drawX(int x, int y);
};