#pragma once
#include "afxdialogex.h"
#include "LLKDlg.h"
#include "GameDlg.h"

// CLLKButton

class CLLKButton : public CButton
{
	DECLARE_DYNAMIC(CLLKButton)

public:
	CLLKButton();
	virtual ~CLLKButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int ID; //按钮的类型，即按钮上图片的类型
	CPoint location; //按钮对应在map中的位置
public:
	CLLKButton(int type, CPoint point);

	static CLLKButton* firstBtn; //第一次点中的按钮
	static CLLKButton* secondBtn; // 第二次点中的按钮

	// 两个拐点
	static CPoint conner1;
	static CPoint conner2;

	static CGameDlg* game;  //游戏窗口

	
	bool LinkInLine(CPoint p1, CPoint p2); // 一条直线消子
	bool OneCornerLink(CPoint p1, CPoint p2); // 两条直线消子
	bool TwoCornerLink(CPoint p1, CPoint p2); // 三条直线消子

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // 点击按钮响应函数

	//afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//void CLLKButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
//	virtual void CLLKButton::PreSubclassWindow();

};