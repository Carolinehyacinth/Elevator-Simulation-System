// MainDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "lift.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "liftDlg.h"
#include "Client.h"
#include "Floor.h"
#include "CLift.h"


bool bStart, bWait,LiftGo,DoorOff;
int i, j, k;
int number;
int bSignalNum;//发出乘梯请求的人数
int signal[100];//用来存放发出请求信号的先后顺序
int a,go_time;
Floor floors[10];
Client passenger[100];
CLift lift;
CString print_out;

//背景全局变量
CRect rDoorRect;
BOOL Closed = 1; //门已关闭
int countup = 0; //上楼动画参数
int countdown = 0;//下楼动画参数       
int count = 0;//下楼动画参数        
int LEFT = 0;
int RIGHT = 0;
int mm = 0;
int ss = 0; 
int ms = 0;

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, capacity(0)
	, num(0)
	, lifts(0)
	, lift_time(0)
	, per_time(0)
	, Operation(_T(""))
{

}

CMainDlg::~CMainDlg()
{}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TimeDis, m_time);
	DDX_Control(pDX, IDC_BMP_STATIC, m_bmpPic);
	DDX_Control(pDX, IDC_BIT_LIFT, m_lift);
	DDX_Control(pDX, IDC_BIT_RIGHT, m_right);
	DDX_Text(pDX, num_txt, num);
	DDX_Text(pDX, per_time_txt, per_time);
	DDX_Text(pDX, lifts_txt, lifts);
	DDX_Text(pDX, capacity_txt, capacity);
	DDX_Text(pDX, lift_time_txt, lift_time);
	DDX_Text(pDX, light_down_10, floors[9].NumGodown);
	DDX_Text(pDX, light_up_9, floors[8].NumGoup);
	DDX_Text(pDX, light_down_9, floors[8].NumGodown);
	DDX_Text(pDX, light_up_8, floors[7].NumGoup);
	DDX_Text(pDX, light_down_8, floors[7].NumGodown);
	DDX_Text(pDX, light_up_7, floors[6].NumGoup);
	DDX_Text(pDX, light_down_7, floors[6].NumGodown);
	DDX_Text(pDX, light_up_6, floors[5].NumGoup);
	DDX_Text(pDX, light_down_6, floors[5].NumGodown);
	DDX_Text(pDX, light_up_5, floors[4].NumGoup);
	DDX_Text(pDX, light_down_5, floors[4].NumGodown);
	DDX_Text(pDX, light_up_4, floors[3].NumGoup);
	DDX_Text(pDX, light_down_4, floors[3].NumGodown);
	DDX_Text(pDX, light_up_3, floors[2].NumGoup);
	DDX_Text(pDX, light_down_3, floors[2].NumGodown);
	DDX_Text(pDX, light_up_2, floors[1].NumGoup);
	DDX_Text(pDX, light_down_2, floors[1].NumGodown);
	DDX_Text(pDX, light_up_1, floors[0].NumGoup);
	DDX_Text(pDX, lift_Position_txt, lift.Position);
	DDX_Text(pDX, lift_number_txt, lift.number);
	DDX_Text(pDX, people1, floors[0].number);
	DDX_Text(pDX, people2, floors[1].number);
	DDX_Text(pDX, people3, floors[2].number);
	DDX_Text(pDX, people4, floors[3].number);
	DDX_Text(pDX, people5, floors[4].number);
	DDX_Text(pDX, people6, floors[5].number);
	DDX_Text(pDX, people7, floors[6].number);
	DDX_Text(pDX, people8, floors[7].number);
	DDX_Text(pDX, people9, floors[8].number);
	DDX_Text(pDX, people10, floors[9].number);
	DDX_Text(pDX, lift_operation, Operation);
	//DDX_Text(pDX, IDC_target, lift.TargetFloor); 
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_Timer, &CMainDlg::OnBnClickedTimer)
	ON_BN_CLICKED(IDC_Reset, &CMainDlg::OnBnClickedReset)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Wait, &CMainDlg::OnBnClickedWait)
END_MESSAGE_MAP()

/******************
  窗口初始化函数
***************/
BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
    // TODO:  在此添加额外的初始化
	//背景
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BACK);
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	//因为是每次都是动态加载  所以要放到这里
	m_bmpPic.GetClientRect(&m_btnRT);
	m_bmpPic.ClientToScreen(m_btnRT);
	ScreenToClient(m_btnRT);

	//文本框输出
	UpdateData(false);
	lift.capitity = capacity;
	floors[0].floor1(num);//楼层一初始化
	bSignalNum = num;//初始时发出请求的人数为总人数
	number = num;
	Operation = "停止";
	for (i = 0; i < num; i++)
	{
		signal[i] = i;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMainDlg::OnBnClickedTimer()
{// TODO: 在此添加控件通知处理程序代码
	bStart = true;
	Operation = "运行";
	bWait = false;
	num = number;
	for (i = 0; i < num; i++)
	{
		passenger[i].Copy();
		signal[i] = i;
	}
	for (i = 1; i < 10; i++)
	{
		floors[i].Copy();
		Lift_Bottom(i);
	}
	floors[0].floor1(num);
	Lift_Bottom(0);
	bSignalNum = num;
	lift.number = 0;
	go_time = 0;
	mm = 0;
	ss = 0;
	ms = 0;
	UpdateData(false);
	SetTimer(1, 10, NULL);//负责定时器
	while (bStart == true)
	{
		while (bWait)
		{
			KillTimer(1);
			MSG   msg;
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			Operation = "暂停";
			UpdateData(false);
		}
		Operation = "运行";
		if (num!= 0)
		{
			if (lift.Position == lift.TargetFloor)//已到达目标楼层
			{
				lift.LiftDirection = false;//电梯停止移动
				lift.DoorCodition = true;
				DoorOff = false;
				SetTimer(4, 10, NULL);//开门动画
				while (DoorOff == false)
				{
					MSG   msg;
					while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					UpdateData(false);
				}
				go_time++;
				//乘客发出乘梯请求并且更新信号队列（入队）,更新楼层的灯和上下的人数
				for (i = 0; i < num; i++)//产生num个人来发信号
				{
					a = rand() % number;//产生一个随机数,该随机数小于总人数
					if ((passenger[a].bInLift == false) && (passenger[a].bSignal == false) && (passenger[a].bStart == true))//如果该乘客不在电梯内且未发出乘梯信号、未完成乘梯次数
					{
						passenger[a].bSignal = true;//楼层中的乘客发出乘梯请求
						bSignalNum++;//更新请求乘梯队列个数
						signal[bSignalNum - 1] = a;//乘客序号进入请求乘梯队列
						//更新楼层灯的状态以及请求上楼下楼的人数
						if (passenger[a].MovingDirection == 1)//如果该乘客的请求方向向上
						{
							floors[passenger[a].Position - 1].NumGoup++;//该乘客所处楼层上楼人数加1
							floors[passenger[a].Position - 1].UpRingCondition = true;//该乘客所处楼层上楼灯亮
						}
						else
						{
							floors[passenger[a].Position - 1].NumGodown++;//该乘客所处楼层下楼人数加1
							floors[passenger[a].Position - 1].DownRingCondition = true;//该乘客所处楼层下楼灯亮	
						}
						Lift_Bottom(passenger[a].Position - 1);
					}
				}
				if (bSignalNum == 0)//当没有乘客发信号时,产生一个发信号的乘客，防止进入死循环
				{
					for (i = 0; i < number; i++)
					{
						if ((passenger[i].bInLift == false) && (passenger[i].bSignal == false) && (passenger[i].bStart == true))//该乘客未完成乘梯
						{
							passenger[i].bSignal = true;
							bSignalNum++;
							signal[bSignalNum - 1] = i;
							break;
						}
					}
					//更新楼层灯的状态以及请求上楼下楼的人数
					if (passenger[i].MovingDirection == 1)//如果该乘客的请求方向向上
					{
						floors[passenger[i].Position - 1].NumGoup++;//该乘客所处楼层上楼人数加1
						floors[passenger[i].Position - 1].UpRingCondition = true;//该乘客所处楼层上楼灯亮
					}
					else
					{
						floors[passenger[i].Position - 1].NumGodown++;//该乘客所处楼层下楼人数加1
						floors[passenger[i].Position - 1].DownRingCondition = true;//该乘客所处楼层下楼灯亮
					}
					Lift_Bottom(passenger[i].Position - 1);
				}
				for (i = 0; i < number; i++) //乘客离开电梯进入楼层，生成新的目标楼层
				{
					if (passenger[i].TargetFloor == lift.Position)
					{
						if (passenger[i].inFloor(floors[lift.Position - 1], lifts))
						{
							lift.number--;//改变电梯总人数
							go_time = go_time + per_time;
							while (mm * 60 + ss < go_time)
							{
								MSG   msg;
								while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
								{
									TranslateMessage(&msg);
									DispatchMessage(&msg);
								}
								UpdateData(false);
							}
							if (passenger[i].bStart == false) num--;
						}
					}
				}
				i = signal[0];//找出最先发出乘梯信号的那个人
				lift.liftMovingDir(passenger[i]);//电梯运行方向刷新（仅在顶、底层或空载时）
				MSG   msg;
				while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				for (i = 0; i < number; i++)//乘客离开楼层进入电梯
				{
					if (lift.number < lift.capitity)
					{
						if (passenger[i].outFloor(floors[lift.Position - 1], lift.Position, lift.MovingDirection))
						{
							lift.number++;
							go_time = go_time + per_time;
							while (mm * 60 + ss < go_time)
							{
								MSG   msg;
								while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
								{
									TranslateMessage(&msg);
									DispatchMessage(&msg);
								}
								UpdateData(false);
							}
						}
					}
				}
				//因为有人出楼层了，所以需要更新请求乘梯信号队列
				j = bSignalNum;
				for (i = 0; i < j;i++)
				{
					if (passenger[signal[i]].bInLift == true)
					{
						bSignalNum--;
						for (k = i; k < bSignalNum; k++)//队列中删除一个数，其他数往前移
						{
							signal[k] = signal[k + 1];
						}
					}
				}
				//***************更新楼层灯(只更新当前楼层）*************

				if (floors[lift.Position - 1].NumGodown == 0)
				{
					floors[lift.Position - 1].DownRingCondition = false;
				}
				else
				{
					floors[lift.Position - 1].DownRingCondition = true;
				}

				if (floors[lift.Position - 1].NumGoup == 0)
				{
					floors[lift.Position - 1].UpRingCondition = false;
				}
				else
				{
					floors[lift.Position - 1].UpRingCondition = true;
				}
				Lift_Bottom(lift.Position - 1);
				//***************更新目标楼层**************
				//if (lift.Position == 1 || lift.Position < 1) lift.MovingDirection = 1;//如果电梯当前为1楼，则运行方向为向上
				//else if (lift.Position == 10 || lift.Position > 10) lift.MovingDirection = 0;//如果电梯当前为10楼，则运行方向为向下
				if (lift.MovingDirection == 1) lift.TargetFloor = 10;
				else if(lift.MovingDirection == 0) lift.TargetFloor = 1;

				for (i = 0; i < number; i++) lift.liftTargetFloor(passenger[i]);//更新目标楼层
				lift.DoorCodition = false;
				DoorOff = false;
				SetTimer(5, 10, NULL);//关门动画
				while (DoorOff == false)
				{
					MSG   msg;
					while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					UpdateData(false);
				}
				go_time++;
				lift.LiftDirection = true;//电梯当前状态为运行状态
			}
			if (num != 0)
			{
				if (lift.MovingDirection == 1)
				{
					LiftGo = true;
					SetTimer(2, 16 * lift_time, NULL);
					lift.Position++;
					while (LiftGo == true)
					{
						MSG   msg;
						while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
						UpdateData(false);
					}
					go_time = go_time + lift_time;
				}
				else if (lift.MovingDirection == 0)
				{
					LiftGo = true;
					SetTimer(3, 16 * lift_time, NULL);
					lift.Position--;
					while (LiftGo == true)
					{
						MSG   msg;
						while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
						UpdateData(false);
					}
					go_time = go_time + lift_time;
				}
			}
		}
		else if (num == 0)
		{
			bStart = false;//如果所有人完成了乘梯，则结束仿真
			KillTimer(1);
		}
		UpdateData(false);
		MSG   msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	print_out.Format(_T("仿真结束！共花费%02i分%02i秒"), mm, ss);
	AfxMessageBox(print_out);

}

void CMainDlg::OnBnClickedWait()
{
	if (bWait == false)
	{
		bWait = true;
	}
	else
	{
		bWait = false;
		Operation = "运行";
		SetTimer(1, 10, NULL);
	}
}

void CMainDlg::OnBnClickedReset()
{
	bStart = false;
	Operation = "停止";
	KillTimer(1);
}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	switch (nIDEvent)
	{
//界面计时器
	case 1:
	{
		ms = ms+1;
		if (ms == 100) { ms = 0; ss++; }
		if (ss == 60) { ss = 0; mm++; }
		str.Format(_T("%02i:%02i:%02i"), mm, ss, ms);
		m_time.SetWindowTextW(str);
	}
	break;
	case 2://电梯上升
	{
		KillTimer(3);
		CRect btnRT; //获取图片的原始坐标
		m_bmpPic.GetClientRect(&btnRT);//将其转换为DLG坐标
		m_bmpPic.ClientToScreen(btnRT);
		ScreenToClient(btnRT);
		
		m_bmpPic.MoveWindow(btnRT.left, btnRT.top - 1, btnRT.Width(), btnRT.Height(), TRUE);//移动图片
		countup++;
		//当图的底部移出窗口的时候,将图片设置为原始坐标点  
		if (countup >= 62)
		{
			KillTimer(2);
			LiftGo = false;
			countup = 0;
		}
	}
	break;
	case 3://电梯下降
	{
		KillTimer(2);
		KillTimer(4);
		KillTimer(5);
		CRect btnRT1; //获取图片的原始坐标
		m_bmpPic.GetClientRect(&btnRT1);//将其转换为DLG坐标
		m_bmpPic.ClientToScreen(btnRT1);
		ScreenToClient(btnRT1);
		
		m_bmpPic.MoveWindow(btnRT1.left, btnRT1.top + 1, btnRT1.Width(), btnRT1.Height(), TRUE);//移动图片
		countdown ++;
		//当图的底部移出窗口的时候,将图片设置为原始坐标点  
		if (countdown >= 62)
		{
			KillTimer(3);
			LiftGo = false;
			countdown = 0;
		}
	}
	break;

	case 4://电梯开门
	{
		
		KillTimer(2);
		KillTimer(3);
		KillTimer(5);
		CRect btnLIFT;
		CRect btnRIGHT; //获取图片的原始坐标
		GetDlgItem(IDC_BIT_LIFT)->GetWindowRect(btnLIFT);
		GetDlgItem(IDC_BIT_RIGHT)->GetWindowRect(btnRIGHT);
		ScreenToClient(btnLIFT);
		ScreenToClient(btnRIGHT);
		
		
		if (btnLIFT.Width() == 2)
		{
			KillTimer(4);
			DoorOff = true;
		}
		else
		{
			GetDlgItem(IDC_BIT_LIFT)->SetWindowPos(NULL, btnLIFT.left, btnLIFT.top, btnLIFT.Width() - 1, btnLIFT.Height(), SWP_NOZORDER | SWP_NOMOVE);
			GetDlgItem(IDC_BIT_RIGHT)->SetWindowPos(NULL, btnRIGHT.left + 1, btnRIGHT.top, btnRIGHT.Width() - 1, btnRIGHT.Height(), SWP_NOZORDER);
		}
		Closed = 0;
	}

	break;

	case 5:
		//电梯关门
	{
		
		KillTimer(2);
		KillTimer(3);
		KillTimer(4);
		CRect btnLIFT;
		CRect btnRIGHT; //获取图片的原始坐标
		GetDlgItem(IDC_BIT_LIFT)->GetWindowRect(btnLIFT);
		GetDlgItem(IDC_BIT_RIGHT)->GetWindowRect(btnRIGHT);
		ScreenToClient(btnLIFT);
		ScreenToClient(btnRIGHT);
		count++;
		GetDlgItem(IDC_BIT_LIFT)->SetWindowPos(NULL, btnLIFT.left, btnLIFT.top, btnLIFT.Width() + 1, btnLIFT.Height(), SWP_NOZORDER | SWP_NOMOVE);
		GetDlgItem(IDC_BIT_RIGHT)->SetWindowPos(NULL, btnRIGHT.left - 1, btnRIGHT.top, btnLIFT.Width() + 1, btnRIGHT.Height(), SWP_NOZORDER);	
		if (count >= 71)
		{
			count = 0;
			KillTimer(5);
			DoorOff = true;
        }
		
		Closed = 1;
	}
	break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this)
	{
		return m_brBk;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
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


	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CMainDlg::Lift_Bottom(int i)
{
	if (lift.MovingDirection == 1)
	{
		GetDlgItem(IDB_UP0)->ShowWindow(true);
		GetDlgItem(IDB_DOWN0)->ShowWindow(false);
	}
	else if (lift.MovingDirection == 0)
	{
		GetDlgItem(IDB_UP0)->ShowWindow(false);
		GetDlgItem(IDB_DOWN0)->ShowWindow(true);
	}
	switch (i)
	{
	case 0:
	{
		if (floors[0].NumGoup == 0)
		{
			GetDlgItem(IDB_UP1)->ShowWindow(false);
		}
		else if (floors[0].NumGoup != 0)
		{
			GetDlgItem(IDB_UP1)->ShowWindow(true);
		}
	}
		break;
	case 1:
	{
		if (floors[1].NumGoup == 0)
		{
			GetDlgItem(IDB_UP2)->ShowWindow(false);
		}
		else if (floors[1].NumGoup != 0)
		{
			GetDlgItem(IDB_UP2)->ShowWindow(true);
		}
		if (floors[1].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN2)->ShowWindow(false);
		}
		else if (floors[1].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN2)->ShowWindow(true);
		}
	}
		break;
	case 2:
	{
		if (floors[2].NumGoup == 0)
		{
			GetDlgItem(IDB_UP3)->ShowWindow(false);
		}
		else if (floors[2].NumGoup != 0)
		{
			GetDlgItem(IDB_UP3)->ShowWindow(true);
		}
		if (floors[2].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN3)->ShowWindow(false);
		}
		else if (floors[2].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN3)->ShowWindow(true);
		}
	}
		break;
	case 3:
	{
		if (floors[3].NumGoup == 0)
		{
			GetDlgItem(IDB_UP4)->ShowWindow(false);
		}
		else if (floors[3].NumGoup != 0)
		{
			GetDlgItem(IDB_UP4)->ShowWindow(true);
		}
		if (floors[3].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN4)->ShowWindow(false);
		}
		else if (floors[3].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN4)->ShowWindow(true);
		}
	}
		break;
	case 4:
	{
		if (floors[4].NumGoup == 0)
		{
			GetDlgItem(IDB_UP5)->ShowWindow(false);
		}
		else if (floors[4].NumGoup != 0)
		{
			GetDlgItem(IDB_UP5)->ShowWindow(true);
		}
		if (floors[4].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN5)->ShowWindow(false);
		}
		else if (floors[4].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN5)->ShowWindow(true);
		}
	}
		break;
	case 5:
	{
		if (floors[5].NumGoup == 0)
		{
			GetDlgItem(IDB_UP6)->ShowWindow(false);
		}
		else if (floors[5].NumGoup != 0)
		{
			GetDlgItem(IDB_UP6)->ShowWindow(true);
		}
		if (floors[5].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN6)->ShowWindow(false);
		}
		else if (floors[5].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN6)->ShowWindow(true);
		}
	}
		break;
	case 6:
	{
		if (floors[6].NumGoup == 0)
		{
			GetDlgItem(IDB_UP7)->ShowWindow(false);
		}
		else if (floors[6].NumGoup != 0)
		{
			GetDlgItem(IDB_UP7)->ShowWindow(true);
		}
		if (floors[6].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN7)->ShowWindow(false);
		}
		else if (floors[6].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN7)->ShowWindow(true);
		}
	}
		break;
	case 7:
	{
		if (floors[7].NumGoup == 0)
		{
			GetDlgItem(IDB_UP8)->ShowWindow(false);
		}
		else if (floors[7].NumGoup != 0)
		{
			GetDlgItem(IDB_UP8)->ShowWindow(true);
		}
		if (floors[7].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN8)->ShowWindow(false);
		}
		else if (floors[7].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN8)->ShowWindow(true);
		}
	}
		break;
	case 8:
	{
		if (floors[8].NumGoup == 0)
		{
			GetDlgItem(IDB_UP9)->ShowWindow(false);
		}
		else if (floors[8].NumGoup != 0)
		{
			GetDlgItem(IDB_UP9)->ShowWindow(true);
		}
		if (floors[8].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN9)->ShowWindow(false);
		}
		else if (floors[8].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN9)->ShowWindow(true);
		}
	}
		break;
	case 9:
	{
		if (floors[9].NumGodown == 0)
		{
			GetDlgItem(IDB_DOWN10)->ShowWindow(false);
		}
		else if (floors[9].NumGodown != 0)
		{
			GetDlgItem(IDB_DOWN10)->ShowWindow(true);
		}
	}
		break;
	}
}