// SimpleOpengl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyOpengl.h"
#include "SimpleOpengl.h"


// CSimpleOpengl

IMPLEMENT_DYNAMIC(CSimpleOpengl, CWnd)

CSimpleOpengl::CSimpleOpengl()
{
	m_hDc = NULL;
	m_pDc = NULL;

	cameraposmap[0] = 0.0f;
	cameraposmap[1] = 0.0f;
	cameraposmap[2] = 7000.0f;
	Angle[0] = 0.0f;
	Angle[1] = 0.0f;
	Angle[2] = 0.0f;
	m_bInit = FALSE;

	m_bDraw = FALSE;
	m_bDrawClear = FALSE;
	m_bDrawClearColor = FALSE;

	ThreadStart();
}

CSimpleOpengl::CSimpleOpengl(HWND& hCtrl, CWnd* pParent/*=NULL*/)
{
	m_pParent = pParent;
	if (pParent)
		m_hParent = pParent->GetSafeHwnd();
	m_hCtrl = hCtrl;
	m_pDc = NULL;
	m_bInit = FALSE;

	m_bDraw = FALSE;
	m_bDrawClear = FALSE;
	m_bDrawClearColor = FALSE;

	m_pDc = new CClientDC(FromHandle(hCtrl));
	CreateWndForm(WS_CHILD | WS_OVERLAPPED);
	ThreadStart();
}

CSimpleOpengl::~CSimpleOpengl()
{
	ThreadStop();
	Sleep(30);
	t1.join();


	if (m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

	if (m_pDc)
	{
		::ReleaseDC(m_hWnd, m_pDc->GetSafeHdc());
		delete m_pDc;
		m_pDc = NULL;
	}

}


BEGIN_MESSAGE_MAP(CSimpleOpengl, CWnd)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSimpleOpengl 메시지 처리기입니다.

BOOL CSimpleOpengl::CreateWndForm(DWORD dwStyle)
{
	//if (!Create(NULL, _T("CSimpleOpengl"), dwStyle, CRect(0, 0, 0, 0), m_pParent, (UINT)this))
	//{
	//	AfxMessageBox(_T("CSimpleOpengl::Create() Failed!!!"));
	//	return FALSE;
	//}
	//if (!Create(_T("CSimpleOpengl"), WS_CHILD | WS_OVERLAPPED, CRect(0, 0, 0, 0), m_pParent, (UINT)this))
	//{
	//	AfxMessageBox(_T("CSimpleOpengl::Create() Failed!!!"));
	//	return FALSE;
	//}

	return TRUE;
}

/*
// 그리기 표면의 픽셀 형식을 설명
typedef struct tagPIXELFORMATDESCRIPTOR {
	WORD  nSize;
	WORD  nVersion;
	DWORD dwFlags;
	BYTE  iPixelType;
	BYTE  cColorBits;
	BYTE  cRedBits;
	BYTE  cRedShift;
	BYTE  cGreenBits;
	BYTE  cGreenShift;
	BYTE  cBlueBits;
	BYTE  cBlueShift;
	BYTE  cAlphaBits;
	BYTE  cAlphaShift;
	BYTE  cAccumBits;
	BYTE  cAccumRedBits;
	BYTE  cAccumGreenBits;
	BYTE  cAccumBlueBits;
	BYTE  cAccumAlphaBits;
	BYTE  cDepthBits;
	BYTE  cStencilBits;
	BYTE  cAuxBuffers;
	BYTE  iLayerType;
	BYTE  bReserved;
	DWORD dwLayerMask;
	DWORD dwVisibleMask;
	DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

[dwFlags]
=================================================================================================================================================
값										의미
=================================================================================================================================================
PFD_DRAW_TO_WINDOW						버퍼는 창 또는 디바이스 화면에 그릴 수 있습니다.
0x00000004

PFD_DRAW_TO_BITMAP						버퍼는 메모리 비트맵에 그릴 수 있습니다.
0x00000008

PFD_SUPPORT_GDI							버퍼는 GDI 그리기를 지원합니다. 이 플래그 및 PFD_DOUBLEBUFFER 현재 제네릭 구현에서 상호 배타적입니다.
0x00000010

PFD_SUPPORT_OPENGL						버퍼는 OpenGL 그리기를 지원합니다.
0x00000020

PFD_GENERIC_ACCELERATED					픽셀 형식은 제네릭 구현을 가속화하는 디바이스 드라이버에서 지원됩니다. 이 플래그가 명확하고 PFD_GENERIC_FORMAT 플래그가 설정된 경우 픽셀 형식은 제네릭 구현에서만 지원됩니다.
0x00001000

PFD_GENERIC_FORMAT						픽셀 형식은 제네릭 구현이라고도 하는 GDI 소프트웨어 구현에서 지원됩니다. 이 비트가 명확한 경우 픽셀 형식은 디바이스 드라이버 또는 하드웨어에서 지원됩니다.
0x00000040

PFD_NEED_PALETTE						버퍼는 팔레트 관리 디바이스에서 RGBA 픽셀을 사용합니다. 이 픽셀 형식에 대한 최상의 결과를 얻으려면 논리적 팔레트가 필요합니다. 색상표의 색은 cRedBits, cRedShift, cGreenBits, cGreenShift, cBluebits 및 cBlueShift 멤버의 값에 따라 지정되어야 합니다. wglMakeCurrent를 호출하기 전에 디바이스 컨텍스트에서 팔레트를 만들고 실현해야 합니다.
0x00000080

PFD_NEED_SYSTEM_PALETTE					256색 모드에서만 하나의 하드웨어 팔레트를 지원하는 하드웨어의 픽셀 형식 설명자에 정의됩니다. 이러한 시스템에서 하드웨어 가속을 사용하려면 RGBA 모드에서 하드웨어 팔레트가 고정 순서(예: 3-3-2)이거나 색 인덱스 모드일 때 논리 팔레트와 일치해야 합니다. 이 플래그가 설정되면 프로그램에서 SetSystemPaletteUse 를 호출하여 논리 팔레트와 시스템 팔레트의 일대일 매핑을 강제해야 합니다. OpenGL 하드웨어가 여러 하드웨어 팔레트를 지원하고 디바이스 드라이버가 OpenGL에 예비 하드웨어 팔레트를 할당할 수 있는 경우 이 플래그는 일반적으로 명확합니다.
0x00000100								이 플래그는 제네릭 픽셀 형식으로 설정되지 않습니다.

PFD_DOUBLEBUFFER						버퍼가 이중 버퍼링됩니다. 이 플래그 및 PFD_SUPPORT_GDI 현재 제네릭 구현에서 상호 배타적입니다.
0x00000001

PFD_STEREO								버퍼는 입체입니다. 이 플래그는 현재 제네릭 구현에서 지원되지 않습니다.
0x00000002

PFD_SWAP_LAYER_BUFFERS					디바이스가 이중 버퍼링 오버레이 또는 언더레이 평면을 포함하는 픽셀 형식으로 개별 레이어 평면을 교환할 수 있는지 여부를 나타냅니다. 그렇지 않으면 모든 레이어 평면이 그룹으로 함께 교환됩니다. 이 플래그가 설정되면 wglSwapLayerBuffers 가 지원됩니다.
0x00000800
=================================================================================================================================================
*/
void CSimpleOpengl::Init()
{
	if (!m_bInit)
	{
		m_bInit = TRUE;
		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			//PFD_DRAW_TO_WINDOW |
			//PFD_SUPPORT_OPENGL |
			//PFD_DOUBLEBUFFER,				// 더블 버퍼 윈도우 (default: 싱글 버퍼 윈도우)
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL,
			PFD_TYPE_RGBA,					// RGBA 모드 (default)
			24,
			0,0,0,0,0,0,
			0,0,
			0,0,0,0,0,
			32,
			0,//1,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
		};

		int nPixelFormat = ChoosePixelFormat(m_hDc, &pfd);	// DC가 지원하는 주어진 픽셀 포맷 사양과 일치하는 적절한 픽셀 포맷을 찾는다.
		VERIFY(SetPixelFormat(m_hDc, nPixelFormat, &pfd));	// HGLRC(GL Rendering Context Handle)와 DC를 연결

		m_hRC = wglCreateContext(m_hDc);					// Rendering Context 생성
		VERIFY(wglMakeCurrent(m_hDc, m_hRC));				// 현재 스레드에 Rendering Context 설정

		int argc = 1;
		char *argv[1] = { (char*)"Something" };
		glutInit(&argc, argv);								// Window OS와 Session 연결 / GLUT Library를 초기화

		//SetupLight();
		//glDisable(GL_LIGHTING);

		CRect rtDispCtrl;
		::GetClientRect(m_hCtrl, &rtDispCtrl);
		//::GetWindowRect(m_hCtrl, &rtDispCtrl);
		m_rtDispCtrl = rtDispCtrl;
		m_nWorldW = rtDispCtrl.right - rtDispCtrl.left;
		m_nWorldH = rtDispCtrl.bottom - rtDispCtrl.top;
		SetupResize(m_nWorldW, m_nWorldH);
		//SetupCamera(cameraposmap, nWorldW, nWorldH, Angle);
	}
}

void CSimpleOpengl::SetHwnd(HWND hCtrlWnd, CWnd* pParent/*=NULL*/)
{
	m_pParent = pParent;
	if (pParent)
		m_hParent = pParent->GetSafeHwnd();

	m_hCtrl = hCtrlWnd;
	m_pDc = new CClientDC(FromHandle(hCtrlWnd));
	//m_pDc = pDc;
	m_hDc = m_pDc->GetSafeHdc();
	//m_hDc = ::GetDC(hCtrlWnd);
	//m_hDc = ::GetDC(this->GetSafeHwnd());

	//Init();
}

void CSimpleOpengl::Refresh()
{
	RedrawWindow();
}

BOOL CSimpleOpengl::IsDraw()
{
	return m_bDraw;
}

void CSimpleOpengl::ProcThrd(const LPVOID lpContext)
{
	CSimpleOpengl* pSimpleOpengl = reinterpret_cast<CSimpleOpengl*>(lpContext);

	while (pSimpleOpengl->ThreadIsAlive())
	{
		if (!pSimpleOpengl->ProcOpengl())
			break;
		Sleep(30);
	}

	pSimpleOpengl->ThreadEnd();
}

BOOL CSimpleOpengl::ProcOpengl()
{
	if (m_bDraw)
	{
		m_bDraw = FALSE;
		Init();
		Draw();
	}
	if (m_bDrawClear)
	{
		m_bDrawClear = FALSE;
		DrawClear();
	}
	if (m_bDrawClearColor)
	{
		m_bDrawClearColor = FALSE;
		stColor color = { 0.0, 0.0, 1.0, 1.0 }; // BLUE
		DrawClearColor(color);
	}
	return TRUE;
}

void CSimpleOpengl::ThreadStart()
{
	m_bThreadStateEnd = FALSE;
	m_bThreadAlive = TRUE;
	t1 = std::thread(ProcThrd, this);
}

void CSimpleOpengl::ThreadStop()
{
	m_bThreadAlive = FALSE;
	MSG message;
	const DWORD dwTimeOut = 1000 * 60 * 3; // 3 Minute
	DWORD dwStartTick = GetTickCount();
	Sleep(30);
	while (!m_bThreadStateEnd)
	{
		if (GetTickCount() >= (dwStartTick + dwTimeOut))
		{
			AfxMessageBox(_T("WaitUntilThreadEnd() Time Out!!!", NULL, MB_OK | MB_ICONSTOP));
			return;
		}
		if (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
		Sleep(30);
	}
}

void CSimpleOpengl::ThreadEnd()
{
	//HWND hWnd = this->GetSafeHwnd();
	//if(!hWnd)
	m_bThreadStateEnd = TRUE;
}

BOOL CSimpleOpengl::ThreadIsAlive()
{
	return m_bThreadAlive;
}

//void CSimpleOpengl::SetupLight(GLfloat R, GLfloat G, GLfloat B, GLfloat A, BOOL CirclePoint)
//{
//	glClearColor(R, G, B, A);
//
//	glEnable(GL_DEPTH_TEST);							//깊이값표현 하기위해사용
//	glEnable(GL_LIGHTING);								//조명을 킨다는뜻
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);			//light0에  자연광을 넣고
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);			//light0에 반사광넣고
//	glLightfv(GL_LIGHT0, GL_POSITION, pos);				//light0에 자연광 위치넣고
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);		//light0반짝임 (재질넣고)
//
//	glEnable(GL_LIGHT0);								//light0를 작동시킴
//
//	if (CirclePoint)glEnable(GL_POINT_SMOOTH);
//
//	glEnable(GL_COLOR_MATERIAL);						//재질 파트
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//재질파트
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specreff);		//재질파트
//	glMateriali(GL_FRONT, GL_SHININESS, 128);
//}

void CSimpleOpengl::SetupResize(int cx, int cy)
{
	GLfloat fAspect;
	if (cy == 0)
		cy = 1;

	glViewport(0, 0, cx, cy);
	//glOrtho(-0.5 * cx, 0.5 * cx, -0.5 * cy, 0.5 * cy, -2, 2);
	glOrtho(0.0, cx, cy, 0.0, -2, 2); // (min_x, max_x, min_y, max_y, near, far)
	//glOrtho(0.0, cx, 0.0, cy, -2, 2); // (min_x, max_x, min_y, max_y, near, far)
/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)cx / (GLfloat)cy;
	gluPerspective(45.0f, fAspect, 1.0f, -1.0f); // (시야각, 종횡비 (W/H), Front_z, Back_z)
	//GLfloat f_w = (GLfloat)cx / (GLfloat)_WINDOW_WIDTH;
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

//void CSimpleOpengl::SetupCamera(GLfloat *cameraposmap, int W, int H, GLfloat *Angle)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glRotatef(Angle[2], 0.0f, 0.0f, 1.0f);
//
//	glTranslatef(cameraposmap[0], cameraposmap[1], cameraposmap[2]);
//
//	glRotatef(Angle[0], 1.0f, 0.0f, 0.0f);
//	glRotatef(Angle[1], 0.0f, 1.0f, 0.0f);
//}


void CSimpleOpengl::DrawBegin(int nMode, int nSize, stColor Color)
{
	if (nMode < Opengl::modPoint || nMode > Opengl::modCircleF)
		return;

	glPushMatrix(); // Martrix상태를 스택에 넣는다
	glColor4f(Color.R, Color.G, Color.B, Color.A);

	/* glBegin ~ glEnd 블록 사이에 위치만을 가지는 정점만을 정의함
	모드				설명
	============================================================
	GL_POINTS			독립적인 점
	GL_LINE_STRIP		연결된 선분
	GL_LINE_LOOP		시작점과 끝점을 이은 선분
	GL_LINES			두개의 정점들을 이은 선분
	GL_TRIANGLES		세개씩 연결한 삼각형
	GL_TRIANGLE_STRIP	연결된 삼각형
	GL_TRIANGLE_FAN		중심을 공유하는 삼각형
	GL_QUADS			정점 4개씩을 연결하여 사각형을 그린다.
	GL_QUAD_STRIP		연결된 사각형
	GL_POLYGON			연결된 볼록 다각형
	============================================================*/
	
	switch (nMode)
	{
	case Opengl::modPoint:
		glPointSize(nSize);
		glBegin(GL_POINTS);
		break;
	case Opengl::modLine:
	case Opengl::modRectE:
	case Opengl::modCross:
	case Opengl::modCrossX:
		glLineWidth(nSize);
		glBegin(GL_LINES);
		break;
	case Opengl::modRectF:
		glLineWidth(nSize);
		glBegin(GL_QUADS);
		break;
	case Opengl::modCircleE:
		glLineWidth(nSize);
		glBegin(GL_LINE_LOOP);
		break;
	case Opengl::modCircleF:
		glLineWidth(nSize);
		glBegin(GL_POLYGON);
		break;
	}
}

void CSimpleOpengl::DrawEnd()
{
	glEnd();
	glPopMatrix();	// Martrix상태를 스택에서 꺼낸다
}

void CSimpleOpengl::DrawRect(stVertex V1, stVertex V2)
{
	glVertex3f(V1.x, V1.y, V1.z);
	glVertex3f(V2.x, V1.y, V2.z);

	glVertex3f(V2.x, V1.y, V2.z);
	glVertex3f(V2.x, V2.y, V2.z);

	glVertex3f(V2.x, V2.y, V2.z);
	glVertex3f(V1.x, V2.y, V1.z);

	glVertex3f(V1.x, V2.y, V1.z);
	glVertex3f(V1.x, V1.y, V1.z);
}

void CSimpleOpengl::DrawLine(stVertex V1, stVertex V2)
{
	glVertex3f(V1.x, V1.y, V1.z);
	glVertex3f(V2.x, V2.y, V2.z);
}

void CSimpleOpengl::SetText(CString str, stVertex pos, int size, stColor color, int line_width)
{
	int nLen = str.GetLength();
	char* pData = new char[nLen + 1]; // for '\0'
	StringToChar(str, pData);

	char *c;
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glLineWidth(line_width);
	glColor3f(color.R, color.G, color.B);
	glScalef(0.01f*size, 0.01f*size, 0.01f*size);

	for (c = pData; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();

	delete pData;
}


HBRUSH CSimpleOpengl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		//Draw(pDC);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CSimpleOpengl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (CTLCOLOR_STATIC == nIDCtl)
	{
		//Draw();
	}

	CStatic::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSimpleOpengl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.

	//Draw();
	m_bDraw = TRUE;
}

void CSimpleOpengl::StringToChar(CString str, char* szStr)  // char* returned must be deleted... 
{
	int nLen = str.GetLength();
	strcpy(szStr, CT2A(str));
	szStr[nLen] = _T('\0');
}

void CSimpleOpengl::AddLine(stVertex v1, stVertex v2)
{
	stLine _line;
	_line.v1 = v1;
	_line.v2 = v2;
	m_arLine.Add(_line);
}

//void CSimpleOpengl::Draw()
//{
//	stVertex v1, v2;
//	stColor color;
//
//	v1.x = m_nWorldW/2; v1.y = m_nWorldH/2; v1.z = 0.0;
//	SetText(_T("Shin Yong Dae"), v1);
//
//	v1.x = 1; v1.y = 1; v1.z = 0.0;
//	v2.x = m_nWorldW; v2.y = m_nWorldH; v2.z = 0.0;
//	color.R = 1.0; color.G = 0.0; color.B = 0.0; color.A = 0.0;
//	DrawBegin(Opengl::modLine, 1, color);
//	DrawRect(v1, v2);
//	DrawEnd();
//
//	v1.x = 0.25*m_nWorldW; v1.y = 0.25*m_nWorldH; v1.z = 0.0;
//	v2.x = 0.75*m_nWorldW; v2.y = 0.75*m_nWorldH; v2.z = 0.0;
//	color.R = 0.0; color.G = 1.0; color.B = 0.0; color.A = 0.0;
//	DrawBegin(Opengl::modLine, 1, color);
//	DrawRect(v1, v2);
//	DrawEnd();
//
//	glFlush();				// 그림이 다 그렸졌다는 걸 알려줌.
//	SwapBuffers(m_hDc);		// OpenGL이 완료한 그림을 새롭게 화면에 그린다 - //현재 buffer에 그려진 것과 Frame에 그려진 것을 swap(Double buffer)
//}

void CSimpleOpengl::Draw()
{
	int i, nTotal;
	stLine _line;
	stColor color;

	nTotal = m_arLine.GetCount();

	if (nTotal <= 0)	return;

	color.R = 1.0; color.G = 0.0; color.B = 0.0; color.A = 0.0;
	DrawBegin(Opengl::modLine, 1, color);

	for (i = 0; i < nTotal; i++)
	{
		_line = m_arLine.GetAt(i);
		DrawLine(_line.v1, _line.v2);
	}

	DrawEnd();
	glFlush();											// 그림이 다 그렸졌다는 걸 알려줌.
	SwapBuffers(m_hDc);									// OpenGL이 완료한 그림을 새롭게 화면에 그린다 - //현재 buffer에 그려진 것과 Frame에 그려진 것을 swap(Double buffer)

	m_arLine.RemoveAll();
}

void CSimpleOpengl::DrawClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();											// 그림이 다 그렸졌다는 걸 알려줌.
	SwapBuffers(m_hDc);									// OpenGL이 완료한 그림을 새롭게 화면에 그린다 - //현재 buffer에 그려진 것과 Frame에 그려진 것을 swap(Double buffer)
}

void CSimpleOpengl::DrawClearColor(stColor color)
{
	glClearColor(color.R, color.G, color.B, color.A);	// 바탕색을 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();											// 그림이 다 그렸졌다는 걸 알려줌.
	SwapBuffers(m_hDc);									// OpenGL이 완료한 그림을 새롭게 화면에 그린다 - //현재 buffer에 그려진 것과 Frame에 그려진 것을 swap(Double buffer)
}

void CSimpleOpengl::SetClear()
{
	m_bDrawClear = TRUE;
}

void CSimpleOpengl::SetClearColor()
{
	m_bDrawClearColor = TRUE;
}

void CSimpleOpengl::SetDraw()
{
	m_bDraw = TRUE;
}
