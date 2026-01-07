
// MyNote2View.h: CMyNote2View 类的接口
//

#pragma once


class CMyNote2View : public CView
{
protected: // 仅从序列化创建
	CMyNote2View() noexcept;
	DECLARE_DYNCREATE(CMyNote2View)

// 功能
public:
	COLORREF m_crBack; // 背景颜色值
	CBrush m_brBack;   // 刷背景
	CFont m_font;      // 文字样式
// 特性
public:
	CMyNote2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyNote2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFont();
	afx_msg void OnSetBg();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

#ifndef _DEBUG  // MyNote2View.cpp 中的调试版本
inline CMyNote2Doc* CMyNote2View::GetDocument() const
   { return reinterpret_cast<CMyNote2Doc*>(m_pDocument); }
#endif

