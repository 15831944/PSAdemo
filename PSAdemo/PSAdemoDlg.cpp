
// PSAdemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PSAdemo.h"
#include "PSAdemoDlg.h"
#include "afxdialogex.h"
#include "ModelBuildDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPSAdemoDlg �Ի���




CPSAdemoDlg::CPSAdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPSAdemoDlg::IDD, pParent)
	, m_AddName(_T(""))
	, m_CurModel(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPSAdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALL_MODEL, m_AllModel);
	DDX_Text(pDX, IDC_ADD_NAME, m_AddName);
	DDX_Text(pDX, IDC_CUR_MODEL, m_CurModel);
}

BEGIN_MESSAGE_MAP(CPSAdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GETPIC, &CPSAdemoDlg::OnBnClickedBtnGetpic)
	ON_BN_CLICKED(IDC_BTN_EDITMODEL, &CPSAdemoDlg::OnBnClickedBtnEditmodel)
	ON_BN_CLICKED(IDC_BTN_FINDMODEL, &CPSAdemoDlg::OnBnClickedBtnFindmodel)
	ON_CBN_SELCHANGE(IDC_ALL_MODEL, &CPSAdemoDlg::OnCbnSelchangeAllModel)
	ON_BN_CLICKED(IDC_BTN_ADD, &CPSAdemoDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CPSAdemoDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CPSAdemoDlg ��Ϣ�������

BOOL CPSAdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//���߳�ʼ��
	g_pCalgorithmRegion = new CalgorithmRegion;
	vector<char*> dir;
	dir.push_back("../Pictures/Mark");
	//dir.push_back("../Pictures/1");
	//dir.push_back("../Pictures/2");
	//dir.push_back("../Pictures/3");
	//dir.push_back("../Pictures/4");
	g_pBmp = new HalconBmp(dir);

	//�½��㷨����
	g_pCalgorithmRegion->AddPro(L"ProgramDoc\\lin");  
	//�����㷨����
	g_pCalgorithmRegion->SetPro(L"ProgramDoc\\lin");

	//���еװ�ģ��
	m_AllModel.ResetContent();
	g_pCalgorithmRegion->GetDownModels(m_DownModels, DownParameter);
	for(int i = 0; i < m_DownModels.size(); i++)
	{
		m_AllModel.AddString(m_DownModels[i]);
	}
	m_AllModel.SetCurSel(0);
	//���صװ�ģ�����
	OnCbnSelchangeAllModel();

	g_ToolDown.SetWindow(GetDlgItem(IDC_STATIC_PIC));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPSAdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPSAdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPSAdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ȡͼ���߼�
void CPSAdemoDlg::OnBnClickedBtnGetpic()
{
	//��ȡͼ��
	HObject image;

	if(isRunPic)
	{
		CString path;
		g_pBmp->GetPic(0, image, path);
	}
	else
	{
		//�����ȡͼ��
	}

	USES_CONVERSION; 
	char* strChar = W2A(DownParameter.model_Path);
	try{
		WriteImage(image, "bmp", 0, strChar);
		g_ToolDown.ShowImage(image);
	}catch(...)
	{
		AfxMessageBox(L"��ȡͼƬʧ�ܣ�");
	}
}

//�༭ģ���߼�
void CPSAdemoDlg::OnBnClickedBtnEditmodel()
{
	//�༭ģ��
	UpdateData(true);
	HObject image;

	USES_CONVERSION; 
	char* strChar = W2A(DownParameter.model_Path);
	try{
		ReadImage(&image, strChar);
	}catch(...)
	{
		AfxMessageBox(L"���Ȼ�ȡͼ��");
		return;
	}
	CModelBuildDlg dlg(image, 0, DownParameter);
	dlg.DoModal();
	//�༭ģ��󣬱������һ����������
	if(!g_pCalgorithmRegion->SetDownModel(m_CurModel, DownParameter))
	{
		AfxMessageBox(L"���صװ�ģ��ʧ��");				
	}
}

//ʶ��ģ���߼�
void CPSAdemoDlg::OnBnClickedBtnFindmodel()
{
	//ʶ��ģ��
	HObject image;

	if(isRunPic)
	{
		CString path;
		g_pBmp->GetPic(0, image, path);
	}
	else
	{
		//�����ȡͼ��
	}

	vector<double> results;
	bool ret = g_pCalgorithmRegion->FindDownModel(g_ToolDown, image, results, DownParameter, g_SaveImage);
	if(isRunPic)
		g_ToolDown.ShowImage(image);

}


void CPSAdemoDlg::OnCbnSelchangeAllModel()
{
	CString strTemp;
	m_AllModel.GetWindowText(strTemp);
	//���صװ�ģ�����
	if(!g_pCalgorithmRegion->SetDownModel(strTemp, DownParameter))
	{
		AfxMessageBox(L"���صװ�ģ��ʧ��");				
	}
	else
	{
		m_CurModel = strTemp;
	}
	UpdateData(false);
}


void CPSAdemoDlg::OnBnClickedBtnAdd()
{
	//����ģ��
	UpdateData(true);
	//�½��װ�ģ��
	if(!g_pCalgorithmRegion->AddDownModel(m_AddName, DownParameter))
	{
		AfxMessageBox(L"�½��װ�ģ�������Ѵ���");	
	}
		
	//���еװ�ģ��
	m_AllModel.ResetContent();
	g_pCalgorithmRegion->GetDownModels(m_DownModels, DownParameter);
	for(int i = 0; i < m_DownModels.size(); i++)
	{
		m_AllModel.AddString(m_DownModels[i]);
	}
	m_AllModel.SetCurSel(0);
	//���صװ�ģ�����
	OnCbnSelchangeAllModel();
	m_AddName = L"";
	UpdateData(false);
}


void CPSAdemoDlg::OnBnClickedBtnDelete()
{
	//ɾ��ģ��
	UpdateData(true);
	if(!g_pCalgorithmRegion->DeleteDownModel(m_CurModel, DownParameter))
	{
		AfxMessageBox(L"ɾ���װ�ģ��ʧ��");	
	}

	//���еװ�ģ��
	m_AllModel.ResetContent();
	g_pCalgorithmRegion->GetDownModels(m_DownModels, DownParameter);
	for(int i = 0; i < m_DownModels.size(); i++)
	{
		m_AllModel.AddString(m_DownModels[i]);
	}
	m_AllModel.SetCurSel(0);
	//���صװ�ģ�����
	OnCbnSelchangeAllModel();
}
