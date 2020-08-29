
// liftDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "lift.h"
#include "liftDlg.h"
#include "afxdialogex.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CliftDlg 对话框



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


// CliftDlg 消息处理程序

BOOL CliftDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CliftDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CliftDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CliftDlg::OnBnClickedOk()
{
	//点击确定
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);    //获取数据
	if (capacity > 9 && capacity < 21 && num > 20 && lifts > 2 && lifts < 11 )
	{
		if (lift_time > 0 && lift_time < 6 && per_time > 1 && per_time < 11)
		{
			this->ShowWindow(SW_HIDE);//当前界面隐藏
			CMainDlg dlg;   //需要添加该C***Dlg.h头文件，否则编译通不过
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
			AfxMessageBox(_T("请输入合适的电梯仿真参数！"));
		}
	}
	else
	{
		AfxMessageBox(_T("请输入合适的电梯仿真参数！"));
	}
	
}

