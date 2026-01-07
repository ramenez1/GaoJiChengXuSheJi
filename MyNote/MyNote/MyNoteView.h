
// MyNoteView.h: CMyNoteView 类的接口
//

#pragma once


class CMyNoteView : public CEditView
{
protected: // 仅从序列化创建
	CMyNoteView() noexcept;
	DECLARE_DYNCREATE(CMyNoteView)

//功能
public:
	COLORREF m_crBack; // 记录背景颜色
	CBrush m_brBack;   // 真正的油漆刷子
// 特性
public:
	CMyNoteDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyNoteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFont();
	afx_msg void OnBgcolor();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};

#ifndef _DEBUG  // MyNoteView.cpp 中的调试版本
inline CMyNoteDoc* CMyNoteView::GetDocument() const
   { return reinterpret_cast<CMyNoteDoc*>(m_pDocument); }
#endif

