#pragma once
#include "afxwin.h"
#include "resource.h"


// CMainDlg 对话框

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();


	void MoveUp();  //设置向上按钮
	void MoveDown(); //设置向下按钮
	static void CALLBACK DoorTimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);




// 对话框数据
	enum { IDD = IDD_MainDlg };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	/***********界面部分************/
	CBrush m_brBk;// 设置界面背景
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
	int perHeight; //每层的高度
public:
	CString Operation;
};
#pragma once



