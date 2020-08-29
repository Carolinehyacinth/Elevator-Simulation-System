#include "stdafx.h"
#include "Floor.h"
Floor::Floor()
{
	UpRingCondition = false;
	DownRingCondition = false;
	NumGoup = 0;
	NumGodown = 0;
	number = 0;
}
void Floor::Copy(void)
{
	UpRingCondition = false;
	DownRingCondition = false;
	NumGoup = 0;
	NumGodown = 0;
	number = 0;
}
void Floor::floor1(int num)//楼层一初始化，num为乘梯总人数
{
	UpRingCondition = true;
	DownRingCondition = false;
	NumGoup = num;
	NumGodown = 0;
	number = num;
}
Floor::~Floor()
{
}
