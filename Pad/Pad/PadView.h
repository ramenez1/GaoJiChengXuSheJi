
// PadView.h: CPadView 类的接口
//

#pragma once


class CPadView : public CEditView
{
protected: // 仅从序列化创建
	CPadView() noexcept;
	DECLARE_DYNCREATE(CPadView)

// 特性
public:
	CPadDoc* GetDocument() const;

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
	virtual ~CPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PadView.cpp 中的调试版本
inline CPadDoc* CPadView::GetDocument() const
   { return reinterpret_cast<CPadDoc*>(m_pDocument); }
#endif

