#pragma once
#include "Floor.h"
#ifndef Client_H
#define Client_H
class Client
{
public:
	//���ݳ�Ա
	int Position;    //����¥��
	int TargetFloor;    //Ŀ��¥��
	int MovingDirection;    //ǰ������,1Ϊ���ϣ�0Ϊ����
	bool bSignal;    //�������������־λ 1Ϊ��������0Ϊδ��������
	bool bInLift;    //�˿��Ƿ��ڵ��ݣ�1�ڵ���
	bool bStart;    //�˿��Ƿ�����˳���,0Ϊ����˳���
	int Count;    //��˵��ݴ���
	//��Ա����
	Client();    //�޲����Ĺ��캯��
	void Copy(void);
	int inFloor(Floor &f, int);    //�˿ͳ����ݽ�¥�㲢����Ŀ��¥��
	int outFloor(Floor &f, int, int);    //�˿ͳ�¥�������
	~Client();    //��������  
};
#endif

