
#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "CLLKButton.h"
#include "ctime"

//初始化全局变量
CLLKButton* CLLKButton::firstBtn = NULL;
CLLKButton* CLLKButton::secondBtn = NULL;
CPoint CLLKButton::conner1(-1, -1);
CPoint CLLKButton::conner2(-1, -1);
CGameDlg* CLLKButton::game = NULL;


IMPLEMENT_DYNAMIC(CLLKButton, CButton)

CLLKButton::CLLKButton()
: ID(0)
, location(0)
{

}

// 析构
CLLKButton::~CLLKButton()
{
}


BEGIN_MESSAGE_MAP(CLLKButton, CButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// 有参构造
CLLKButton::CLLKButton(int type, CPoint point)
{
	location = point;
	ID = type;

}


// 一条直线消子
bool CLLKButton::LinkInLine(CPoint p1, CPoint p2) 
{
	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	BOOL b = true;
	if (p1.y == p2.y) // 两个点再同一行
	{
		int min_x = min(p1.x, p2.x);
		int max_x = max(p1.x, p2.x);
		for (int i = min_x+1; i < max_x; i++)
		{
			if (game->map[i][p1.y] != 0)
			{
				b = false;
			}
		}
	}
	else if (p1.x == p2.x) // 在同一列
	{
		int min_y = min(p1.y, p2.y);
		int max_y = max(p1.y, p2.y);
		for (int i = min_y + 1; i < max_y; i++)
		{
			if (game->map[p1.x][i] != 0)
			{
				b = false;
			}
		}
	}
	else // 不在同一直线
	{
		b = false;
	}
	return b;
}

// 两条直线消子
bool CLLKButton::OneCornerLink(CPoint p1, CPoint p2) 
{
	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	int min_x = min(p1.x, p2.x);
	int max_x = max(p1.x, p2.x);
	int min_y = min(p1.y, p2.y);
	int max_y = max(p1.y, p2.y);

	// 拐点1
	int x1 = p1.x;
	int y1 = p2.y;
	//拐点2
	int x2 = p2.x;
	int y2 = p1.y;

	BOOL b = true;
	if (game->map[x1][y1] != 0 && game->map[x2][y2] != 0)
	{
		b = false;
	}
	else
	{
		if (game->map[x1][y1] == 0) // 拐点1位置无图片
		{
			for (int i = min_x + 1; i < max_x; i++)
			{
				if (game->map[i][y1] != 0)
				{
					b = false;
					break;
				}
			}
			for (int i = min_y + 1; i < max_y; i++)
			{
				if (game->map[x1][i] != 0)
				{
					b = false;
					break;
				}
			}
			if (b)
			{
				conner1.x = x1;
				conner1.y = y1;
				return b;
			}

		}
		
		
		if (game->map[x2][y2] == 0) // 拐点2位置无图片
		{
			b = true;
			for (int i = min_x + 1; i < max_x; i++)
			{
				if (game->map[i][y2] != 0)
				{
					b = false;
					break;
				}
			}
			for (int i = min_y + 1; i < max_y; i++)
			{
				if (game->map[x2][i] != 0)
				{
					b = false;
					break;
				}
			}
			if (b)
			{
				conner1.x = x2;
				conner1.y = y2;
				return b;
			}
		}
	}

	return b;
}

// 三条直线消子
bool CLLKButton::TwoCornerLink(CPoint p1, CPoint p2) 
{
	conner1.x = conner1.y = -1;
	conner2.x = conner2.y = -1;

	int min_x = min(p1.x, p2.x);
	int max_x = max(p1.x, p2.x);
	int min_y = min(p1.y, p2.y);
	int max_y = max(p1.y, p2.y);
	bool b;
	for (int i = 0; i < MAX_Y; i++) // 扫描行
	{
		b = true;
		if (game->map[p1.x][i] == 0 && game->map[p2.x][i] == 0) // 两个拐点位置无图片
		{
			for (int j = min_x + 1; j < max_x; j++) // 判断连个拐点之间是否可以连接
			{
				if (game->map[j][i] != 0)
				{
					b = false;
					break;
				}
			}

			if (b)
			{
				int temp_max = max(p1.y, i);
				int temp_min = min(p1.y, i);
				for (int j = temp_min + 1; j < temp_max; j++) // 判断p1和它所对应的拐点之间是否可以连接
				{
					if (game->map[p1.x][j] != 0)
					{
						b = false;
						break;
					}
				}
			}

			if (b)
			{
				int temp_max = max(p2.y, i);
				int temp_min = min(p2.y, i);
				for (int j = temp_min + 1; j < temp_max; j++) // 判断p2和它所对应的拐点之间是否可以连接
				{
					for (int j = temp_min + 1; j < temp_max; j++)
					{
						if (game->map[p2.x][j] != 0)
						{
							b = false;
							break;
						}
					}
				}
			}
			if (b) // 如果存在路线，返回true
			{
				conner1.x = p1.x;
				conner1.y = i;
				conner2.x = p2.x;
				conner2.y = i;
				return b;
			}
		} 
		
	}// 扫描行结束

	

	for (int i = 0; i < MAX_X; i++) // 扫描列
	{
		b = true;
		if (game->map[i][p1.y] == 0 && game->map[i][p2.y] == 0) // 连个拐点位置无图片
		{
			for (int j = min_y + 1; j < max_y; j++) // 两个拐点之间是否可以连接
			{
				if (game->map[i][j] != 0)
				{
					b = false;
					break;
				}
			}

			if (b)
			{
				int temp_max = max(i, p1.x);
				int temp_min = min(i, p1.x);
				for (int j = temp_min + 1; j < temp_max; j++) // 判断p1和它所对应的拐点之间是否可以连接
				{
					if (game->map[j][p1.y] != 0)
					{
						b = false;
						break;
					}
				}
			}

			if (b)
			{
				int temp_max = max(p2.x, i);
				int temp_min = min(p2.x, i);
				for (int j = temp_min + 1; j < temp_max; j++)
				{
					if (game->map[j][p2.y] != 0)
					{
						b = false;
						break;
					}
				}
			}
			if (b) // 如果存在路线，返回true
			{
				conner1.y = p1.y;
				conner1.x = i;
				conner2.y = p2.y;
				conner2.x = i;
				return b;
			}
		}
		
	} // 扫描列结束

	return b;
}

// 点击按钮响应函数
void CLLKButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (firstBtn == NULL) // 第一次点击按钮时
	{
		firstBtn = this;
		//firstBtn->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
	}
	else if (firstBtn == this) // 两次点击的按钮相同时,取消选中
	{
		//firstBtn->ModifyStyle(0, BS_DEFPUSHBUTTON);
		firstBtn = NULL; 
	}
	else if (firstBtn->ID != this->ID) // 第二次点击按钮但图片不相同时
	{
		firstBtn = this;
	}
	else if (firstBtn->ID == this->ID) // 两次点击的图片相同
	{
		if (LinkInLine(firstBtn->location, this->location) || OneCornerLink(firstBtn->location, this->location)
			|| TwoCornerLink(firstBtn->location, this->location) || game->clickPropBtn) // 两张图片之间可以连接
		{
			secondBtn = this;
			if (!game->clickPropBtn)
			{
				game->OnPaint(); // 画线
			}
			else
			{
				game->propCount--;
				game->clickPropBtn = false;
			}
			firstBtn->ShowWindow(SW_HIDE); // 隐藏按钮
			secondBtn->ShowWindow(SW_HIDE);
			game->map[firstBtn->location.x][firstBtn->location.y] = 0;
			game->map[secondBtn->location.x][secondBtn->location.y] = 0;

			CString text;
			game->range.GetWindowTextW(text);
			CString ra = text.Mid(3);
			int n = _ttoi(ra);
			n += 10;  // 积分加10
			text.Format(_T("%d"), n);
			text = _T("积分:") + text;
			game->range.SetWindowTextW(text);

			if (n - game->propSum * 100 >= 100)
			{
				game->propSum = game->propSum + 1;
				game->propCount = game->propCount + 1;
			}

			if (game->propCount > 0 && game->isRelax) // 道具功能是否可用
			{
				game->prop.EnableWindow(true);
			}
			else
			{
				game->prop.EnableWindow(false);
			}

			if (n >= 50) // 重排功能是否可用
			{
				game->m_shuffle.EnableWindow(true);
				game->shuffleEnable = true;
			}
			else
			{
				game->m_shuffle.EnableWindow(false || !game->isRelax);
				game->shuffleEnable = false;
			}

			if (n >= 20) // 提示功能是否可用
			{
				game->m_hint.EnableWindow(true);
				game->hintEnable = true;
			}
			else
			{
				game->m_hint.EnableWindow(false || !game->isRelax);
				game->hintEnable = false;
			}

			firstBtn->ID = 0;
			secondBtn->ID = 0;
			if (game->IsFinished()) // 如果通关
			{
				MessageBox(_T("恭喜通过！！！"), _T("通关"));

				if (MessageBox(_T("是否保存记录"), _T("提示"), MB_YESNO) == IDYES && game->isRelax)// 保存记录
				{
					CStdioFile mFile;
					CFileException mExcept;
					if (!mFile.Open(_T("record.txt"), CFile::modeWrite, &mExcept))
						mFile.Open(_T("record.txt"), CFile::modeCreate | CFile::modeWrite, &mExcept);
					CString str;
					mFile.SeekToEnd();
					//将记录写入文件的最后面
					CTime t = CTime::GetCurrentTime();
					CString s = t.Format(_T("%Y-%m-%d %H:%M:%S\n"));
					//MessageBox(_T("" + s));
					mFile.WriteString(s);
					s.Format(_T("%d\n"), n);
					mFile.WriteString(s);

				}
			}
			firstBtn = NULL;
			secondBtn = NULL;
		}
		else
		{
			firstBtn = NULL;
		}
	}
}


