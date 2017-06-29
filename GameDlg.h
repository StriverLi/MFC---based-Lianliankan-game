#pragma once
#include <iostream>
#include "afxwin.h"
#include "LLKDlg.h"
 
#define MAX_X 10 // ��ͼ����
#define MAX_Y 14  // ��ͼ����
#define IDC_BLOCK 100  // ��ťID

// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CPtrArray m_btnGroup; //Button ��,��Ű�ť

public:

	int m_typeNum = 16; // ͼƬ����
	int map[MAX_X][MAX_Y];
	int m_time; // ʣ��ʱ�䣬��λΪ��

	void InitMap();  // ��ʼ����ͼ
	void ShowMap(); // ����ͼ��ʾ�ڴ�����
	void CGameDlg::OnCancel(); // �رմ���
	afx_msg void OnPaint(); // ��������

	afx_msg void OnBnClickedBtnStsrt(); // ��ʼ��Ϸ

	//��·��ʱ������β���
	CPoint pt1; 
	CPoint pt2;
	CPoint pt3;
	CPoint pt4;

	bool isRelax = false;

	// ��ʱ����Ӧ�����������߳�������
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// �ж��Ƿ���ͨ��
	bool IsFinished(); 

	// // ����ʱ
	CStatic count;
	// ����ʱ
	CString count_time;
	CStatic Time;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnPause();

	bool firstPause = false;; // ��һ�ΰ���ͣ��ť
	// ���߰�ť
	CButton prop;
	// ���ְ�ť
	CButton range;
	CButton m_begin;
	CButton m_pause;
	CButton m_hint;
	CButton m_shuffle;
	afx_msg void OnBnClickedShuffle();
	afx_msg void OnBnClickedBtnHint();

	bool hintEnable = false;  // ��ʾ��ť�Ƿ����
	bool shuffleEnable = false; // ���Ű�ť�Ƿ����
	bool propEnable = false; // ���߰�ť�Ƿ����
	bool clickPropBtn = false; // ������߰�ť
	int propCount = 0; // ʣ���������
	int propSum = 0; // �ܹ���õĵ�������
	afx_msg void OnBnClickedBtnProp();
};
