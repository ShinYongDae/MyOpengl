#pragma once
#include <thread>

#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")

#define WM_THREAD_END	(WM_USER + 0x73FF)	// 0x7FFF (Range of WM_USER is 0x400 ~ 0x7FFF)

static GLfloat ambient[] = { 0.1f,0.1f,0.1f,1.0f };			//이것은 자연광 1.0이 제일쎄고 지금은 0.1로했군..
static GLfloat diffuse[] = { 0.7f,0.7f,0.7f,1.0f };			//이것은 반사광
static GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };		//반짝임효과(재질때문에쓰인다
static GLfloat specreff[] = { 1.0f,1.0f,1.0f,1.0f };		//위랑 똑같음
static GLfloat pos[] = { 200.0f,300.0f,400.0f,1.0f };		//이것은 빛의 위치  x로500y로500z는0 


namespace Opengl
{
	typedef enum Mode { modPoint = 0, modLine = 1, modRectE = 2, modRectF = 3, modCross = 4, modCrossX = 5, modCircleE = 6, modCircleF = 7 };
}

struct stVertex
{
	float x;
	float y;
	float z;
};
typedef CArray<stVertex, stVertex> CArVertex;

struct stLine
{
	stVertex v1, v2;
};
typedef CArray<stLine, stLine> CArLine;

struct stColor
{
	GLfloat R;
	GLfloat G;
	GLfloat B;
	GLfloat A;
};

// CSimpleOpengl

class CSimpleOpengl : public CStatic //public CWnd
{
	DECLARE_DYNAMIC(CSimpleOpengl)

	CWnd* m_pParent;
	HWND m_hParent;
	HWND m_hCtrl;
	HDC m_hDc;
	CDC *m_pDc;
	HGLRC m_hRC;
	CRect m_rtDispCtrl;
	int m_nWorldW, m_nWorldH;
	CArLine m_arLine;

	BOOL m_bInit;
	BOOL m_bDraw, m_bDrawClear, m_bDrawClearColor;
	BOOL m_bThreadAlive, m_bThreadStateEnd;
	std::thread t1;

	GLfloat cameraposmap[3];
	GLfloat Angle[3];

	BOOL CreateWndForm(DWORD dwStyle);

	void ThreadStart();
	void ThreadStop();

	void StringToChar(CString str, char* szStr);

	void DrawBegin(int mode, int size, stColor color);
	void DrawEnd();
	void DrawRect(stVertex V1, stVertex V2);
	void DrawLine(stVertex V1, stVertex V2);
	void Draw();
	void DrawClear();
	void DrawClearColor(stColor color);

public:
	CSimpleOpengl();
	CSimpleOpengl(HWND& hCtrl, CWnd* pParent = NULL);
	virtual ~CSimpleOpengl();
	void SetHwnd(HWND hCtrlWnd, CWnd* pParent=NULL);
	//void SetHwnd(CDC* pDc, CWnd* pParent = NULL);
	void Refresh();

	static void ProcThrd(const LPVOID lpContext);

	void SetText(CString str, stVertex pos, int size=10, stColor color = { 1,1,1 }, int line_width=1);
	void SetClear();
	void SetClearColor();
	void SetDraw();

	void AddLine(stVertex v1, stVertex v2);

	void SetupResize(int cx, int cy);
	//void SetupLight(GLfloat R = 0.0f, GLfloat G = 0.0f, GLfloat B = 0.0f, GLfloat A = 1.0f, BOOL CirclePoint = 1);
	//void SetupCamera(GLfloat *cameraposmap, int W, int H, GLfloat *Angle);
	void Init();
	BOOL IsDraw();

protected:
	void ThreadEnd();
	BOOL ThreadIsAlive();
	BOOL ProcOpengl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
};


