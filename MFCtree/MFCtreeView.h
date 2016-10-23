
// MFCtreeView.h : CMFCtreeView ��Ľӿ�
//

#pragma once


class CMFCtreeView : public CTreeView
{
protected: // �������л�����
	CMFCtreeView();
	DECLARE_DYNCREATE(CMFCtreeView)

// ����
public:
	CMFCtreeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMFCtreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCtreeView.cpp �еĵ��԰汾
inline CMFCtreeDoc* CMFCtreeView::GetDocument() const
   { return reinterpret_cast<CMFCtreeDoc*>(m_pDocument); }
#endif

