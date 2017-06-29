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
	int ID; //��ť�����ͣ�����ť��ͼƬ������
	CPoint location; //��ť��Ӧ��map�е�λ��
public:
	CLLKButton(int type, CPoint point);

	static CLLKButton* firstBtn; //��һ�ε��еİ�ť
	static CLLKButton* secondBtn; // �ڶ��ε��еİ�ť

	// �����յ�
	static CPoint conner1;
	static CPoint conner2;

	static CGameDlg* game;  //��Ϸ����

	
	bool LinkInLine(CPoint p1, CPoint p2); // һ��ֱ������
	bool OneCornerLink(CPoint p1, CPoint p2); // ����ֱ������
	bool TwoCornerLink(CPoint p1, CPoint p2); // ����ֱ������

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // �����ť��Ӧ����

	//afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//void CLLKButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
//	virtual void CLLKButton::PreSubclassWindow();

};