#pragma once
#include "afxcmn.h"


// CRankDlg �Ի���

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRankDlg();

// �Ի�������
	enum { IDD = IDD_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
