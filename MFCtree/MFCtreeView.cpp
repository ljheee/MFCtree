
// MFCtreeView.cpp : CMFCtreeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMFCtreeView ����/����

CMFCtreeView::CMFCtreeView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMFCtreeView::~CMFCtreeView()
{
}

BOOL CMFCtreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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


// CMFCtreeView ���

#ifdef _DEBUG
void CMFCtreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMFCtreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMFCtreeDoc* CMFCtreeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCtreeDoc)));
	return (CMFCtreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCtreeView ��Ϣ�������
