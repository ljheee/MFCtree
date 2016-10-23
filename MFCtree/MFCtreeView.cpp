
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
//	ON_NOTIFY_REFLECT(TVN_SELCHANGING, &CMFCtreeView::OnTvnSelchanging)
ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMFCtreeView::OnTvnSelchanged)
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

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;//�ı����ؼ����
	return CTreeView::PreCreateWindow(cs);
}

void CMFCtreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	m_ImageList.Create(16 , 16,ILC_COLOR8|ILC_MASK,2,1 );
	m_ImageList.SetBkColor( RGB(255,255,255) );
	treeCtrl.SetImageList(&m_ImageList , TVSIL_NORMAL);

	CString strParh;//
	GetWindowsDirectory((LPTSTR)(LPCTSTR)strParh , MAX_PATH+1);

	//
	SHFILEINFO fi;
	SHGetFileInfo( strParh, 0, &fi , sizeof(SHFILEINFO),
		SHGFI_ICON|SHGFI_SMALLICON|SHGFI_OPENICON);
	m_ImageList.Add( fi.hIcon);
	

	//
	CString str;
	for (int i = 0; i < 32; i++)
	{
		str.Format(_T("%c:\\") , 'A'+i);
		SHGetFileInfo(str , 0, &fi, sizeof(SHFILEINFO),
			SHGFI_ICON | SHGFI_SMALLICON | SHGFI_DISPLAYNAME);

		if (fi.hIcon){
			int nImage = m_ImageList.Add( fi.hIcon);
			HTREEITEM hItem = treeCtrl.InsertItem( fi.szDisplayName, nImage , nImage);
			treeCtrl.SetItemData( hItem, (DWORD)('A'+i));
		}


	}


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

//�Զ��庯��������ԭ����.h�ļ�
void  CMFCtreeView::InsertFoldItem(HTREEITEM hItem, CString strPath){
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	if (treeCtrl.ItemHasChildren(hItem)){
		return;
	}

	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	while (bWorking){
		bWorking = finder.FindNextFileW();
		if (finder.IsDirectory() && !finder.IsHidden() && !finder.IsDots()){
			treeCtrl.InsertItem(finder.GetFileTitle(), 0 , 1,hItem ,TVI_SORT);
		}
	}
}

//�Զ��庯��
CString  CMFCtreeView::GetFoldItemPath(HTREEITEM hItem){
	CString strPath, str;
	strPath.Empty();
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM folderItem = hItem;
	while (folderItem){
		int data = (int)treeCtrl.GetItemData(folderItem);
		if (data == 0){
			str = treeCtrl.GetItemText( folderItem);
		}else{
			str.Format(_T("%c:\\"), data);  //?
		}
		strPath = str + "\\" + strPath;
		folderItem = treeCtrl.GetParentItem( folderItem);
	}
//	strPath = strPath + "*.*";
	strPath += "*.*";  //
	return strPath;
}

// CMFCtreeView ��Ϣ�������




//C...View���е���Ϣ����������ǰѡ��Ľڵ�ı�ʱ
void CMFCtreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hSelItem = pNMTreeView->itemNew.hItem;//��ȡ��ǰѡ��Ľڵ�
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	CString strPath = GetFoldItemPath( hSelItem);
	if (!strPath.IsEmpty()){
		InsertFoldItem(hSelItem ,strPath);
		treeCtrl.Expand(hSelItem, TVE_EXPAND);
	}

	*pResult = 0;
}
