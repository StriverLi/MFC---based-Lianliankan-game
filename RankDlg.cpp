// RankDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "RankDlg.h"
#include "afxdialogex.h"


// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRankDlg::IDD, pParent)
{

}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CRankDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCLEAR, &CRankDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_RADIO2, &CRankDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CRankDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序


BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CheckDlgButton(IDC_RADIO1, 1);

	m_list.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(2, _T("积分"), LVCFMT_CENTER, 70);
	

	//给列表加上表格
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

// 读取记录
void CRankDlg::ReadRecord()
{

	CStdioFile mFile;
	CFileException mExcept;
	CString readstr;
	CString IDstr;
	int i = 0;
	if (!mFile.Open(_T("record.txt"), CFile::modeRead, &mExcept))
		mFile.Open(_T("record.txt"), CFile::modeCreate | CFile::modeRead, &mExcept);
	CString name[10];
	int grade[10];
	//读出文件中的内容，并按积分排序
	while (mFile.ReadString(readstr))
	{
		name[i] = readstr;

		mFile.ReadString(readstr);
		int g = _ttoi(readstr);
		grade[i] = g;

		for (int j = 0; grade[j] > 0; j++) // 排序
		{
			if (grade[j] < grade[i])
			{
				CString temp = name[i];
				int te = grade[i];
				for (int k = i; k > 0; k--)
				{
					name[i] = name[i - 1];
					grade[i] = grade[i - 1];
				}
				name[j] = temp;
				grade[j] = te;
			}
		}

		i++;
	}
	// 写入列表
	m_list.DeleteAllItems();
	for (int i = 0; grade[i] > 0; i++)
	{
		IDstr.Format(_T("%d"), (i + 1));
		m_list.InsertItem(i, IDstr);
		m_list.SetItemText(i, 1, name[i]);
		CString str;
		str.Format(_T("%d"), grade[i]);
		m_list.SetItemText(i, 2,str);
	}
}


void CRankDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

// 清除记录
void CRankDlg::OnBnClickedClear()
{
	// TODO:  在此添加控件通知处理程序代码
	if (AfxMessageBox(_T("确定删除历史纪录"), MB_OKCANCEL) == IDOK)
	{
		m_list.DeleteAllItems();
		//清除文件纪录（重新创建一个同名文件）
		CFile mFile;
		CFileException mExcept;
		mFile.Open(_T("record.txt"), CFile::modeCreate, &mExcept);
	}
}

// 关卡模式排行榜
void CRankDlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < 3; i++)
	{
		m_list.DeleteColumn(0);
	}
	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("关卡数"), LVCFMT_CENTER, 70);


	//给列表加上表格
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();
}

// 休闲模式排行榜
void CRankDlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < 3; i++)
	{
		m_list.DeleteColumn(0);
	}

	m_list.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("积分"), LVCFMT_CENTER, 70);


	//给列表加上表格
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();
}
