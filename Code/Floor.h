#pragma once
#ifndef Floor_H
#define Floor_H
class Floor
{
public:
	//���ݳ�Ա
	bool UpRingCondition;    //��¥��״̬
	bool DownRingCondition;    //��¥��״̬
	int NumGoup;    //��¥����
	int NumGodown;    //��¥����
	int number;//¥����������
	//��Ա����
	Floor();    //���캯��
	void Copy(void);
	void floor1(int);    //¥��һ��ʼ����numΪ����������
	~Floor();    //��������	
};
#endif
