
// ReNet_OCR.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReNet_OCRApp: 
// �йش����ʵ�֣������ ReNet_OCR.cpp
//

class CReNet_OCRApp : public CWinApp
{
public:
	CReNet_OCRApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReNet_OCRApp theApp;