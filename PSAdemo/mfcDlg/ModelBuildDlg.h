#pragma once
#include "CalgorithmRegion.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "readme.h"

// CModelBuildDlg �Ի���

class CModelBuildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelBuildDlg)

public:
	CModelBuildDlg(HObject &scrImage, int type, CalgorithmRegion::ModelParameter &Parameter, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelBuildDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRect();
	afx_msg void OnBnClickedBtnModel();
	afx_msg void OnBnClickedBtnSave();

	int type;					//0���װ�ģ�壬 1����Ƭģ��
	HObject scrImage;			//ԭͼ��
	HalconTool ToolModel;		//ģ����ʾͼ�񹤾�
	virtual BOOL OnInitDialog();
	// ��ʼ�Ƕ�
	double m_AStart;
	// �Ƕȷ�Χ
	double m_ARange;
	// �ϸ����
	double m_Score;

	//��ǿͼ��Ա�
	afx_msg void OnBnClickedCheckMult();
	afx_msg void OnNMCustomdrawSliderMult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderAdd(NMHDR *pNMHDR, LRESULT *pResult);

	// �Ƿ���ǿͼ��Ա�
	BOOL m_IsMultImage;
	// ��ǿͼ��Ա�mult
	double m_Mult;
	// ��ǿͼ��Ա�add
	double m_Add;
	// mult������
	CSliderCtrl m_MultSc;
	// add������
	CSliderCtrl m_AddSc;

	//�������ƶ�
	//����Ƿ������
	bool m_MouseDown;
	//������갴��ʱ������
	CPoint origin;  
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//ֱ��1ֱ��2����
	afx_msg void OnBnClickedBtnLine1();
	afx_msg void OnBnClickedBtnLine2();
	// ��׼��
	CComboBox m_Line;
	// ʶ��ʽ
	CComboBox m_check;
	afx_msg void OnCbnSelchangeComboCheck();

	//Բ��1Բ��2����
	afx_msg void OnBnClickedBtnC1();
	afx_msg void OnBnClickedBtnC2();
	// ��׼��
	CComboBox m_Point;

	//��Ƭ�װ����
	CalgorithmRegion::ModelParameter Parameter;
	afx_msg void OnBnClickedBtnRect1();
	// ƥ�䷽ʽ
	int m_ModelCheck;
	afx_msg void OnBnClickedModle();
	afx_msg void OnBnClickedLines();
	afx_msg void OnBnClickedCir();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRect();

	//ԭģ������ ������ʣ������ ģ������ ��������
	HObject ho_Rectangle, ho_Rectangle_model, ho_Region_xld, ho_RubberRectangle;

	// ������Ƥ�ߴ�С
	CSliderCtrl m_RubberSize;
	afx_msg void OnBnClickedCheckEdit();
	// �Ƿ����ò�������
	BOOL m_isRubber;
	afx_msg void OnBnClickedCenter();

	//��������תͼ������
	void ViewToImage(double &dx,double &dy);
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedSigleCir();
	// �Ƿ�ʹ�þ���2ѡ��ģ��
	BOOL m_UseRect2;
	afx_msg void OnBnClickedBtnLine();
	afx_msg void OnBnClickedSigleLine();


	// ��ֵ�˲�������
	int m_median;
	afx_msg void OnNMCustomdrawSliderMedian(NMHDR *pNMHDR, LRESULT *pResult);
	// ��ֵ�˲����뻬����
	CSliderCtrl m_MedianSc;
	afx_msg void OnBnClickedCheckMedian();
	// �Ƿ�ʹ����ֵ�˲�
	BOOL m_UseMedian;
	afx_msg void OnBnClickedBtnC();
	afx_msg void OnClose();
	afx_msg void OnEnChangeEditMult();
};
