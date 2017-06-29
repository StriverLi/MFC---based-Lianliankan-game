#pragma once


// CHelp 对话框

class CHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHelp();

// 对话框数据
	enum { IDD = IDD_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ixoldpos = 0;
	int m_iyoldpos = 0;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
