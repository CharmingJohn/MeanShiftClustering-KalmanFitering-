//Edited by github.com/charmingjohn


// Mean shift clustering.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMeanshiftclusteringApp:
// �� Ŭ������ ������ ���ؼ��� Mean shift clustering.cpp�� �����Ͻʽÿ�.
//

class CMeanshiftclusteringApp : public CWinApp
{
public:
	CMeanshiftclusteringApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMeanshiftclusteringApp theApp;