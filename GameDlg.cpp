// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "CLLKButton.h"

#include "atlimage.h";


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
	, count_time(_T(""))
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PROP, prop);
	DDX_Control(pDX, IDC_BTN_RANGE, range);
	DDX_Control(pDX, IDC_COUNT, count);
	DDX_Text(pDX, IDC_COUNT_TIME, count_time);
	DDX_Control(pDX, IDC_COUNT_TIME, Time);
	DDX_Control(pDX, IDC_BTN_STSRT, m_begin);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_pause);
	DDX_Control(pDX, IDC_BTN_HINT, m_hint);
	DDX_Control(pDX, IDC_SHUFFLE, m_shuffle);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BTN_STSRT, &CGameDlg::OnBnClickedBtnStsrt)
	ON_WM_TIMER()
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_SHUFFLE, &CGameDlg::OnBnClickedShuffle)
	ON_BN_CLICKED(IDC_BTN_HINT, &CGameDlg::OnBnClickedBtnHint)
	ON_BN_CLICKED(IDC_BTN_PROP, &CGameDlg::OnBnClickedBtnProp)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


// 初始化地图
void CGameDlg::InitMap() 
{
	for (int i = 0; i < MAX_X; i++) // 初始化map数组
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			map[i][j] = 0;
		}
	}

	//随机数种子
	srand((unsigned int)time(NULL));

	for (int i = 1; i < MAX_X - 1; i++)
	{
		for (int j = 1; j < MAX_Y - 1; j = j+2)
		{
			int type = rand() % m_typeNum + 1;// 随机产生一个的图片种类编号
			map[i][j] = type;
			map[i][j+1] = type; // 保证同种图片连续出现两次
		}
	}
	int k = 0;
	while (k < 100) // 随机选中两个位置交换100次
	{
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		while (x1 == x2 && y1 == y2) // 确保两个位置不同
		{
			x1 = rand() % (MAX_X - 2) + 1;
			y1 = rand() % (MAX_Y - 2) + 1;

			x2 = rand() % (MAX_X - 2) + 1;
			y2 = rand() % (MAX_Y - 2) + 1;
		}
		int temp = map[x1][y1];
		map[x1][y1] = map[x2][y2];
		map[x2][y2] = temp;
		k++;
	}
}

// 显示地图
void CGameDlg::ShowMap()
{
	int i, j;
	CPoint p; // 按钮位置
	CString str = _T("");
	//清除原有按钮
	for (i = 0; i<m_btnGroup.GetSize(); i++)
		delete (CLLKButton *)m_btnGroup.GetAt(i);
	m_btnGroup.RemoveAll();
	//添加新按钮
	for (i = 1; i <= MAX_X - 2; i++)
		for (j = 1; j <= MAX_Y - 2; j++)
		{
			p.x = i;
			p.y = j;
			//arr[map[i][j] - 1]++;
			//将按钮放入m_btnGroup指针数组中
			m_btnGroup.Add(new CLLKButton(map[i][j], p));
			 
		}
	//显示按钮
	for (i = 0; i<(MAX_X - 2)*(MAX_Y - 2); i++)
	{
		CLLKButton *btn = (CLLKButton *)m_btnGroup.GetAt(i);
		if (btn->ID > 0)
		{
			str.Format(_T("res\\%d.png"), btn->ID);

			CImage image;
			image.Load(str);

			btn->Create(str, WS_CHILD | BS_BITMAP | WS_VISIBLE,
				CRect(70 + (i % (MAX_Y - 2)) * 50, 70 + (i / (MAX_Y - 2)) * 50,
				120 + (i % (MAX_Y - 2)) * 50, 120 + (i / (MAX_Y - 2)) * 50), this,
				IDC_BLOCK + i);
			btn->SetBitmap(image);
			btn->ShowWindow(SW_SHOW);
		}
	}

	
}

// 开始游戏
void CGameDlg::OnBnClickedBtnStsrt()
{
	// TODO:  在此添加控件通知处理程序代码
	
	//如果不是休闲模式显示倒计时
	if (!isRelax)
	{
		m_time = 120;
		count.ShowWindow(SW_SHOW);
		Time.SetWindowTextW(_T("00 : 00 : 00"));
		Time.ShowWindow(SW_SHOW);
		SetTimer(2, 1000, NULL); // 设置计时器，每过一秒时间减一
		m_hint.EnableWindow(true);
		m_shuffle.EnableWindow(true);
	}

	InitMap();
	ShowMap();
	CLLKButton::game = this;
	m_pause.EnableWindow(true);
	range.EnableWindow(true);

}

// 关闭窗口时的事件
void CGameDlg::OnCancel() 
{
	CLLKDlg* parent = (CLLKDlg*)GetParent();
	parent->ShowWindow(SW_SHOW);  // 显示主窗口
	KillTimer(2);
	CDialogEx::OnCancel();
}

// 画线
void CGameDlg::OnPaint()
{
	CWindowDC dc2(this);
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	dc2.SelectObject(pen);

	//画出路径
	if (CLLKButton::firstBtn != NULL && CLLKButton::secondBtn != NULL)
	{
		//设置计时器，0.2秒后擦除路径线条
		SetTimer(1, 200, 0);
		pt1.x = CLLKButton::firstBtn->location.y * 50 + 45;
		pt1.y = CLLKButton::firstBtn->location.x * 50 + 70;
		pt2.x = CLLKButton::secondBtn->location.y * 50 + 45;
		pt2.y = CLLKButton::secondBtn->location.x * 50 + 70;
		pt3.x = CLLKButton::conner1.y * 50 + 45;
		pt3.y = CLLKButton::conner1.x * 50 + 70;
		pt4.x = CLLKButton::conner2.y * 50 + 45;
		pt4.y = CLLKButton::conner2.x * 50 + 70;

		//无拐点
		if (CLLKButton::conner1.x == -1)
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt2);
		}
		//一个拐点
		else if (CLLKButton::conner2.x == -1)
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt3);
			dc2.MoveTo(pt3);
			dc2.LineTo(pt2);
		}
		//两个拐点
		else
		{
			dc2.MoveTo(pt1);
			dc2.LineTo(pt3);
			dc2.MoveTo(pt3);
			dc2.LineTo(pt4);
			dc2.MoveTo(pt4);
			dc2.LineTo(pt2);
		}
	}
	
}

//响应计时器信号
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	if (nIDEvent == 1) // 消除连线
	{
		{
			CWindowDC dc2(this);
			//用背景色将路径再画一次  
			CPen pen(PS_SOLID, 5, RGB(200, 191, 231));
			dc2.SelectObject(pen);
			//无拐点
			if (CLLKButton::conner1.x == -1)
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt2);
			}
			//一个拐点
			else if (CLLKButton::conner2.x == -1)
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt3);
				dc2.MoveTo(pt3);
				dc2.LineTo(pt2);
			}
			//两个拐点
			else
			{
				dc2.MoveTo(pt1);
				dc2.LineTo(pt3);
				dc2.MoveTo(pt3);
				dc2.LineTo(pt4);
				dc2.MoveTo(pt4);
				dc2.LineTo(pt2);
			}
		}
		KillTimer(nIDEvent);
	}

	if (nIDEvent == 2 && !firstPause) // 倒计时
	{
		m_time--;
		int m = m_time / 60; // 分钟
		int s = m_time % 60; // 秒
		CString sm;
		CString ss;
		if (m > 9)
		{
			sm.Format(_T("%d"), m);
		}
		else if (m == 0)
		{
			sm = "00";
		}
		else
		{
			sm.Format(_T("%d%d"), 0, m);
		}
		if (s > 9)
		{
			ss.Format(_T("%d"), s);
		}
		else if (s == 0)
		{
			ss = "00";
		}
		else
		{
			ss.Format(_T("%d%d"), 0, s);
		}
		Time.SetWindowTextW(_T("00 : " + sm + " : " + ss));
		if (s == 0 && m == 0 && !IsFinished())
		{
			KillTimer(nIDEvent); // 关闭计时器
			MessageBox(_T("时间到，闯关失败"), _T("失败"));

			for (int i = 0; i < m_btnGroup.GetSize(); i++)
			{
				delete (CLLKButton *)m_btnGroup.GetAt(i);
			}
			m_btnGroup.SetSize(0);

			m_pause.EnableWindow(false);
			m_hint.EnableWindow(false);
			m_shuffle.EnableWindow(false);
			prop.EnableWindow(false);
			range.EnableWindow(false);
		}
		if (IsFinished())
		{
			m_pause.EnableWindow(false);
			m_hint.EnableWindow(false);
			m_shuffle.EnableWindow(false);
			prop.EnableWindow(false);
			range.EnableWindow(false);
			KillTimer(nIDEvent);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
	
}

// 判断是否通关
bool CGameDlg::IsFinished()
{
	bool b = true;
	for (int i = 1; i < MAX_X - 1; i++)
	{
		for (int j = 1; j < MAX_Y - 1; j++)
		{
			if (map[i][j] != 0)
			{
				b = false;
				break;
			}
		}
	}
	return b;
}

// 设置倒计时背景及字体
HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_COUNT || pWnd->GetDlgCtrlID() == IDC_COUNT_TIME)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(RGB(200, 191, 231));
	}
//	if (pWnd->GetDlgCtrlID() == 100)
//	{
//		pDC->SetBkColor(RGB(0, 255, 0));
//		pDC->SetTextColor(RGB(255, 0, 0));
//	}

	return hbr;
}

// 暂停
void CGameDlg::OnBnClickedBtnPause()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!firstPause) // 第一次点击暂停按钮
	{
		firstPause = true;
		for (int i = 0; i<(MAX_X - 2)*(MAX_Y - 2); i++)
		{
			CLLKButton *btn = (CLLKButton *)m_btnGroup.GetAt(i);
			if (btn->ID > 0)
				btn->ShowWindow(SW_HIDE);
			m_begin.EnableWindow(false);
			range.EnableWindow(false);
			m_hint.EnableWindow(false);
			m_shuffle.EnableWindow(false);
			prop.EnableWindow(false);
		}
		m_pause.SetWindowTextW(_T("继续游戏"));
	}
	else // 第二次点击暂停按钮
	{
		firstPause = false;
		for (int i = 0; i<(MAX_X - 2)*(MAX_Y - 2); i++)
		{
			CLLKButton *btn = (CLLKButton *)m_btnGroup.GetAt(i);
			if (btn->ID > 0)
				btn->ShowWindow(SW_SHOW);
			m_begin.EnableWindow(true);
			range.EnableWindow(true);
			m_hint.EnableWindow(hintEnable || !isRelax);
			m_shuffle.EnableWindow(shuffleEnable || !isRelax);
			prop.EnableWindow(propEnable);
		}
		m_pause.SetWindowTextW(_T("暂停游戏"));
	}
}

// 重排
void CGameDlg::OnBnClickedShuffle()
{
	// TODO:  在此添加控件通知处理程序代码
	//随机数种子
	srand((unsigned int)time(NULL));

	int k = 0;
	while (k < 100) // 随机选中两个位置交换100次
	{
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		while (x1 == x2 && y1 == y2 || map[x1][y1] == 0 || map[x2][y2] == 0) // 确保两个位置不同且两个位置都有图片
		{
			x1 = rand() % (MAX_X - 2) + 1;
			y1 = rand() % (MAX_Y - 2) + 1;

			x2 = rand() % (MAX_X - 2) + 1;
			y2 = rand() % (MAX_Y - 2) + 1;
		}
		int temp = map[x1][y1];
		map[x1][y1] = map[x2][y2];
		map[x2][y2] = temp;
		k++;
	}
	
	ShowMap(); // 重新显示地图

	CString text;
	range.GetWindowTextW(text);
	CString ra = text.Mid(3);
	int n = _ttoi(ra);
	n -= 50;  // 积分加10
	text.Format(_T("%d"), n);
	text = _T("积分:") + text;
	range.SetWindowTextW(text);
	if (n >= 50)
	{
		m_shuffle.EnableWindow(true);
		shuffleEnable = true;
	}
	else
	{
		m_shuffle.EnableWindow(false || !isRelax);
		shuffleEnable = false;
	}
}

// 提示
void CGameDlg::OnBnClickedBtnHint()
{
	// TODO:  在此添加控件通知处理程序代码
	CLLKButton* btn1;
	CLLKButton* btn2;
	bool b = true;
	
	for (int i = 0; i < m_btnGroup.GetSize() - 1; i++)
	{
		btn1 = (CLLKButton*)m_btnGroup.GetAt(i);
		for (int j = i + 1; j < m_btnGroup.GetSize(); j++)
		{
			btn2 = (CLLKButton*)m_btnGroup.GetAt(j);
			if (btn1->ID != 0 && btn1->ID == btn2->ID) // 两个位置的图片相同
			{
				if (btn1->LinkInLine(btn1->location, btn2->location) || btn1->OneCornerLink(btn1->location, btn2->location)
					|| btn1->TwoCornerLink(btn1->location, btn2->location)) // 两张图片之间可以连接
				{
					b = false;
					CWindowDC dc2(this);
					CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
					dc2.SelectObject(pen);
					pt1.x = btn1->location.y * 50 + 45;
					pt1.y = btn1->location.x * 50 + 70;
					pt2.x = btn2->location.y * 50 + 45;
					pt2.y = btn2->location.x * 50 + 70;
					pt3.x = CLLKButton::conner1.y * 50 + 45;
					pt3.y = CLLKButton::conner1.x * 50 + 70;
					pt4.x = CLLKButton::conner2.y * 50 + 45;
					pt4.y = CLLKButton::conner2.x * 50 + 70;

					//无拐点
					if (CLLKButton::conner1.x == -1)
					{
						dc2.MoveTo(pt1);
						dc2.LineTo(pt2);
					}
					//一个拐点
					else if (CLLKButton::conner2.x == -1)
					{
						dc2.MoveTo(pt1);
						dc2.LineTo(pt3);
						dc2.MoveTo(pt3);
						dc2.LineTo(pt2);
					}
					//两个拐点
					else
					{
						dc2.MoveTo(pt1);
						dc2.LineTo(pt3);
						dc2.MoveTo(pt3);
						dc2.LineTo(pt4);
						dc2.MoveTo(pt4);
						dc2.LineTo(pt2);
					}

					if (b)
					{
						MessageBox(_T("无法消除"), _T("警告"));
						for (int i = 0; i < m_btnGroup.GetSize(); i++)
						{
							delete (CLLKButton *)m_btnGroup.GetAt(i);
						}
						m_btnGroup.SetSize(0);

						m_pause.EnableWindow(false);
						m_hint.EnableWindow(false);
						m_shuffle.EnableWindow(false);
						prop.EnableWindow(false);
						range.EnableWindow(false);
					}

					CString text;
					range.GetWindowTextW(text);
					CString ra = text.Mid(3);
					int n = _ttoi(ra);
					n -= 20;  // 积分减20
					text.Format(_T("%d"), n);
					text = _T("积分:") + text;
					range.SetWindowTextW(text);

					if (n >= 20)
					{
						m_hint.EnableWindow(true);
						hintEnable = true;
					}
					else
					{
						m_hint.EnableWindow(false || isRelax);
						hintEnable = false;
					}
					return;
				}
			}
		}
	}

	
}

// 点击道具按钮
void CGameDlg::OnBnClickedBtnProp()
{
	// TODO:  在此添加控件通知处理程序代码
	clickPropBtn = true;

}
