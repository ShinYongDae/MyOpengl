
// MyOpenglDlg.h : 헤더 파일
//

#pragma once

#include "SimpleOpengl.h"


// CMyOpenglDlg 대화 상자
class CMyOpenglDlg : public CDialogEx
{
	CSimpleOpengl *m_pOpengl;
	CSimpleOpengl m_Opengl;
	CDC* m_pDc;

// 생성입니다.
public:
	CMyOpenglDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CMyOpenglDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYOPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
