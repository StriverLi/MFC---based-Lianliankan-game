
// LLKDlg.h : ͷ�ļ�
//

#pragma once


// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBasic(); // ����ģʽ
	afx_msg void OnBnClickedBtnRelax(); // ����ģʽ
	afx_msg void OnBnClickedBtnLevel(); // �ؿ�ģʽ
	afx_msg void OnBnClickedBtnRank();
	afx_msg void OnBnClickedBtnHelp();
};
