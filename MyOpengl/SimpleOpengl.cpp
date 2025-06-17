// SimpleOpengl.cpp : ���� �����Դϴ�.
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

	//CreateWndForm(WS_CHILD | WS_OVERLAPPED);
	ThreadStart();
}

CSimpleOpengl::CSimpleOpengl(HWND& hCtrl, CWnd* pParent/*=NULL*/)
{
	m_pParent = pParent;
	if (pParent)
		m_hParent = pParent->GetSafeHwnd();
	m_hCtrl = hCtrl;
	m_pDc = NULL;
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



// CSimpleOpengl �޽��� ó�����Դϴ�.

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

//void CSimpleOpengl::SetHwnd(CDC* pDc, CWnd* pParent/*=NULL*/)
void CSimpleOpengl::SetHwnd(HWND hCtrlWnd, CWnd* pParent/*=NULL*/)
{
	m_pParent = pParent;
	if (pParent)
		m_hParent = pParent->GetSafeHwnd();

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
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
	m_hCtrl = hCtrlWnd;
	m_pDc = new CClientDC(FromHandle(hCtrlWnd));
	//m_pDc = pDc;
	m_hDc = m_pDc->GetSafeHdc();
	//m_hDc = ::GetDC(hCtrlWnd);
	//m_hDc = ::GetDC(this->GetSafeHwnd());

	int nPixelFormat = ChoosePixelFormat(m_hDc, &pfd);	// DC�� �����ϴ� �־��� �ȼ� ���� ���� ��ġ�ϴ� ������ �ȼ� ������ ã�´�.
	VERIFY(SetPixelFormat(m_hDc, nPixelFormat, &pfd));	// HGLRC(GL Rendering Context Handle)�� DC�� ����

	m_hRC = wglCreateContext(m_hDc);					// Rendering Context ����
	VERIFY(wglMakeCurrent(m_hDc, m_hRC));				// ���� �����忡 Rendering Context ����

	int argc = 1;
	char *argv[1] = { (char*)"Something" };
	glutInit(&argc, argv);

	//SetupLight();
	//glDisable(GL_LIGHTING);

	CRect rtDispCtrl;
	::GetWindowRect(m_hCtrl, &rtDispCtrl);
	m_rtDispCtrl = rtDispCtrl;
	int nWorldW = rtDispCtrl.right - rtDispCtrl.left;
	int nWorldH = rtDispCtrl.bottom - rtDispCtrl.top;
	//SetupResize(nWorldW, nWorldH);

	//SetupCamera(cameraposmap, nWorldW, nWorldH, Angle);
}

void CSimpleOpengl::Refresh()
{
	RedrawWindow();
}


void CSimpleOpengl::Draw(CDC *pDc)
{
	//HDC hDc = pDc->GetSafeHdc();
	//m_hRC = wglCreateContext(m_pDc->GetSafeHdc());
	//wglMakeCurrent(m_hDc, m_hRC); //GVGLMakehDC(hDc, hRc);

	//SetupLight();
	//glDisable(GL_LIGHTING);

	//CRect rtDispCtrl;
	//::GetWindowRect(m_hCtrl, &rtDispCtrl);
	//int nWorldW = rtDispCtrl.right - rtDispCtrl.left;
	//int nWorldH = rtDispCtrl.bottom - rtDispCtrl.top;
	//SetupResize(nWorldW, nWorldH);

	//SetupCamera(cameraposmap, nWorldW, nWorldH, Angle);




	//m_hRC = wglCreateContext(m_hDc);	// Rendering Context ����
	//wglMakeCurrent(m_hDc, m_hRC);		// ���� �����忡 Rendering Context ����

	//SetupLight();
	//glDisable(GL_LIGHTING);

	//CRect rtDispCtrl;
	//::GetWindowRect(m_hCtrl, &rtDispCtrl);
	//int nWorldW = rtDispCtrl.right - rtDispCtrl.left;
	//int nWorldH = rtDispCtrl.bottom - rtDispCtrl.top;
	//SetupResize(nWorldW, nWorldH);

	//SetupCamera(cameraposmap, nWorldW, nWorldH, Angle);
	


	stVertex v1, v2;
	stColor color;
	//v1.x = m_rtDispCtrl.left; v1.y = m_rtDispCtrl.top; v1.z = 0.0;
	//v2.x = m_rtDispCtrl.right; v2.y = m_rtDispCtrl.bottom; v2.z = 0.0;
	v1.x = 0; v1.y = 0; v1.z = 0.0;
	v2.x = 0.5; v2.y = 0.5; v2.z = 0.0;
	color.R = 1.0; color.G = 0.0; color.B = 0.0; color.A = 0.0;
	//DrawBegin(Opengl::modRectF, 3, color);
	DrawBegin(Opengl::modLine, 3, color);
	DrawRect(v1, v2);

	////��
	//glVertex3f(0, 0, 0);
	//glVertex3f(0.3, 0, 0);
	////���Ӹ�
	//glVertex3f(0.3, 0, 0);
	//glVertex3f(0.21, 0.09, 0);
	////���Ӹ�
	//glVertex3f(0.3, 0, 0);
	//glVertex3f(0.21, -0.09, 0);

	DrawEnd();

	SwapBuffers(m_hDc); // OpenGL�� �Ϸ��� �׸��� ���Ӱ� ȭ�鿡 �׸��� - //���� buffer�� �׷��� �Ͱ� Frame�� �׷��� ���� swap(Double buffer)
}

void CSimpleOpengl::ProcThrd(const LPVOID lpContext)
{
	CSimpleOpengl* pSimpleOpengl = reinterpret_cast<CSimpleOpengl*>(lpContext);

	while (pSimpleOpengl->ThreadIsAlive())
	{
		if (!pSimpleOpengl->ProcOpengl())
			break;
	}

	pSimpleOpengl->ThreadEnd();
}

BOOL CSimpleOpengl::ProcOpengl()
{
	Sleep(100);
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

void CSimpleOpengl::SetupLight(GLfloat R, GLfloat G, GLfloat B, GLfloat A, BOOL CirclePoint)
{
	glClearColor(R, G, B, A);

	glEnable(GL_DEPTH_TEST);							//���̰�ǥ�� �ϱ����ػ��
	glEnable(GL_LIGHTING);								//������ Ų�ٴ¶�
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);			//light0��  �ڿ����� �ְ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);			//light0�� �ݻ籤�ְ�
	glLightfv(GL_LIGHT0, GL_POSITION, pos);				//light0�� �ڿ��� ��ġ�ְ�
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);		//light0��¦�� (�����ְ�)

	glEnable(GL_LIGHT0);								//light0�� �۵���Ŵ

	if (CirclePoint)glEnable(GL_POINT_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);						//���� ��Ʈ
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//������Ʈ
	glMaterialfv(GL_FRONT, GL_SPECULAR, specreff);		//������Ʈ
	glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void CSimpleOpengl::SetupResize(int cx, int cy)
{
	GLfloat fAspect;
	if (cy == 0)
		cy = 1;

	glViewport(0, 0, cx, cy);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)cx / (GLfloat)cy;
	gluPerspective(45.0f, fAspect, 1.0f, -1.0f);
	//GLfloat f_w = (GLfloat)cx / (GLfloat)_WINDOW_WIDTH;
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CSimpleOpengl::SetupCamera(GLfloat *cameraposmap, int W, int H, GLfloat *Angle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(Angle[2], 0.0f, 0.0f, 1.0f);

	glTranslatef(cameraposmap[0], cameraposmap[1], cameraposmap[2]);

	glRotatef(Angle[0], 1.0f, 0.0f, 0.0f);
	glRotatef(Angle[1], 0.0f, 1.0f, 0.0f);
}


void CSimpleOpengl::DrawBegin(int nMode, int nSize, stColor Color)
{
	if (nMode < Opengl::modPoint || nMode > Opengl::modCircleF)
		return;

	glPushMatrix(); // Martrix���¸� ���ÿ� �ִ´�
	glColor4f(Color.R, Color.G, Color.B, Color.A);

	/* glBegin ~ glEnd ��� ���̿� ��ġ���� ������ �������� ������
	���				����
	============================================================
	GL_POINTS			�������� ��
	GL_LINE_STRIP		����� ����
	GL_LINE_LOOP		�������� ������ ���� ����
	GL_LINES			�ΰ��� �������� ���� ����
	GL_TRIANGLES		������ ������ �ﰢ��
	GL_TRIANGLE_STRIP	����� �ﰢ��
	GL_TRIANGLE_FAN		�߽��� �����ϴ� �ﰢ��
	GL_QUADS			���� 4������ �����Ͽ� �簢���� �׸���.
	GL_QUAD_STRIP		����� �簢��
	GL_POLYGON			����� ���� �ٰ���
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
	glPopMatrix();	// Martrix���¸� ���ÿ��� ������
	glFlush();		//�׸��� �� �׷����ٴ� �� �˷���.
}

void CSimpleOpengl::DrawRect(stVertex V1, stVertex V2)
{
	//glVertex3f(V1.x, V1.y, V1.z);
	//glVertex3f(V2.x, V2.y, V2.z);
	glVertex3f(V1.x, V1.y, V1.z);
	glVertex3f(V2.x, V1.y, V2.z);

	glVertex3f(V2.x, V1.y, V2.z);
	glVertex3f(V2.x, V2.y, V2.z);

	glVertex3f(V2.x, V2.y, V2.z);
	glVertex3f(V1.x, V2.y, V1.z);

	glVertex3f(V1.x, V2.y, V1.z);
	glVertex3f(V1.x, V1.y, V1.z);
}



HBRUSH CSimpleOpengl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		//Draw(pDC);
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CSimpleOpengl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (CTLCOLOR_STATIC == nIDCtl)
	{
		//Draw();
	}

	CStatic::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSimpleOpengl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CStatic::OnPaint()��(��) ȣ������ ���ʽÿ�.

	//HDC hdc = ::GetDC(this->m_hWnd);
	//HDC hdc = dc.GetSafeHdc();
	//HGLRC hRc = wglCreateContext(hdc);

	//HGLRC hRc = wglCreateContext(dc.GetSafeHdc());
	//if (hRc == 0)
	//{
	//	AfxMessageBox(_T("Error Creating RC"));
	//	return;
	//}
	//Draw(&dc);

	Draw(m_pDc);
}
