
// MyOpengl.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyOpenglApp:
// �� Ŭ������ ������ ���ؼ��� MyOpengl.cpp�� �����Ͻʽÿ�.
//

class CMyOpenglApp : public CWinApp
{
public:
	CMyOpenglApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyOpenglApp theApp;