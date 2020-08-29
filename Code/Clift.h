#pragma once
#include "Client.h"
#ifndef CLift_H
#define CLift_H
class CLift
{
public:
	int  Position; //当前楼层
	int  TargetFloor; //目标楼层
	int  MovingDirection;//移动方向
	bool LiftDirection;//电梯当前状态 1 运行 0 停止
	bool DoorCodition;//电梯门的状态“1”为开门，“0”为关门
	int capitity;//电梯的容量
	int number;//电梯人数
	CLift();
	void liftMovingDir(Client &c);
	void liftTargetFloor(Client &c);
	void moving();
	~CLift();
};
#endif
