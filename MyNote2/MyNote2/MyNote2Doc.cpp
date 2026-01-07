
// MyNote2Doc.cpp: CMyNote2Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyNote2.h"
#endif

#include "MyNote2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyNote2Doc

IMPLEMENT_DYNCREATE(CMyNote2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyNote2Doc, CDocument)
END_MESSAGE_MAP()


// CMyNote2Doc 构造/析构

CMyNote2Doc::CMyNote2Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CMyNote2Doc::~CMyNote2Doc()
{
}

BOOL CMyNote2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_strContent = _T(""); // 新建
	m_filePath = _T("");

	return TRUE;
}




// CMyNote2Doc 序列化

void CMyNote2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << m_strContent;
	}
	else
	{
		// TODO: 在此添加加载代码
		ar >> m_strContent;
	}
}

bool CMyNote2Doc::SaveToFile(const CString& path)
{
	CStdioFile file;
	if (!file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		return false;
	}

	file.WriteString(m_strContent);
	file.Close();
	return true;
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMyNote2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMyNote2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMyNote2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyNote2Doc 诊断

#ifdef _DEBUG
void CMyNote2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyNote2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyNote2Doc 命令
