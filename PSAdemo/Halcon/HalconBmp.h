//ѭ���ļ��ж�ͼ
////��ʼ��
//HalconBmp *bmp = NULL;
//vector<char*> dir;
//dir.push_back("G:/MCEQVIn0/2018-01-26/101");
//dir.push_back("G:/MCEQVIn0/2018-01-26/101");
//dir.push_back("G:/MCEQVIn0/2018-01-26/101");
//bmp = new HalconBmp(dir, 3);

////ʹ��
//HObject ho_Image;
//bmp->GetPic(2, ho_Image);

////�ͷ�
//if(NULL != bmp)
//	delete bmp;
#pragma once
#include<vector>
#include "HalconCpp.h"

using namespace std;
using namespace HalconCpp;

class HalconBmp
{
public:
	HalconBmp(vector<char*> dir);
	~HalconBmp(void);

	vector<HTuple> hv_ImageFilesVector;					//�ļ�������
	vector<int>    hv_IndexVector;						//ͼƬ·����ʶ

	bool GetPic(int type, HObject &ho_Image, CString &path);			//��ȡĳ�ļ���ͼƬ		
	bool  CheckFolderExist(CString charstrPath);						//Ŀ¼�Ƿ���ڵļ��
};

