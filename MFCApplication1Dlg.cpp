
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(ID_BTN_CENTER, &CMFCApplication1Dlg::OnBnClickedBtnCenter)
	ON_BN_CLICKED(ID_BTN_CIRCLE, &CMFCApplication1Dlg::OnBnClickedBtnCircle)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

	
void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this);

	if (m_image != NULL)
	{
		m_image.Draw(dc, 0, 0);
	}
	
	

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMFCApplication1Dlg::OnBnClickedBtnCenter()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	CRect rect(0, 0, nWidth, nHeight);
	int nX = 0;
	int nY = 0;
	int nCount = 0;

	for (int i = rect.top; i< rect.bottom; i++)
	{
		for (int j = rect.left; j < rect.right; j++)
		{
			unsigned char* pixel = fm + i * nPitch + j * 3;

			if (pixel[0] + pixel[1] + pixel[2] > 0)
			{
				nX += j;
				nY += i;
				nCount++;
			}
		}
	}

	double nCenterX = (double)(nX / nCount);
	double nCenterY = (double)(nY / nCount);

	std::cout << nCenterX << ", " << nCenterY << '\n';

	DrawCross(nCenterX, nCenterY);

	Invalidate();

}


void CMFCApplication1Dlg::OnBnClickedBtnCircle()
{
	CDC cdc;
	CString radi;
	GetDlgItemText(IDC_EDIT_Radi, radi);

	if (m_image != NULL)
		m_image.Destroy();		
	

	m_radi = _tstoi(radi);

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 24;

	m_image.Create(nWidth, -nHeight, nBpp);

	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	


	int x = rand() % m_image.GetWidth();
	int y = rand() % m_image.GetHeight();

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			if (isInCircle(j,i,x,y)) {
				unsigned char* pixel = fm + i * nPitch + j * 3;

				pixel[0] = 0;
				pixel[1] = 0;
				pixel[2] = 255;
			}
			else{
				unsigned char* pixel = fm + i * nPitch + j * 3;

				pixel[0] = 0;
				pixel[1] = 0;
				pixel[2] = 0;
			}
		}
	}



	Invalidate();
}

void CMFCApplication1Dlg::DrawCircle(CDC* pDC)
{
	/*CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);*/

	if (m_image != NULL)
		m_image.Destroy();
	int x = rand() % m_image.GetWidth();
	int y = rand() % m_image.GetHeight();
	while (x <= 0 || x + m_radi*2 >= m_image.GetWidth() || y <= 0 || y + m_radi * 2 >= m_image.GetHeight() )
	{
		x = rand() % m_image.GetWidth();
		y = rand() % m_image.GetHeight();
	}

	/*CRect rect(x,y,x+m_radi*2,y+m_radi*2);
	pDC->Ellipse(rect);
	pDC->SelectObject(pOldPen);*/
	

}

void CMFCApplication1Dlg::DrawCross(int x, int y)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	for (int i = y-5; i < y + 5; i++)
	{
		unsigned char* pixel = fm + i * nPitch + x * 3;

		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 255;
	}
	for (int j = x-5; j < x + 5; j++)
	{
		unsigned char* pixel = fm + y * nPitch + j * 3;

		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 255;
	}
}

bool CMFCApplication1Dlg::isInCircle(int x, int y, int cx, int cy)
{
	bool flg = false;

	double dX = x - cx;
	double dY = y - cy;
	double dDist = dX * dX + dY * dY;
	if (dDist <= m_radi + 2 && dDist >= m_radi - 2 )
	{
		flg = true;
	}
	return flg;
}