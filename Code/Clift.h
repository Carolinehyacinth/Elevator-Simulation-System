#pragma once
#include "Client.h"
#ifndef CLift_H
#define CLift_H
class CLift
{
public:
	int  Position; //��ǰ¥��
	int  TargetFloor; //Ŀ��¥��
	int  MovingDirection;//�ƶ�����
	bool LiftDirection;//���ݵ�ǰ״̬ 1 ���� 0 ֹͣ
	bool DoorCodition;//�����ŵ�״̬��1��Ϊ���ţ���0��Ϊ����
	int capitity;//���ݵ�����
	int number;//��������
	CLift();
	void liftMovingDir(Client &c);
	void liftTargetFloor(Client &c);
	void moving();
	~CLift();
};
#endif
