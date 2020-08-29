//Client类
#include "stdafx.h"
#include "Client.h"
#include "stdlib.h"
#include "Floor.h"

Client::Client()
{
	Position = 1;
	bSignal = true;
	bInLift = false;
	MovingDirection = 1;    //向上
	Count = 0;
	bStart = true;
	do
	{
		TargetFloor = rand() % 10 + 1;

	} while (Position == TargetFloor);
}
void Client::Copy(void)
{
	Position = 1;
	bSignal = true;
	bInLift = false;
	MovingDirection = 1;    //向上
	Count = 0;
	bStart = true;
	do
	{
		TargetFloor = rand() % 10 + 1;

	} while (Position == TargetFloor);
}
int Client::inFloor(Floor &f, int lifts)//乘客出电梯进楼层并更新目标楼层
{
	if (bInLift == true)
	{
		f.number++; //改变楼层总人数
		Count++;
		bInLift = false;//乘客所处位置发生改变 
		Position = TargetFloor;//改变乘客当前楼层
		if (Count == (lifts + 1))
		{
			bStart = false;//完成乘梯标志
		}
		//更新目标楼层
		if (bStart == true)//当该乘客未完成乘梯时
		{
			if (Count < (lifts - 1))   //lifts为设定的乘坐次数
			{
				do
				{
					TargetFloor = rand() % 10 + 1;

				} while (Position == TargetFloor);
			}
			else if (Count == lifts) TargetFloor = 1;//最后一次目标楼层为1
			else if (Count == (lifts - 1))//倒数第二次目标楼层不能为第一层
			{
				do
				{
					TargetFloor = rand() % 9 + 2;

				} while (Position == TargetFloor);
			}

			if (Position < TargetFloor) MovingDirection = 1;//更新运动方向
			else if (Position > TargetFloor)MovingDirection = 0;
		}
		return 1;
	}
	else
		return 0;
}
int Client::outFloor(Floor &f, int level, int moving)////乘客出楼层进电梯
{
	if ((bInLift == false) && (bSignal == true) && (Position == level) && (MovingDirection == moving))
	{
		f.number--;//改变楼层总人数
		bInLift = true;//改变乘客所处位置
		bSignal = false;//取消乘客的乘梯请求
		if (moving == 0) f.NumGodown--;//改变上楼或下楼人数
		else f.NumGoup--;
		return 1;
	}
	else
		return 0;
}
Client::~Client()
{
}
