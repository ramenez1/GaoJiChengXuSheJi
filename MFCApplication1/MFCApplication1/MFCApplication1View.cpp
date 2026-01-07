
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_LINE, &CMFCApplication1View::OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMFCApplication1View::OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &CMFCApplication1View::OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CMFCApplication1View::OnUpdateDrawRect)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CMFCApplication1View::OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CMFCApplication1View::OnUpdateDrawEllipse)
	ON_COMMAND(ID_EDIT_UNDO, &CMFCApplication1View::OnEditUndo)
	ON_COMMAND(ID_EDIT_CLEARALL, &CMFCApplication1View::OnEditClearall)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码
	m_isDrawing = false;
	m_currentType = SHAPE_LINE; // 默认画直线
	m_ptStart = 0;
	m_ptEnd = 0;

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	//1. 绘制历史图形
	for (const auto& shape : pDoc->m_shapes)
	{
		if (shape.type == SHAPE_LINE) {
			pDC->MoveTo(shape.start);
			pDC->LineTo(shape.end);
		}
		else if (shape.type == SHAPE_RECT) {
			CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(CRect(shape.start, shape.end));
			pDC->SelectObject(pOldBrush);
		}
		else if (shape.type == SHAPE_ELLIPSE) { 
			CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); 
			pDC->Ellipse(CRect(shape.start, shape.end));
			pDC->SelectObject(pOldBrush);
		}
	}

	//2. 绘制正在拖拽的预览
	if (m_isDrawing)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);

		if (m_currentType == SHAPE_LINE) {
			pDC->MoveTo(m_ptStart);
			pDC->LineTo(m_ptEnd);
		}
		else if (m_currentType == SHAPE_RECT) {
			CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle(CRect(m_ptStart, m_ptEnd));
			pDC->SelectObject(pOldBrush);
		}
		else if (m_currentType == SHAPE_ELLIPSE) {
			CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->Ellipse(CRect(m_ptStart, m_ptEnd));
			pDC->SelectObject(pOldBrush);
		}

		pDC->SelectObject(pOldPen);
	}
}


// CMFCApplication1View 打印

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 1. 标记开始绘图
	m_isDrawing = true;

	// 2. 记录起点
	m_ptStart = point;
	m_ptEnd = point; // 刚按下时，终点等于起点

	// 3. 捕获鼠标（防止拖拽出窗口后收不到消息）
	SetCapture();

	CView::OnLButtonDown(nFlags, point);

}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_isDrawing)
	{
		// 更新当前的终点
		m_ptEnd = point;

		// 触发重绘
		// Invalidate() 会告诉 Windows："这个窗口脏了，请尽快调用 OnDraw 重画"
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_isDrawing)
	{
		m_isDrawing = false;
		m_ptEnd = point;

		// 释放鼠标捕获
		ReleaseCapture();
		// 获取文档指针
		CMFCApplication1Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		// 将当前画完的图形存入 vector
		MyShape newShape;
		newShape.type = m_currentType;
		newShape.start = m_ptStart;
		newShape.end = m_ptEnd;
		pDoc->m_shapes.push_back(newShape);
		//存入文档的数据中
		pDoc->m_shapes.push_back(newShape);

		//标记文档已修改
		pDoc->SetModifiedFlag(TRUE);

		// 最后刷新一次
		Invalidate();
	}


	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplication1View::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_currentType = SHAPE_LINE; // 切换模式
}

void CMFCApplication1View::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// 如果当前是直线模式，SetCheck(TRUE) 会在菜单旁打个钩
	pCmdUI->SetCheck(m_currentType == SHAPE_LINE);
}

void CMFCApplication1View::OnDrawRect()
{
	m_currentType = SHAPE_RECT;
	// TODO: 在此添加命令处理程序代码
}

void CMFCApplication1View::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_currentType == SHAPE_RECT);
}

void CMFCApplication1View::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_currentType = SHAPE_ELLIPSE;
}

void CMFCApplication1View::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_currentType == SHAPE_ELLIPSE);
}

void CMFCApplication1View::OnEditUndo()
{
	// 获取文档指针
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 在此添加命令处理程序代码
	if (pDoc->m_shapes.empty())
	{
		MessageBox(_T("没有可以撤销的图形了！"));
		return;
	}

	// 弹出
	pDoc->m_shapes.pop_back();
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CMFCApplication1View::OnEditClearall()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档指针
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_shapes.empty()) return;

	if (MessageBox(_T("确定要清空画布吗？"), _T("警告"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		// 清空 vector
		pDoc->m_shapes.clear();
		pDoc->SetModifiedFlag(TRUE);
		Invalidate();
	}
}
