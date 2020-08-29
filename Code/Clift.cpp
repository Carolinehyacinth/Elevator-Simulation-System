#include "stdafx.h"
#include "CLift.h"
#include "Client.h"

CLift::CLift()
{
	Position = 1;//电梯处在一楼
	TargetFloor = 1;
	MovingDirection = 1;//电梯运行方向向上
	LiftDirection = false;//电梯停止
	DoorCodition = false;//电梯门关
	number = 0;//电梯初始人数为0
}
void CLift::liftMovingDir(Client &c)//电梯运行状态刷新,这里的对象为最先发出乘梯信号的那个人
{
	//运行状态刷新
	if (Position == 1 || Position < 1) MovingDirection = 1;//如果电梯当前为1楼，则运行方向为向上
	else if (Position == 10 || Position > 10) MovingDirection = 0;//如果电梯当前为10楼，则运行方向为向下
	else//当前楼层为2-9楼
	{
		if (number == 0)//如果电梯此时空载,则根据先发乘梯请求的乘客确定运行方向，否则运行方向不变
		{
			if (c.Position > Position)MovingDirection = 1;//如果先发出请求的人在电梯所处位置的上面，则电梯运行方向为上
			else if (c.Position < Position)MovingDirection = 0;//如果先发出请求的人在电梯所处位置的下面，则电梯运行方向为下
			else    MovingDirection = c.MovingDirection;  //如果先发出请求的人和电梯处于同一位置,运行方向与该乘客相同
		}
	}
}
void CLift::liftTargetFloor(Client &c)//更新目标楼层
{
	//当电梯移动方向向上时
	if (MovingDirection == 1)
	{
		if (c.bInLift == true)//如果乘客在电梯里面
		{
			if (c.TargetFloor < TargetFloor)TargetFloor = c.TargetFloor;
		}
		else//如果乘客不在电梯里
		{
			//如果发出请求的乘客在电梯的上方最近处同时该乘客的运行方向与电梯运行方向相同
			if ((c.Position < TargetFloor) && (c.bSignal == true) && (c.MovingDirection == 1) && (c.Position > Position))TargetFloor = c.Position;
		}
	}

	//当电梯移动方向向下时
	else if (MovingDirection == 0)
	{
		if (c.bInLift == true)//如果乘客在电梯里面
		{
			if (c.TargetFloor > TargetFloor)TargetFloor = c.TargetFloor;
		}
		else
		{
			if ((c.Position > TargetFloor) && (c.bSignal == true) && (c.MovingDirection == 0) && (c.Position < Position))TargetFloor = c.Position;

		}
	}

}
//电梯运行
void CLift::moving()
{
	while (Position != TargetFloor)
	{
		//延时一个楼层的时间
		//电梯上楼(下楼)动画
		if (Position < TargetFloor) Position++;
		else Position--;
	}
}
CLift::~CLift()
{
}
