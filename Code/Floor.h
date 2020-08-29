#pragma once
#ifndef Floor_H
#define Floor_H
class Floor
{
public:
	//数据成员
	bool UpRingCondition;    //上楼灯状态
	bool DownRingCondition;    //下楼灯状态
	int NumGoup;    //上楼人数
	int NumGodown;    //下楼人数
	int number;//楼层里总人数
	//成员函数
	Floor();    //构造函数
	void Copy(void);
	void floor1(int);    //楼层一初始化，num为乘梯总人数
	~Floor();    //析构函数	
};
#endif
