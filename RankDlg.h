#pragma once
#include "afxcmn.h"


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRankDlg();

// 对话框数据
	enum { IDD = IDD_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;

	void ReadRecord();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClear(); 
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
