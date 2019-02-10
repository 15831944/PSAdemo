// ModelBuildDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModelBuildDlg.h"
#include "afxdialogex.h"
#include "MassageDlg.h"

// CModelBuildDlg �Ի���

IMPLEMENT_DYNAMIC(CModelBuildDlg, CDialogEx)

CModelBuildDlg::CModelBuildDlg(HObject &scrImage, int type, 
	CalgorithmRegion::ModelParameter &Parameter, CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelBuildDlg::IDD, pParent)
	, m_AStart(0)
	, m_ARange(0)
	, m_Score(0)
	, m_IsMultImage(FALSE)
	, m_Mult(0)
	, m_Add(0)
	, m_MouseDown(false)
	, m_ModelCheck(0)
	, m_isRubber(FALSE)
	, m_UseRect2(FALSE)
	, m_median(0)
	, m_UseMedian(FALSE)
{
	this->type = type;
	this->Parameter = Parameter;
	this->scrImage = scrImage;
}

CModelBuildDlg::~CModelBuildDlg()
{
}

void CModelBuildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ASTART, m_AStart);
	DDX_Text(pDX, IDC_ARANGE, m_ARange);
	DDX_Text(pDX, IDC_SCORE, m_Score);
	DDX_Check(pDX, IDC_CHECK_MULT, m_IsMultImage);
	DDX_Text(pDX, IDC_EDIT_MULT, m_Mult);
	DDX_Text(pDX, IDC_EDIT_ADD, m_Add);
	DDX_Control(pDX, IDC_SLIDER_MULT, m_MultSc);
	DDX_Control(pDX, IDC_SLIDER_ADD, m_AddSc);
	DDX_Control(pDX, IDC_COMBO_LINE, m_Line);
	DDX_Control(pDX, IDC_COMBO_CHECK, m_check);
	DDX_Control(pDX, IDC_COMBO_C, m_Point);
	DDX_Radio(pDX, IDC_MODLE, m_ModelCheck);
	DDX_Control(pDX, IDC_SLIDER_EDIT, m_RubberSize);
	DDX_Check(pDX, IDC_CHECK_EDIT, m_isRubber);
	DDX_Check(pDX, IDC_CHECK_RECT2, m_UseRect2);
	DDX_Text(pDX, IDC_EDIT_MEDIAN, m_median);
	DDX_Control(pDX, IDC_SLIDER_MEDIAN, m_MedianSc);
	DDX_Check(pDX, IDC_CHECK_MEDIAN, m_UseMedian);
}


BEGIN_MESSAGE_MAP(CModelBuildDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RECT, &CModelBuildDlg::OnBnClickedBtnRect)
	ON_BN_CLICKED(IDC_BTN_MODEL, &CModelBuildDlg::OnBnClickedBtnModel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CModelBuildDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_CHECK_MULT, &CModelBuildDlg::OnBnClickedCheckMult)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MULT, &CModelBuildDlg::OnNMCustomdrawSliderMult)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ADD, &CModelBuildDlg::OnNMCustomdrawSliderAdd)
	ON_BN_CLICKED(IDC_BTN_LINE1, &CModelBuildDlg::OnBnClickedBtnLine1)
	ON_BN_CLICKED(IDC_BTN_LINE2, &CModelBuildDlg::OnBnClickedBtnLine2)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECK, &CModelBuildDlg::OnCbnSelchangeComboCheck)
	ON_BN_CLICKED(IDC_BTN_C1, &CModelBuildDlg::OnBnClickedBtnC1)
	ON_BN_CLICKED(IDC_BTN_C2, &CModelBuildDlg::OnBnClickedBtnC2)
	ON_BN_CLICKED(IDC_BTN_RECT1, &CModelBuildDlg::OnBnClickedBtnRect1)
	ON_BN_CLICKED(IDC_MODLE, &CModelBuildDlg::OnBnClickedModle)
	ON_BN_CLICKED(IDC_LINES, &CModelBuildDlg::OnBnClickedLines)
	ON_BN_CLICKED(IDC_CIR, &CModelBuildDlg::OnBnClickedCir)
	ON_BN_CLICKED(IDC_RECT, &CModelBuildDlg::OnBnClickedRect)
	ON_BN_CLICKED(IDC_CHECK_EDIT, &CModelBuildDlg::OnBnClickedCheckEdit)
	ON_BN_CLICKED(IDC_CENTER, &CModelBuildDlg::OnBnClickedCenter)
	ON_BN_CLICKED(IDC_BTN_TEST, &CModelBuildDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_SIGLE_CIR, &CModelBuildDlg::OnBnClickedSigleCir)
	ON_BN_CLICKED(IDC_BTN_LINE, &CModelBuildDlg::OnBnClickedBtnLine)
	ON_BN_CLICKED(IDC_SIGLE_LINE, &CModelBuildDlg::OnBnClickedSigleLine)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MEDIAN, &CModelBuildDlg::OnNMCustomdrawSliderMedian)
	ON_BN_CLICKED(IDC_CHECK_MEDIAN, &CModelBuildDlg::OnBnClickedCheckMedian)
	ON_BN_CLICKED(IDC_BTN_C, &CModelBuildDlg::OnBnClickedBtnC)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_MULT, &CModelBuildDlg::OnEnChangeEditMult)
END_MESSAGE_MAP()


// CModelBuildDlg ��Ϣ�������


void CModelBuildDlg::OnBnClickedBtnRect()
{
	//������Χ
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_RECT, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_RECT, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownRect(ToolModel, scrImage, Parameter);
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpRect(ToolModel, scrImage, Parameter);
			break;
		}
		SetDlgItemText(IDC_BTN_RECT, L"������Χ");
	}
}


void CModelBuildDlg::OnBnClickedBtnModel()
{
	UpdateData(true);
	//ѡ��ģ��
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_MODEL, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_MODEL, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->BuildDownModel(ToolModel, scrImage,
				m_UseRect2, Parameter);
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->BuildUpModel(ToolModel, scrImage,
				m_UseRect2, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_MODEL, L"ѡ��ģ��");
	}
	//��ǰģ��
	switch(type)
	{
	case 0:
		//�װ�		
		g_pCalgorithmRegion->RestoreDownModel(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 0,
			Parameter);
		break;
	case 1:
		//��Ƭ
		g_pCalgorithmRegion->RestoreUpModel(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 0,
			Parameter);
		break;
	}
}


void CModelBuildDlg::OnBnClickedBtnSave()
{
	//ͼ��Ԥ����
	OnBnClickedCheckMult();
	//ƥ�䷽ʽ
	OnBnClickedModle();

	//����
	UpdateData(true);
	if(m_isRubber)
	{
		m_isRubber = false;
		UpdateData(false);
		OnBnClickedCheckEdit();
	}

	//����ģ��
	switch(type)
	{
	case 0:
		//�װ�		
		g_pCalgorithmRegion->SaveDownParameter(Parameter);
		break;
	case 1:
		//��Ƭ
		g_pCalgorithmRegion->SaveUpParameter(Parameter);
		break;
	}	

	//ʶ�����
	vector<double> results;
	bool ret = false;
	switch(type)
	{
	case 0:
		{
			//�װ�		
			g_pCalgorithmRegion->SetDownModel(Parameter.model_Name, Parameter);
			ret = g_pCalgorithmRegion->FindDownModel(ToolModel, scrImage, results, Parameter, g_SaveImage);
		}
		break;
	case 1:
		{
			//��Ƭ
			g_pCalgorithmRegion->SetUpModel(Parameter.model_Name, Parameter);
			ret = g_pCalgorithmRegion->FindUpModel(ToolModel, scrImage, results, Parameter, g_SaveImage);
		}
		break;
	}	
	ToolModel.ShowImage(scrImage);
	if(!ret)
	{
		AfxMessageBox(L"ģ�屣��ʧ�ܣ��밴�������±༭ģ��"); 
	}
}


BOOL CModelBuildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����
	SetWindowTextW(L"�༭ģ�壺"+Parameter.model_Name);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ToolModel.SetWindow(GetDlgItem(IDC_STATIC_MODELVIEW));

	GetDlgItem(IDC_EDIT_MULT)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_ADD)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_MEDIAN)->EnableWindow(false);

	//��׼�߳�ʼ��
	m_Line.InsertString(0, L"ֱ��1");
	m_Line.InsertString(1, L"ֱ��2");

	//��׼���ʼ��
	m_Point.InsertString(0, L"Բ��1");
	m_Point.InsertString(1, L"Բ��2");
	
	//ʶ��ʽ
	m_check.InsertString(0, L"ģ��ƥ��");
	m_check.InsertString(1, L"ֱ��ƥ��");
	m_check.InsertString(2, L"Բ��ƥ��");
	m_check.InsertString(3, L"����ƥ��");
	m_check.InsertString(4, L"ʵ��Բƥ��");

	switch(type)
	{
	case 0:
		//�װ�
		m_AStart = (double)Parameter.hv_AStart;
		m_ARange = (double)Parameter.hv_ARange;
		m_Score = (double)Parameter.hv_Score;

		m_Mult = (double)Parameter.hv_Mult;
		m_Add = (double)Parameter.hv_Add;
		m_IsMultImage = Parameter.is_Mult;

		m_median = Parameter.hv_Parameter_median;
		m_UseMedian = Parameter.hv_median_bool;

		m_Line.SetCurSel(Parameter.linesParameter.baseline);
		m_Point.SetCurSel(Parameter.circlesParameter.basepoint);
		if(L"" == Parameter.check)
		{
			m_ModelCheck = 0;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Lines" == Parameter.check)
		{
			m_ModelCheck = 1;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Circles" == Parameter.check)
		{
			m_ModelCheck = 2;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Rects" == Parameter.check)
		{
			m_ModelCheck = 3;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"SolidCircle" == Parameter.check)
		{
			m_ModelCheck = 4;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Line" == Parameter.check)
		{
			m_ModelCheck = 5;
			m_check.SetCurSel(m_ModelCheck);
		}
		break;
	case 1:
		//��Ƭ
		m_AStart = (double)Parameter.hv_AStart;
		m_ARange = (double)Parameter.hv_ARange;
		m_Score = (double)Parameter.hv_Score;

		m_Mult = (double)Parameter.hv_Mult;
		m_Add = (double)Parameter.hv_Add;
		m_IsMultImage = Parameter.is_Mult;

		m_median = Parameter.hv_Parameter_median;
		m_UseMedian = Parameter.hv_median_bool;

		m_Line.SetCurSel(Parameter.linesParameter.baseline);
		m_Point.SetCurSel(Parameter.circlesParameter.basepoint);
		if(L"" == Parameter.check)
		{
			m_ModelCheck = 0;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Lines" == Parameter.check)
		{
			m_ModelCheck = 1;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Circles" == Parameter.check)
		{
			m_ModelCheck = 2;
			m_check.SetCurSel(m_ModelCheck);
		}
		else if(L"Rects" == Parameter.check)
		{
			m_ModelCheck = 3;
			m_check.SetCurSel(m_ModelCheck);
		}		
		else if(L"SolidCircle" == Parameter.check)
		{
			m_ModelCheck = 4;
			m_check.SetCurSel(m_ModelCheck);
		}
		break;
	}	

	//��Ƥ�ߴ�С
	m_RubberSize.SetRange(10,50,TRUE);	
	m_RubberSize.SetPos(25);

	UpdateData(false);

	//ͼ��Աȶȳ�ʼ��
	//Mult:0.01~0.1
	//Add��-2000~0
	m_MultSc.SetRange(1,10,TRUE);	
	m_MultSc.SetPos(m_Mult*100);
	m_AddSc.SetRange(-2000,0,TRUE);	
	m_AddSc.SetPos(m_Add);

	//��ֵ�˲���
	m_MedianSc.SetRange(1,20,TRUE);	
	m_MedianSc.SetPos(m_median);

	//ͼ����ʾ��С
	CRect rect0;
	GetDlgItem(IDC_STATIC_MODELVIEW)->GetWindowRect(rect0);
	CRect rect1;
	rect1.SetRect(0, 0, rect0.Height(), rect0.Height());
	GetDlgItem(IDC_STATIC_MODELVIEW)->MoveWindow(rect1, TRUE);

	OnBnClickedCheckMult();
	OnBnClickedModle();

	//��ǰģ��
	switch(type)
	{
	case 0:
		//�װ�		
		g_pCalgorithmRegion->RestoreDownModel(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 0,
			Parameter);
		break;
	case 1:
		//��Ƭ
		g_pCalgorithmRegion->RestoreUpModel(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 0,
			Parameter);
		break;
	}

	//��ʾ��ͼ���԰�ť
	if(isRunPic)
		GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CModelBuildDlg::OnBnClickedCheckMult()
{
	//�Ƿ���ǿͼ��Ա�
	UpdateData(true);
	
	Parameter.hv_Mult = m_Mult;
	Parameter.hv_Add = m_Add;
	Parameter.is_Mult = m_IsMultImage;
	Parameter.hv_Parameter_median = m_median;
	Parameter.hv_median_bool = m_UseMedian;

	HObject dstImage;	
	switch(type)
	{
	case 0:
		//�װ�
		dstImage = g_pCalgorithmRegion->SetPretreatImage(ToolModel, scrImage,
			g_pCalgorithmRegion->DownSetting, Parameter, 
			Parameter.model_Name);
		break;
	case 1:
		//��Ƭ
		dstImage = g_pCalgorithmRegion->SetPretreatImage(ToolModel, scrImage,
			g_pCalgorithmRegion->UpSetting, Parameter, 
			Parameter.model_Name);
		break;
	}
	ToolModel.ShowImage(dstImage);
}


void CModelBuildDlg::OnNMCustomdrawSliderMult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//mult
	m_Mult = m_MultSc.GetPos()/100.0;
	UpdateData(false);
	OnBnClickedCheckMult();
	*pResult = 0;
}


void CModelBuildDlg::OnNMCustomdrawSliderAdd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//add
	m_Add = m_AddSc.GetPos();
	UpdateData(false);
	OnBnClickedCheckMult();
	*pResult = 0;
}

BOOL CModelBuildDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg ->message == WM_KEYDOWN)  // If a keydown message
	{
		double oldX = ToolModel.m_X;
		double oldY = ToolModel.m_Y;

		if(VK_LEFT==pMsg ->wParam )
		{
			ToolModel.m_X = oldX - 20;
		}
		else if(VK_DOWN==pMsg ->wParam)
		{
			ToolModel.m_Y = oldY + 20;
		}
		else if(VK_UP==pMsg ->wParam)
		{
			ToolModel.m_Y = oldY - 20;
		}
		else if(VK_RIGHT==pMsg ->wParam)
		{
			ToolModel.m_X = oldX + 20;
		}
		OnBnClickedCheckMult();
	}

	//������������
	if (pMsg->message == WM_LBUTTONDOWN)  
    {  
		CRect rect0;
		GetDlgItem(IDC_STATIC_MODELVIEW)->GetWindowRect(rect0);
		CPoint  pt;
        GetCursorPos(&pt);	
		if (rect0.PtInRect(pt))
		{
			//����ƶ���ָ��������		
			UpdateData(true);
			if(m_isRubber)
			{
				//��Ƥ��
				double dx = pt.x-rect0.left;
				double dy = pt.y-rect0.top;
				ViewToImage(dx, dy);
				HObject rubber;
				GenCircle(&rubber, dy, dx, m_RubberSize.GetPos());		
				Union2(rubber, ho_RubberRectangle, &ho_RubberRectangle);

				//����ģ��
				g_pCalgorithmRegion->EditModel(ToolModel, scrImage, 
					ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld);
			}
			else
			{
				//��갴��
				m_MouseDown = true;
				//����λ��
				origin = pMsg->pt;
			}
			return true;
		}
    }  
    //����������  
    else if (pMsg->message == WM_LBUTTONUP)  
    {  
		m_MouseDown = false;
    }  
	//����ƶ�
	else if (pMsg->message == WM_MOUSEMOVE)  
	{  
		int zDelta= pMsg->wParam;
		CRect rect0;
		GetDlgItem(IDC_STATIC_MODELVIEW)->GetWindowRect(rect0);
		CPoint  pt;
        GetCursorPos(&pt);	
		if (rect0.PtInRect(pt))
        {
			//����ƶ���ָ��������		
			UpdateData(true);
			if(m_isRubber)
			{
				//��Ƥ��
				double dx = pt.x-rect0.left;
				double dy = pt.y-rect0.top;
				ViewToImage(dx, dy);
				HObject rubber;
				GenCircle(&rubber, dy, dx, m_RubberSize.GetPos());
				ToolModel.downlines.clear();
				ToolModel.downlines.push_back(rubber);			
				OnBnClickedCheckMult();
			}
			else
			{
				//�ƶ�ͼ��
				if(m_MouseDown)
				{
					double oldX = ToolModel.m_X;
					double oldY = ToolModel.m_Y;

					if(pMsg->pt.x > origin.x && (pMsg->pt.x - origin.x)>5)
					{
						ToolModel.m_X = oldX - 5;

						origin.x = pMsg->pt.x ;
					}
					else if(pMsg->pt.x < origin.x && (origin.x - pMsg->pt.x)>5)
					{
						ToolModel.m_X = oldX + 5;

						origin.x = pMsg->pt.x ;
					}

					if(pMsg->pt.y > origin.y&& (pMsg->pt.y - origin.y)>5)
					{
						/*ToolModel.m_Y = oldY - 0.3*(point.y - origin.y);*/
						ToolModel.m_Y = oldY - 5;

						origin.y = pMsg->pt.y;
					}
					else if(pMsg->pt.y < origin.y&& (origin.y - pMsg->pt.y)>5)
					{
						/*ToolModel.m_Y = oldY + 0.3*(origin.y - point.y);*/
						ToolModel.m_Y = oldY + 5;

						origin.y = pMsg->pt.y;
					}
					OnBnClickedCheckMult();
				}
			}
			return true;
        }
	}  
	//����м�����
	else if (pMsg->message == WM_MOUSEWHEEL)  
	{
		int zDelta= pMsg->wParam;
		CRect rect0;
		GetDlgItem(IDC_STATIC_MODELVIEW)->GetWindowRect(rect0);

		//����ƶ���ָ��������
		if((rect0.top < pMsg->pt.y && rect0.bottom > pMsg->pt.y) && (rect0.left < pMsg->pt.x && rect0.right > pMsg->pt.x))
		{
			double oldscale = ToolModel.m_scale;
			if(zDelta > 0)
			{
				ToolModel.m_scale = oldscale * 1.25;			
			}
			else if(zDelta < 0)
			{
				ToolModel.m_scale = oldscale * 0.75;
			}
			OnBnClickedCheckMult();
		}
	}	
	//return CDialogEx::PreTranslateMessage(pMsg);
	return false;
}


void CModelBuildDlg::OnBnClickedBtnLine1()
{
	//ֱ��1����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_LINE1, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_LINE1, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownLinesRect(ToolModel, scrImage, 1, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpLinesRect(ToolModel, scrImage, 1, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_LINE1, L"ֱ��1����");
	}
}


void CModelBuildDlg::OnBnClickedBtnLine2()
{
	//ֱ��2����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_LINE2, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_LINE2, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownLinesRect(ToolModel, scrImage, 2, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpLinesRect(ToolModel, scrImage, 2, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_LINE2, L"ֱ��2����");
	}
}


void CModelBuildDlg::OnCbnSelchangeComboCheck()
{
	//ʶ��ʽ
	UpdateData(true);		
	CString check;
	switch(m_check.GetCurSel())
	{
	case 0:
		check = L"";	
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		//Բ��
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		break;
	case 1:
		check = L"Lines";	
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);
				
		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BASE)->SetWindowText(L"��׼��");
				
		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		break;
	case 2:
		check = L"Circles";	
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BASE)->SetWindowText(L"��׼��");
				
		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		break;
	case 3:
		check = L"Rects";	
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);
				
		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_SHOW);
		break;
	}
	Parameter.hv_AStart = m_AStart;
	Parameter.hv_ARange = m_ARange;
	Parameter.hv_Score = m_Score;
	Parameter.linesParameter.baseline = m_Line.GetCurSel();
	Parameter.circlesParameter.basepoint = m_Point.GetCurSel();
	Parameter.check = check;
}


void CModelBuildDlg::OnBnClickedBtnC1()
{
	//Բ��1����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_C1, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_C1, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownCirclesRect(ToolModel, scrImage, 1, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpCirclesRect(ToolModel, scrImage, 1, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_C1, L"Բ��1����");
	}
}


void CModelBuildDlg::OnBnClickedBtnC2()
{
	//Բ��2����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_C2, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_C2, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownCirclesRect(ToolModel, scrImage, 2, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpCirclesRect(ToolModel, scrImage, 2, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_C2, L"Բ��2����");
	}
}


void CModelBuildDlg::OnBnClickedBtnRect1()
{
	//��������
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_RECT1, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_RECT1, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownRectsRect(ToolModel, scrImage, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpRectsRect(ToolModel, scrImage, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_RECT1, L"��������");
	}
}

void CModelBuildDlg::OnBnClickedBtnLine()
{
	//��ֱ������
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_LINE, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_LINE, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownLineRect(ToolModel, scrImage, Parameter);			
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpLineRect(ToolModel, scrImage, Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_LINE, L"ֱ������");
	}
}


void CModelBuildDlg::OnBnClickedModle()
{
	//ģ��ƥ��
	UpdateData(true);
	CString check;
	switch(m_ModelCheck)
	{
	case 0:
		check = L"";	
		//ģ��
		GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_SHOW);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		//Բ��
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_HIDE);
		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_HIDE);
		break;
	case 1:
		check = L"Lines";	
		//ģ��
		GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_SHOW);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BASE)->SetWindowText(L"��׼��");

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_HIDE);
		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_HIDE);
		break;
	case 2:
		check = L"Circles";	
		//ģ��
		GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_SHOW);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BASE)->SetWindowText(L"��׼��");

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_HIDE);
		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_HIDE);
		break;
	case 3:
		check = L"Rects";	
		//ģ��
		GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_SHOW);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_SHOW);
		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_HIDE);
		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_HIDE);
		break;
	case 4:
		check = L"SolidCircle";	
		//ģ��
		//GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_HIDE);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		//Բ��
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);
		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_HIDE);

		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_SHOW);
		break;
	case 5:
		check = L"Line";	
		//ģ��
		GetDlgItem(IDC_BTN_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_RECT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EDIT)->ShowWindow(SW_SHOW);
		//ֱ��
		GetDlgItem(IDC_BTN_LINE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_LINE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_LINE)->ShowWindow(SW_HIDE);
		//Բ��
		GetDlgItem(IDC_BTN_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_C)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_BASE)->ShowWindow(SW_HIDE);

		//����
		GetDlgItem(IDC_BTN_RECT1)->ShowWindow(SW_HIDE);

		//��ֱ��
		GetDlgItem(IDC_BTN_LINE)->ShowWindow(SW_SHOW);

		//��Բ��
		GetDlgItem(IDC_BTN_C)->ShowWindow(SW_HIDE);
		break;
	}
	Parameter.hv_AStart = m_AStart;
	Parameter.hv_ARange = m_ARange;
	Parameter.hv_Score = m_Score;
	Parameter.linesParameter.baseline = m_Line.GetCurSel();
	Parameter.circlesParameter.basepoint = m_Point.GetCurSel();
	Parameter.check = check;
}


void CModelBuildDlg::OnBnClickedLines()
{
	//ֱ��ƥ��
	OnBnClickedModle();
}


void CModelBuildDlg::OnBnClickedCir()
{
	//Բ��ƥ��
	OnBnClickedModle();
}


void CModelBuildDlg::OnBnClickedRect()
{
	//����ƥ��
	OnBnClickedModle();
}

void CModelBuildDlg::OnBnClickedSigleCir()
{
	//ʵ��Բƥ��
	OnBnClickedModle();
}

void CModelBuildDlg::OnBnClickedSigleLine()
{
	//��ֱ��ƥ��
	OnBnClickedModle();
}

void CModelBuildDlg::OnBnClickedCheckEdit()
{
	//����
	UpdateData(true);
	bool ret = false;
	if(m_isRubber)
	{
		//������������
		//��ԭģ��
		switch(type)
		{
		case 0:
			//�װ�		
			ret = g_pCalgorithmRegion->RestoreDownModel(ToolModel, scrImage, 
				ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 1,
				Parameter);
			break;
		case 1:
			//��Ƭ
			ret = g_pCalgorithmRegion->RestoreUpModel(ToolModel, scrImage, 
				ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld, 1,
				Parameter);
			break;
		}
		if(!ret)
		{
			m_isRubber = false;
			ToolModel.downlines.clear();
			UpdateData(false);
		}
	}
	else
	{
		//��ɲ���
		ToolModel.downlines.clear();

		//���������ģ��
		switch(type)
		{
		case 0:
			//�װ�		
			g_pCalgorithmRegion->SaveDownModel(ToolModel, scrImage,
				ho_Rectangle_model, Parameter);
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SaveUpModel(ToolModel, scrImage,
				ho_Rectangle_model, Parameter);
			break;
		}

		OnBnClickedCenter();
	}
}


void CModelBuildDlg::OnBnClickedCenter()
{
	//����
	switch(type)
	{
	case 0:
		//�װ�
		g_pCalgorithmRegion->SaveDownGravity(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld,
			Parameter);
		break;
	case 1:
		//��Ƭ
		g_pCalgorithmRegion->SaveUpGravity(ToolModel, scrImage, 
			ho_Rectangle, ho_Rectangle_model, ho_RubberRectangle, ho_Region_xld,
			Parameter);
		break;
	}
}

void CModelBuildDlg::ViewToImage(double &dx,double &dy)
{
	//��������תͼ������
	CRect picRect;
	GetDlgItem(IDC_STATIC_MODELVIEW)->GetWindowRect(&picRect);
	ScreenToClient(picRect);

	//double ratioX = (double)g_pMachineCur->GetDownCam()->GetPicWidth()/picRect.Width();
	//double ratioY = (double)g_pMachineCur->GetDownCam()->GetPicHeight()/picRect.Height();

	double ratioX = (double)(ToolModel.PartCol1-ToolModel.PartCol0)/picRect.Width();
	double ratioY = (double)(ToolModel.PartRow1-ToolModel.PartRow0)/picRect.Height();

	dx = dx*ratioX + ToolModel.PartCol0;
	dy = dy*ratioY + ToolModel.PartRow0;
}


void CModelBuildDlg::OnBnClickedBtnTest()
{
	//��ͼ����
	//HObject image;
	//vector<double> findResults;
	//bool ret = false;

	////�������Ϲ���
	//vector<double> parameters, results;
	////����λ�ý��
	//vector<CString> paths;
	//vector<vector<double>> allResults;
	//CString path;
	//int count = 36;

	////���Ա���
	//vector<double> X_paste, Y_paste, X_obj, Y_obj;
	//for(int i=0; i< count; i++)
	//{
	//	switch(type)
	//	{
	//	case 0:
	//		{
	//			//�װ�		
	//			g_pBmp->GetPic(0, image, path);
	//			ret = g_pCalgorithmRegion->FindDownModel(ToolModel, image, findResults, Parameter, g_SaveImage);
	//		}
	//		break;
	//	case 1:
	//		{
	//			//��Ƭ
	//			g_pBmp->GetPic(1, image, path);
	//			ret = g_pCalgorithmRegion->FindUpModel(ToolModel, image, findResults, Parameter, g_SaveImage);

	//			parameters.clear();
	//			//�װ����ݣ���е����ϵ��
	//			parameters.push_back(0);
	//			parameters.push_back(i*20);
	//			parameters.push_back(0);
	//			//�װ�ƫ�����ݣ��Եװ�ֱ��Ϊ����ϵ��
	//			parameters.push_back(0);
	//			parameters.push_back(0);
	//			parameters.push_back(0);
	//			//��Ƭ���ݣ�������������ϵ��
	//			parameters.push_back(findResults[0]);
	//			parameters.push_back(findResults[1]);
	//			parameters.push_back(findResults[2]);
	//		}
	//		break;
	//	}	
	//	
	//	g_pCalgorithmRegion->GetResult(parameters, results);

	//	parameters.push_back(results[0]);
	//	parameters.push_back(results[1]);
	//	parameters.push_back(results[2]);
	//	paths.push_back(path);
	//	allResults.push_back(parameters);
	//	ToolModel.ShowImage(image);

	//	X_paste.push_back(allResults[i][6]);
	//	Y_paste.push_back(allResults[i][7]);
	//	X_obj.push_back(allResults[i][9]);
	//	Y_obj.push_back(allResults[i][10]);
	//}

	AfxMessageBox(L"��ͼ�������ϵ��������"); 
}


void CModelBuildDlg::OnNMCustomdrawSliderMedian(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// ��ֵ�˲�������
	m_median = m_MedianSc.GetPos();
	UpdateData(false);
	OnBnClickedCheckMult();
	*pResult = 0;
}


void CModelBuildDlg::OnBnClickedCheckMedian()
{
	//2.�Ƿ�ʹ����ֵ�˲���
	OnBnClickedCheckMult();
}


void CModelBuildDlg::OnBnClickedBtnC()
{
	//Բ������
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_C, butCStr);
	if(L"����Ҽ�ȷ��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_C, L"����Ҽ�ȷ��");
		switch(type)
		{
		case 0:
			//�װ�
			g_pCalgorithmRegion->SetDownCircleRect(ToolModel, scrImage, 
				Parameter);
			break;
		case 1:
			//��Ƭ
			g_pCalgorithmRegion->SetUpCircleRect(ToolModel, scrImage, 
				Parameter);
			break;
		}	
		SetDlgItemText(IDC_BTN_C, L"Բ������");
	}
}


void CModelBuildDlg::OnClose()
{
	bool ret = false;
	switch(type)
	{
	case 0:
		//�װ�
		ret = g_pCalgorithmRegion->CompareDownParameters(Parameter);
		break;
	case 1:
		//��Ƭ
		ret = g_pCalgorithmRegion->CompareUpParameters(Parameter);
		break;
	}
	if(!ret)
	{
		CMassageDlg l_MassageDlg(_T("ȷ��Ҫ����ģ����"),this);
		int ret = l_MassageDlg.DoModal();
		if(IDOK == ret)
		{
			OnBnClickedBtnSave();
		}
		if(IDCANCEL == ret)
		{
			
		}
	}
	CDialogEx::OnClose();
}


void CModelBuildDlg::OnEnChangeEditMult()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
