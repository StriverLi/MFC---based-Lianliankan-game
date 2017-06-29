// RankDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "RankDlg.h"
#include "afxdialogex.h"


// CRankDlg �Ի���

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


// CRankDlg ��Ϣ�������


BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CheckDlgButton(IDC_RADIO1, 1);

	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("�������"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(2, _T("����"), LVCFMT_CENTER, 70);
	

	//���б���ϱ��
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// ��ȡ��¼
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
	//�����ļ��е����ݣ�������������
	while (mFile.ReadString(readstr))
	{
		name[i] = readstr;

		mFile.ReadString(readstr);
		int g = _ttoi(readstr);
		grade[i] = g;

		for (int j = 0; grade[j] > 0; j++) // ����
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
	// д���б�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

// �����¼
void CRankDlg::OnBnClickedClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (AfxMessageBox(_T("ȷ��ɾ����ʷ��¼"), MB_OKCANCEL) == IDOK)
	{
		m_list.DeleteAllItems();
		//����ļ���¼�����´���һ��ͬ���ļ���
		CFile mFile;
		CFileException mExcept;
		mFile.Open(_T("record.txt"), CFile::modeCreate, &mExcept);
	}
}

// �ؿ�ģʽ���а�
void CRankDlg::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < 3; i++)
	{
		m_list.DeleteColumn(0);
	}
	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("�������"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("�ؿ���"), LVCFMT_CENTER, 70);


	//���б���ϱ��
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();
}

// ����ģʽ���а�
void CRankDlg::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < 3; i++)
	{
		m_list.DeleteColumn(0);
	}

	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, _T("�������"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("����"), LVCFMT_CENTER, 70);


	//���б���ϱ��
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)lStyle);

	ReadRecord();
}
