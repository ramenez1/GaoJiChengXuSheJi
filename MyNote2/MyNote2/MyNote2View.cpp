
// MyNote2View.cpp: CMyNote2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyNote2.h"
#endif

#include "MyNote2Doc.h"
#include "MyNote2View.h"

#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyNote2View

IMPLEMENT_DYNCREATE(CMyNote2View, CView)

BEGIN_MESSAGE_MAP(CMyNote2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_COMMAND(ID_SET_FONT, &CMyNote2View::OnSetFont)
	ON_COMMAND(ID_SET_BG, &CMyNote2View::OnSetBg)
	ON_COMMAND(ID_FILE_SAVE, &CMyNote2View::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMyNote2View::OnFileSaveAs)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMyNote2View 构造/析构

CMyNote2View::CMyNote2View() noexcept
{
	// TODO: 在此处添加构造代码
	m_crBack = RGB(255, 255, 255); // 默认背景是白色
	m_brBack.CreateSolidBrush(m_crBack);
	// 初始字体（宋体，高20像素）
	m_font.CreatePointFont(120, _T("宋体"));
	m_hasFocus = false;

}

CMyNote2View::~CMyNote2View()
{
}

BOOL CMyNote2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyNote2View 绘图

void CMyNote2View::OnDraw(CDC* pDC)
{
	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	// 1. 画背景
	CRect rect;
	GetClientRect(&rect); // 获取当前窗口的大小
	pDC->FillRect(&rect, &m_brBack); // 用我们的刷子涂满背景

	// 2. 画文字
	pDC->SelectObject(&m_font);      // 换上我们的字体
	pDC->SetBkMode(TRANSPARENT);    // 设置文字底色透明，否则会有白框
	pDC->DrawText(pDoc->m_strContent, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

}


// CMyNote2View 打印

BOOL CMyNote2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyNote2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyNote2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyNote2View 诊断

#ifdef _DEBUG
void CMyNote2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyNote2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyNote2Doc* CMyNote2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyNote2Doc)));
	return (CMyNote2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMyNote2View 消息处理程序

void CMyNote2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMyNote2Doc* pDoc = GetDocument(); // 拿到Doc的指针

	if (nChar == VK_BACK) { // 如果按的是退格键
		if (!pDoc->m_strContent.IsEmpty()) {
			pDoc->m_strContent.Delete(pDoc->m_strContent.GetLength() - 1); // 删掉最后一个字
		}
	}
	else {
		pDoc->m_strContent += (TCHAR)nChar; // 把按下的字符加进去
	}

	pDoc->SetModifiedFlag(TRUE);
	Invalidate(); 

	UpdateCaretPosition();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CMyNote2View::OnSetFont()
{
	// TODO: 在此添加命令处理程序代码
	LOGFONT lf;
	m_font.GetLogFont(&lf); // 拿到当前字体信息
	CFontDialog dlg(&lf);   // 让对话框默认选中当前字体
	if (dlg.DoModal() == IDOK) {
		m_font.DeleteObject();
		dlg.GetCurrentFont(&lf); // 拿到用户选的新字体
		m_font.CreateFontIndirect(&lf); // 创建新字体
		Invalidate(); // 立即刷屏
		UpdateCaretPosition();
	}
}

void CMyNote2View::OnSetBg()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg(m_crBack); // 弹出调色盘
	if (dlg.DoModal() == IDOK) {
		m_crBack = dlg.GetColor(); // 存下新颜色
		m_brBack.DeleteObject();
		m_brBack.CreateSolidBrush(m_crBack); // 更新刷子
		Invalidate(); // 立即刷屏
		UpdateCaretPosition();
	}
}

void CMyNote2View::UpdateCaretPosition()
{
	if (!m_hasFocus)
	{
		return;
	}

	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_font);

	CRect rect;
	GetClientRect(&rect);
	int lineHeight = dc.GetTextExtent(L"A").cy;

	int x = 0;
	int y = 0;
	CString text = pDoc->m_strContent;
	for (int i = 0; i < text.GetLength(); ++i)
	{
		TCHAR ch = text[i];
		if (ch == L'\r')
		{
			continue;
		}
		if (ch == L'\n')
		{
			x = 0;
			y += lineHeight;
			continue;
		}

		CString oneChar(ch);
		CSize sz = dc.GetTextExtent(oneChar);
		if (x + sz.cx > rect.Width())
		{
			x = 0;
			y += lineHeight;
		}
		x += sz.cx;
	}

	dc.SelectObject(pOldFont);
	SetCaretPos(CPoint(x, y));
}

void CMyNote2View::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	m_hasFocus = true;

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_font);
	int lineHeight = dc.GetTextExtent(L"A").cy;
	dc.SelectObject(pOldFont);

	CreateSolidCaret(2, lineHeight);
	UpdateCaretPosition();
	ShowCaret();
}

void CMyNote2View::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);
	m_hasFocus = false;
	HideCaret();
	DestroyCaret();
}

void CMyNote2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	UpdateCaretPosition();
}

void CMyNote2View::OnFileSave()
{
	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	if (pDoc->m_filePath.IsEmpty())
	{
		OnFileSaveAs();
		return;
	}

	if (pDoc->SaveToFile(pDoc->m_filePath))
	{
		pDoc->SetModifiedFlag(FALSE);
	}
}

void CMyNote2View::OnFileSaveAs()
{
	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CFileDialog dlg(FALSE, L"txt", nullptr,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();
		if (pDoc->SaveToFile(path))
		{
			pDoc->m_filePath = path;
			pDoc->SetPathName(path);
			pDoc->SetModifiedFlag(FALSE);
		}
	}
}

void CMyNote2View::OnFileSave()
{
	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	if (pDoc->m_filePath.IsEmpty())
	{
		OnFileSaveAs();
		return;
	}

	if (pDoc->SaveToFile(pDoc->m_filePath))
	{
		pDoc->SetModifiedFlag(FALSE);
	}
}

void CMyNote2View::OnFileSaveAs()
{
	CMyNote2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CFileDialog dlg(FALSE, L"txt", nullptr,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();
		if (pDoc->SaveToFile(path))
		{
			pDoc->m_filePath = path;
			pDoc->SetPathName(path);
			pDoc->SetModifiedFlag(FALSE);
		}
	}
}

//void CMyNote2View::OnSetFocus(CWnd* pOldWnd)
//{
//	CView::OnSetFocus(pOldWnd);
//
	// TODO: 在此处添加消息处理程序代码
	// 参数：光标宽度2，高度20。你可以根据字体大小调整 20 这个值
//	CreateSolidCaret(2, 20);
//	ShowCaret(); // 必须显式调用显示，否则它是隐藏的
//}

//void CMyNote2View::OnKillFocus(CWnd* pNewWnd)
//{
//	CView::OnKillFocus(pNewWnd);
//
	// TODO: 在此处添加消息处理程序代码
//	HideCaret(); // 隐藏
//	::DestroyCaret(); // 彻底销毁销毁
//}
