
// MFCtreeView.h : CMFCtreeView 类的接口
//

#pragma once


class CMFCtreeView : public CTreeView
{
protected: // 仅从序列化创建
	CMFCtreeView();
	DECLARE_DYNCREATE(CMFCtreeView)

// 特性
public:
	CMFCtreeDoc* GetDocument() const;

	CImageList m_ImageList;//添加成员变量
	CString m_strPath;

// 操作
public:
	void InsertFoldItem(HTREEITEM hItem , CString strPath);
	CString GetFoldItemPath(HTREEITEM hItem);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMFCtreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTvnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // MFCtreeView.cpp 中的调试版本
inline CMFCtreeDoc* CMFCtreeView::GetDocument() const
   { return reinterpret_cast<CMFCtreeDoc*>(m_pDocument); }
#endif

