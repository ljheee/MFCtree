
// MFCtreeView.cpp : CMFCtreeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCtree.h"
#endif

#include "MFCtreeDoc.h"
#include "MFCtreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCtreeView

IMPLEMENT_DYNCREATE(CMFCtreeView, CTreeView)

BEGIN_MESSAGE_MAP(CMFCtreeView, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCtreeView 构造/析构

CMFCtreeView::CMFCtreeView()
{
	// TODO:  在此处添加构造代码

}

CMFCtreeView::~CMFCtreeView()
{
}

BOOL CMFCtreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CMFCtreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

}

void CMFCtreeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCtreeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCtreeView 诊断

#ifdef _DEBUG
void CMFCtreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMFCtreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMFCtreeDoc* CMFCtreeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCtreeDoc)));
	return (CMFCtreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCtreeView 消息处理程序
