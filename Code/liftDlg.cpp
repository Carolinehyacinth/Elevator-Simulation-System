
// liftDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "lift.h"
#include "liftDlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"

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


// CliftDlg �Ի���



CliftDlg::CliftDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CliftDlg::IDD, pParent)
	, capacity(0)
	, num(0) 
	, lifts(0)
	, lift_time(0)
	, per_time(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CliftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, num_txt_1, num);
	DDX_Text(pDX, capacity_txt_1, capacity);
	DDX_Text(pDX, lift_time_txt_1, lift_time);
	DDX_Text(pDX, lifts_txt_1, lifts);
	DDX_Text(pDX, num_txt_1, num);
	DDX_Text(pDX, per_time_txt_1, per_time);
}

BEGIN_MESSAGE_MAP(CliftDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CliftDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CliftDlg ��Ϣ�������

BOOL CliftDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CliftDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CliftDlg::OnPaint()
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
HCURSOR CliftDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CliftDlg::OnBnClickedOk()
{
	//���ȷ��
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);    //��ȡ����
	if (capacity > 9 && capacity < 21 && num > 20 && lifts > 2 && lifts < 11 )
	{
		if (lift_time > 0 && lift_time < 6 && per_time > 1 && per_time < 11)
		{
			this->ShowWindow(SW_HIDE);//��ǰ��������
			CMainDlg dlg;   //��Ҫ��Ӹ�C***Dlg.hͷ�ļ����������ͨ����
			dlg.capacity = capacity;
			dlg.num = num;
			dlg.lifts = lifts;
			dlg.lift_time = lift_time;
			dlg.per_time = per_time;
			dlg.DoModal();
			this->ShowWindow(SW_SHOW);
		}
		else
		{
			AfxMessageBox(_T("��������ʵĵ��ݷ��������"));
		}
	}
	else
	{
		AfxMessageBox(_T("��������ʵĵ��ݷ��������"));
	}
	
}

