
// LLKDlg.h : 头文件
//

#pragma once


// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBasic(); // 基本模式
	afx_msg void OnBnClickedBtnRelax(); // 休闲模式
	afx_msg void OnBnClickedBtnLevel(); // 关卡模式
	afx_msg void OnBnClickedBtnRank();
	afx_msg void OnBnClickedBtnHelp();
};
