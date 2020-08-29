#pragma once
#include "afxwin.h"
#include "resource.h"


// CMainDlg �Ի���

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();


	void MoveUp();  //�������ϰ�ť
	void MoveDown(); //�������°�ť
	static void CALLBACK DoorTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);




// �Ի�������
	enum { IDD = IDD_MainDlg };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTimer();
	afx_msg void OnBnClickedReset();
	CStatic m_time;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void Lift_Bottom(int);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	/***********���沿��************/
	CBrush m_brBk;// ���ý��汳��
	CStatic m_bmpPic;
	CRect m_btnRT;
	CStatic m_lift;
	CStatic m_right;
	CRect m_btnlift;
	CRect m_btnright;

	POINT m_point;


	/*******************************/
	int num;
	int per_time;
	int lifts;
	int capacity;
	int lift_time;
	afx_msg void OnStnClickedBmpStatic();
	//afx_msg void OnStnClickedBitRight();
	afx_msg void OnBnClickedWait();

private:
	RECT m_rect;
	int perHeight; //ÿ��ĸ߶�
public:
	CString Operation;
};
#pragma once



