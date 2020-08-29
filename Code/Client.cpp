//Client��
#include "stdafx.h"
#include "Client.h"
#include "stdlib.h"
#include "Floor.h"

Client::Client()
{
	Position = 1;
	bSignal = true;
	bInLift = false;
	MovingDirection = 1;    //����
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
	MovingDirection = 1;    //����
	Count = 0;
	bStart = true;
	do
	{
		TargetFloor = rand() % 10 + 1;

	} while (Position == TargetFloor);
}
int Client::inFloor(Floor &f, int lifts)//�˿ͳ����ݽ�¥�㲢����Ŀ��¥��
{
	if (bInLift == true)
	{
		f.number++; //�ı�¥��������
		Count++;
		bInLift = false;//�˿�����λ�÷����ı� 
		Position = TargetFloor;//�ı�˿͵�ǰ¥��
		if (Count == (lifts + 1))
		{
			bStart = false;//��ɳ��ݱ�־
		}
		//����Ŀ��¥��
		if (bStart == true)//���ó˿�δ��ɳ���ʱ
		{
			if (Count < (lifts - 1))   //liftsΪ�趨�ĳ�������
			{
				do
				{
					TargetFloor = rand() % 10 + 1;

				} while (Position == TargetFloor);
			}
			else if (Count == lifts) TargetFloor = 1;//���һ��Ŀ��¥��Ϊ1
			else if (Count == (lifts - 1))//�����ڶ���Ŀ��¥�㲻��Ϊ��һ��
			{
				do
				{
					TargetFloor = rand() % 9 + 2;

				} while (Position == TargetFloor);
			}

			if (Position < TargetFloor) MovingDirection = 1;//�����˶�����
			else if (Position > TargetFloor)MovingDirection = 0;
		}
		return 1;
	}
	else
		return 0;
}
int Client::outFloor(Floor &f, int level, int moving)////�˿ͳ�¥�������
{
	if ((bInLift == false) && (bSignal == true) && (Position == level) && (MovingDirection == moving))
	{
		f.number--;//�ı�¥��������
		bInLift = true;//�ı�˿�����λ��
		bSignal = false;//ȡ���˿͵ĳ�������
		if (moving == 0) f.NumGodown--;//�ı���¥����¥����
		else f.NumGoup--;
		return 1;
	}
	else
		return 0;
}
Client::~Client()
{
}
