
// MyOpenglDlg.h : ��� ����
//

#pragma once

#include "SimpleOpengl.h"


// CMyOpenglDlg ��ȭ ����
class CMyOpenglDlg : public CDialogEx
{
	CSimpleOpengl *m_pOpengl;
	CSimpleOpengl m_Opengl;
	CDC* m_pDc;

// �����Դϴ�.
public:
	CMyOpenglDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CMyOpenglDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYOPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
