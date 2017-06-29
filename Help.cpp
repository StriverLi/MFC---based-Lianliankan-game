// Help.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "Help.h"
#include "afxdialogex.h"


// CHelp 对话框

IMPLEMENT_DYNAMIC(CHelp, CDialogEx)

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelp::IDD, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelp, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CHelp 消息处理程序


// 设置滚动条大小
void CHelp::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//设置滚动条范围  
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = 998;
	si.nPage = cx;
	//SetScrollInfo(SB_HORZ, &si, TRUE);
	si.nMax = 496;
	si.nPage = cy;
	SetScrollInfo(SB_VERT, &si, TRUE);

	int icurxpos = GetScrollPos(SB_HORZ);
	int icurypos = GetScrollPos(SB_VERT);

	if (icurxpos < m_ixoldpos || icurypos < m_iyoldpos)
	{
		ScrollWindow(m_ixoldpos - icurxpos, 0);
		ScrollWindow(0, m_iyoldpos - icurypos);

	}
	m_ixoldpos = icurxpos;
	m_iyoldpos = icurypos;

	Invalidate(TRUE);

	// TODO:  在此处添加消息处理程序代码
}

// 单击竖直滚动条
void CHelp::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	static int oldpos = 0;
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.  
	int curpos = GetScrollPos(SB_VERT);

	// Determine the new position of scroll box.  
	switch (nSBCode)
	{
	case SB_TOP:  // Scroll to far left.  
		curpos = minpos;
		break;

	case SB_BOTTOM:   // Scroll to far right.  
		curpos = maxpos;
		break;

	case SB_ENDSCROLL:    //End scroll.  
		break;

	case SB_LINEUP: // Scroll left.  
		if (curpos > minpos)
			curpos--;
		break;

	case SB_LINEDOWN:   // Scroll right.  
		if (curpos < maxpos)
			curpos++;
		break;

	case SB_PAGEUP:  // Scroll one page left.  
	{
		// Get the page size.   
		SCROLLINFO info;
		 GetScrollInfo(SB_VERT, &info, SIF_ALL);

		if (curpos > minpos)
			curpos = max(minpos, (curpos - (int)info.nPage));
	}
	break;

	case SB_PAGEDOWN:  // Scroll one page right.  
	{
		// Get the page size.   
		SCROLLINFO info;
		GetScrollInfo(SB_VERT, &info, SIF_ALL);

		if (curpos < maxpos)
			curpos = min(maxpos, curpos + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION:  // Scroll to absolute position. nPos is the position  
		curpos = nPos;  // of the scroll box at the end of the drag operation.  
		break;

	case SB_THUMBTRACK:  // Drag scroll box to specified position. nPos is the  
		curpos = nPos;  // position that the scroll box has been dragged to.  
		break;
	}

	SetScrollPos(SB_VERT, curpos);
	ScrollWindow(0, oldpos - curpos);

	oldpos = curpos;
	UpdateWindow();

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
