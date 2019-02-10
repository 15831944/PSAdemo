
// PSAdemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CPSAdemoDlg �Ի���
class CPSAdemoDlg : public CDialogEx
{
// ����
public:
	CPSAdemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PSADEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetpic();
	afx_msg void OnBnClickedBtnEditmodel();
	afx_msg void OnBnClickedBtnFindmodel();

	//3.���Ա����
	//ģ�����
	CalgorithmRegion::ModelParameter DownParameter;
	// ����ģ��
	CComboBox m_AllModel;
	vector<CString> m_DownModels;
	afx_msg void OnCbnSelchangeAllModel();
	afx_msg void OnBnClickedBtnAdd();
	// ����ģ������
	CString m_AddName;
	afx_msg void OnBnClickedBtnDelete();
	// ��ǰģ��
	CString m_CurModel;
};
