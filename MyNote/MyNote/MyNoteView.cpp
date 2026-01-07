
// MyNoteView.cpp: CMyNoteView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyNote.h"
#endif

#include "MyNoteDoc.h"
#include "MyNoteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyNoteView

IMPLEMENT_DYNCREATE(CMyNoteView, CEditView)

BEGIN_MESSAGE_MAP(CMyNoteView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_FONT, &CMyNoteView::OnFont)
	ON_COMMAND(ID_BGCOLOR, &CMyNoteView::OnBgcolor)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// CMyNoteView 构造/析构

CMyNoteView::CMyNoteView() noexcept
{
	// TODO: 在此处添加构造代码
	m_crBack = RGB(255, 255, 255); // 初始为白色
	m_brBack.CreateSolidBrush(m_crBack); // 创建白色的刷子

}

CMyNoteView::~CMyNoteView()
{
}

BOOL CMyNoteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// CMyNoteView 打印

BOOL CMyNoteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认 CEditView 准备
	return CEditView::OnPreparePrinting(pInfo);
}

void CMyNoteView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 开始打印
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMyNoteView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 结束打印
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMyNoteView 诊断

#ifdef _DEBUG
void CMyNoteView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyNoteView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyNoteDoc* CMyNoteView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyNoteDoc)));
	return (CMyNoteDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyNoteView 消息处理程序

void CMyNoteView::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg; // 弹出字体窗口
	if (dlg.DoModal() == IDOK)
	{
		static CFont font; // 必须是 static，否则函数结束字体就失效了
		font.DeleteObject();

		LOGFONT lf;
		dlg.GetCurrentFont(&lf); // 获取选中的字体信息
		font.CreateFontIndirect(&lf); // 创建字体

		SetFont(&font); // 给编辑器设置新字体
	}
}

void CMyNoteView::OnBgcolor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg(m_crBack); // 弹出颜色盘
	if (dlg.DoModal() == IDOK)
	{
		m_crBack = dlg.GetColor(); // 保存选中的颜色值
		m_brBack.DeleteObject();
		m_brBack.CreateSolidBrush(m_crBack); // 更新刷子颜色

		Invalidate(); // 强制窗口重绘，触发下面的刷新动作
	}
}

HBRUSH CMyNoteView::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// 设置文字背后的填充颜色
	pDC->SetBkColor(m_crBack);
	// 返回我们刚才选好的“刷子”，这样系统就会用它刷掉整个背景
	return (HBRUSH)m_brBack;
}
