
// MyOpenglDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MyOpengl.h"
#include "MyOpenglDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
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


// CMyOpenglDlg 대화 상자

CMyOpenglDlg::CMyOpenglDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYOPENGL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pOpengl = NULL;
	m_pDc = NULL;
}

CMyOpenglDlg::~CMyOpenglDlg()
{
	if (m_pOpengl)
	{
		delete m_pOpengl;
		m_pOpengl = NULL;
	}

	//if (m_pDc)
	//{
	//	::ReleaseDC(m_hWnd, m_pDc->GetSafeHdc());
	//	delete m_pDc;
	//	m_pDc = NULL;
	//}
}

void CMyOpenglDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyOpenglDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyOpenglDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyOpenglDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyOpenglDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyOpenglDlg 메시지 처리기

BOOL CMyOpenglDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//HDC hDc = ::GetDC(this->m_hWnd);


	//GetDlgItem(IDC_STATIC_OPENGL)->SetWindowText(_T(""));
	HWND hWnd = GetDlgItem(IDC_STATIC_OPENGL)->GetSafeHwnd();
	//m_pOpengl = new CSimpleOpengl(hWnd, this);
	m_Opengl.SubclassDlgItem(IDC_STATIC_OPENGL, this);
	m_Opengl.SetHwnd(hWnd, this);
	//m_pDc = new CClientDC(FromHandle(hWnd));
	//m_Opengl.SetHwnd(m_pDc, this);
	//m_Opengl.RedrawWindow(NULL, NULL, RDW_INVALIDATE);
	m_Opengl.SetFont(_T("굴림체"), 12, TRUE);

	stVertex v1, v2;
	v1.x = 10; v1.y = 10; v1.z = 0.0;
	v2.x = 500; v2.y = 500; v2.z = 0.0;
	m_Opengl.AddLine(v1, v2);

	SetTimer(0, 100, NULL);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyOpenglDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyOpenglDlg::OnPaint()
{
	//HDC hDc = ::GetDC(this->m_hWnd);

	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyOpenglDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyOpenglDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		KillTimer(0);

		stVertex v1, v2;
		v1.x = 500; v1.y = 500; v1.z = 0.0;
		v2.x = 1100; v2.y = 500; v2.z = 0.0;
		m_Opengl.AddLine(v1, v2);
		m_Opengl.Refresh();

		//m_Opengl.RedrawWindow(NULL, NULL, RDW_INVALIDATE);

		//SetTimer(0, 100, NULL);
	}

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CMyOpenglDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	//HDC hDc = ::GetDC(this->m_hWnd);
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMyOpenglDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_Opengl.DrawClear();
	m_Opengl.SetClear();
}


void CMyOpenglDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Opengl.SetClearColor();
}


void CMyOpenglDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	stVertex v1, v2;
	v1.x = 10; v1.y = 10; v1.z = 0.0;
	v2.x = 500; v2.y = 500; v2.z = 0.0;
	m_Opengl.AddLine(v1, v2);
	v1.x = 500; v1.y = 500; v1.z = 0.0;
	v2.x = 1100; v2.y = 500; v2.z = 0.0;
	m_Opengl.AddLine(v1, v2);
	m_Opengl.SetDraw();
}
