
// PSAdemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "CalgorithmRegion.h"
#include "HalconBmp.h"
#include "HalconTool.h"
// CPSAdemoApp:
// �йش����ʵ�֣������ PSAdemo.cpp
//

class CPSAdemoApp : public CWinApp
{
public:
	CPSAdemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPSAdemoApp theApp;


//1.ȫ�ֱ�������
extern HalconBmp *g_pBmp;								//��ͼ����
extern HalconTool g_ToolDown;							//��ʾͼ�񹤾�
extern bool isRunPic;									//�Ƿ���ͼ
extern int g_SaveImage;									//ʶ���Ƿ񱣴�ͼ��(D:/ͼ�񱸷�/)
extern CalgorithmRegion *g_pCalgorithmRegion;			//�����㷨����