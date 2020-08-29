#include "stdafx.h"
#include "CLift.h"
#include "Client.h"

CLift::CLift()
{
	Position = 1;//���ݴ���һ¥
	TargetFloor = 1;
	MovingDirection = 1;//�������з�������
	LiftDirection = false;//����ֹͣ
	DoorCodition = false;//�����Ź�
	number = 0;//���ݳ�ʼ����Ϊ0
}
void CLift::liftMovingDir(Client &c)//��������״̬ˢ��,����Ķ���Ϊ���ȷ��������źŵ��Ǹ���
{
	//����״̬ˢ��
	if (Position == 1 || Position < 1) MovingDirection = 1;//������ݵ�ǰΪ1¥�������з���Ϊ����
	else if (Position == 10 || Position > 10) MovingDirection = 0;//������ݵ�ǰΪ10¥�������з���Ϊ����
	else//��ǰ¥��Ϊ2-9¥
	{
		if (number == 0)//������ݴ�ʱ����,������ȷ���������ĳ˿�ȷ�����з��򣬷������з��򲻱�
		{
			if (c.Position > Position)MovingDirection = 1;//����ȷ�����������ڵ�������λ�õ����棬��������з���Ϊ��
			else if (c.Position < Position)MovingDirection = 0;//����ȷ�����������ڵ�������λ�õ����棬��������з���Ϊ��
			else    MovingDirection = c.MovingDirection;  //����ȷ���������˺͵��ݴ���ͬһλ��,���з�����ó˿���ͬ
		}
	}
}
void CLift::liftTargetFloor(Client &c)//����Ŀ��¥��
{
	//�������ƶ���������ʱ
	if (MovingDirection == 1)
	{
		if (c.bInLift == true)//����˿��ڵ�������
		{
			if (c.TargetFloor < TargetFloor)TargetFloor = c.TargetFloor;
		}
		else//����˿Ͳ��ڵ�����
		{
			//�����������ĳ˿��ڵ��ݵ��Ϸ������ͬʱ�ó˿͵����з�����������з�����ͬ
			if ((c.Position < TargetFloor) && (c.bSignal == true) && (c.MovingDirection == 1) && (c.Position > Position))TargetFloor = c.Position;
		}
	}

	//�������ƶ���������ʱ
	else if (MovingDirection == 0)
	{
		if (c.bInLift == true)//����˿��ڵ�������
		{
			if (c.TargetFloor > TargetFloor)TargetFloor = c.TargetFloor;
		}
		else
		{
			if ((c.Position > TargetFloor) && (c.bSignal == true) && (c.MovingDirection == 0) && (c.Position < Position))TargetFloor = c.Position;

		}
	}

}
//��������
void CLift::moving()
{
	while (Position != TargetFloor)
	{
		//��ʱһ��¥���ʱ��
		//������¥(��¥)����
		if (Position < TargetFloor) Position++;
		else Position--;
	}
}
CLift::~CLift()
{
}
