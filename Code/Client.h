#pragma once
#include "Floor.h"
#ifndef Client_H
#define Client_H
class Client
{
public:
	//数据成员
	int Position;    //所处楼层
	int TargetFloor;    //目标楼层
	int MovingDirection;    //前往方向,1为向上，0为向下
	bool bSignal;    //发出乘梯请求标志位 1为发出请求，0为未发出请求
	bool bInLift;    //乘客是否在电梯：1在电梯
	bool bStart;    //乘客是否完成了乘梯,0为完成了乘梯
	int Count;    //搭乘电梯次数
	//成员函数
	Client();    //无参数的构造函数
	void Copy(void);
	int inFloor(Floor &f, int);    //乘客出电梯进楼层并更新目标楼层
	int outFloor(Floor &f, int, int);    //乘客出楼层进电梯
	~Client();    //析构函数  
};
#endif

