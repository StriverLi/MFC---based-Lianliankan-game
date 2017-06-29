#pragma once
#include <iostream>
#include "afxwin.h"
#include "LLKDlg.h"
 
#define MAX_X 10 // 地图行数
#define MAX_Y 14  // 地图列数
#define IDC_BLOCK 100  // 按钮ID

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CPtrArray m_btnGroup; //Button 组,存放按钮

public:

	int m_typeNum = 16; // 图片种类
	int map[MAX_X][MAX_Y];
	int m_time; // 剩余时间，单位为秒

	void InitMap();  // 初始化地图
	void ShowMap(); // 将地图显示在窗口上
	void CGameDlg::OnCancel(); // 关闭窗口
	afx_msg void OnPaint(); // 绘制连线

	afx_msg void OnBnClickedBtnStsrt(); // 开始游戏

	//画路径时保存首尾结点
	CPoint pt1; 
	CPoint pt2;
	CPoint pt3;
	CPoint pt4;

	bool isRelax = false;

	// 计时器响应函数，用于檫除画的线
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 判断是否所通关
	bool IsFinished(); 

	// // 倒计时
	CStatic count;
	// 倒计时
	CString count_time;
	CStatic Time;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnPause();

	bool firstPause = false;; // 第一次按暂停按钮
	// 道具按钮
	CButton prop;
	// 积分按钮
	CButton range;
	CButton m_begin;
	CButton m_pause;
	CButton m_hint;
	CButton m_shuffle;
	afx_msg void OnBnClickedShuffle();
	afx_msg void OnBnClickedBtnHint();

	bool hintEnable = false;  // 提示按钮是否可用
	bool shuffleEnable = false; // 重排按钮是否可用
	bool propEnable = false; // 道具按钮是否可用
	bool clickPropBtn = false; // 点击道具按钮
	int propCount = 0; // 剩余道具数量
	int propSum = 0; // 总共获得的道具数量
	afx_msg void OnBnClickedBtnProp();
};
