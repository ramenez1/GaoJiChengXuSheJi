
// CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#include <stack>   // 必须加，用来放数字桶和符号桶
#include <string>  // 字符串处理

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, show_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, XianShi_Kuang, show_text);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ANN_1, &CCalculatorDlg::OnBnClicked1)
	ON_BN_CLICKED(ANN_2, &CCalculatorDlg::OnBnClicked2)
	ON_BN_CLICKED(ANN_3, &CCalculatorDlg::OnBnClicked3)
	ON_BN_CLICKED(ANN_4, &CCalculatorDlg::OnBnClicked4)
	ON_BN_CLICKED(ANN_5, &CCalculatorDlg::OnBnClicked5)
	ON_BN_CLICKED(ANN_6, &CCalculatorDlg::OnBnClicked6)
	ON_BN_CLICKED(ANN_7, &CCalculatorDlg::OnBnClicked7)
	ON_BN_CLICKED(ANN_8, &CCalculatorDlg::OnBnClicked8)
	ON_BN_CLICKED(ANN_9, &CCalculatorDlg::OnBnClicked9)
	ON_BN_CLICKED(ANN_0, &CCalculatorDlg::OnBnClicked0)
	ON_BN_CLICKED(ANN_JIA, &CCalculatorDlg::OnBnClickedJia)
	ON_BN_CLICKED(ANN_JIAN, &CCalculatorDlg::OnBnClickedJian)
	ON_BN_CLICKED(ANN_CHENG, &CCalculatorDlg::OnBnClickedCheng)
	ON_BN_CLICKED(ANN_CHU, &CCalculatorDlg::OnBnClickedChu)
	ON_BN_CLICKED(ANN_DENG, &CCalculatorDlg::OnBnClickedDeng)
	ON_BN_CLICKED(ANN_QINGCHU, &CCalculatorDlg::OnBnClickedQingchu)
	ON_BN_CLICKED(ANN_ZUO, &CCalculatorDlg::OnBnClickedZuo)
	ON_BN_CLICKED(ANN_YOU, &CCalculatorDlg::OnBnClickedYou)
	ON_BN_CLICKED(ANN_TUIGE, &CCalculatorDlg::OnBnClickedTuige)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCalculatorDlg::OnBnClicked1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "1";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "1";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "2";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "2";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "3";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "3";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "4";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "4";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "5";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "5";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "6";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "6";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "7";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "7";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "8";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "8";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "9";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "9";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClicked0()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 1. 先把屏幕上的数字同步给变量
	if (is_new) {
		show_text = "0";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "0";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}

void CCalculatorDlg::OnBnClickedJia()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);        // 1. 先把屏幕上的字拿进程序
	show_text += L"+";       // 2. 直接在后面接一个加号
	is_new = false;   // 3. 只要按了符号，就说明没算完，继续拼式子
	UpdateData(FALSE);       // 4. 把更新后的长式子显示回屏幕
}

void CCalculatorDlg::OnBnClickedJian()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);        // 1. 先把屏幕上的字拿进程序
	show_text += L"-";       // 2. 直接在后面接一个加号
	is_new = false;   // 3. 只要按了符号，就说明没算完，继续拼式子
	UpdateData(FALSE);       // 4. 把更新后的长式子显示回屏幕      
}

void CCalculatorDlg::OnBnClickedCheng()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);        // 1. 先把屏幕上的字拿进程序
	show_text += L"*";       // 2. 直接在后面接一个加号
	is_new = false;   // 3. 只要按了符号，就说明没算完，继续拼式子
	UpdateData(FALSE);       // 4. 把更新后的长式子显示回屏幕 
}

void CCalculatorDlg::OnBnClickedChu()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);        // 1. 先把屏幕上的字拿进程序
	show_text += L"/";       // 2. 直接在后面接一个加号
	is_new = false;   // 3. 只要按了符号，就说明没算完，继续拼式子
	UpdateData(FALSE);       // 4. 把更新后的长式子显示回屏幕    
}


void CCalculatorDlg::OnBnClickedDeng()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (show_text.IsEmpty()) return;

	std::wstring s = show_text.GetString();
	std::stack<double> shu_tong;     // 存数字
	std::stack<wchar_t> fu_hao_tong; // 存符号

	for (int i = 0; i < s.length(); i++) {
		// 1. 处理数字（包括多位和小数点）
		if (iswdigit(s[i]) || s[i] == L'.') {
			wchar_t* endPtr;
			shu_tong.push(wcstod(&s[i], &endPtr));
			i += (endPtr - &s[i]) - 1;
		}
		// 2. 处理左括号
		else if (s[i] == L'(') {
			fu_hao_tong.push(L'(');
		}
		// 3. 处理右括号
		else if (s[i] == L')') {
			while (!fu_hao_tong.empty() && fu_hao_tong.top() != L'(')
				SuanYiXia(shu_tong, fu_hao_tong);
			if (!fu_hao_tong.empty()) fu_hao_tong.pop(); // 扔掉左括号
		}
		// 4. 处理加减乘除
		else {
			while (!fu_hao_tong.empty() && fu_hao_tong.top() != L'(' &&
				HuoQuYouXianJi(fu_hao_tong.top()) >= HuoQuYouXianJi(s[i])) {
				SuanYiXia(shu_tong, fu_hao_tong);
			}
			fu_hao_tong.push(s[i]);
		}
	}
	// 把剩下的算完
	while (!fu_hao_tong.empty()) SuanYiXia(shu_tong, fu_hao_tong);

	if (!shu_tong.empty()) {
		show_text.Format(L"%g", shu_tong.top());
	}
	UpdateData(FALSE);
	is_new = true; // 标记算完了

}

void CCalculatorDlg::OnBnClickedQingchu()
{
	// TODO: 在此添加控件通知处理程序代码
	show_text = L"";
	num1 = 0;
	fu_hao = L"";
	is_new = true;
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedZuo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (is_new) {
		show_text = "(";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += "(";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上

}



void CCalculatorDlg::OnBnClickedYou()
{
	// TODO: 在此添加控件通知处理程序代码
	if (is_new) {
		show_text = ")";    // 如果是新输入的，就直接覆盖
		is_new = false;
	}
	else {
		show_text += ")";   // 如果不是新输入的，就接在屁股后面
	}
	UpdateData(FALSE); // 2. 把更新后的变量显示到屏幕上
}



void CCalculatorDlg::OnBnClickedTuige()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!show_text.IsEmpty()) {
		show_text.Delete(show_text.GetLength() - 1);
	}
	UpdateData(FALSE);
}





//辅助
// 规则：乘除是2级，加减是1级，括号是0级
int CCalculatorDlg::HuoQuYouXianJi(wchar_t op) {
	if (op == L'+' || op == L'-') return 1;
	if (op == L'*' || op == L'/') return 2;
	return 0;
}

// 从数字桶拿两个数，从符号桶拿一个符，算完再塞回去
void CCalculatorDlg::SuanYiXia(std::stack<double>& shu_tong, std::stack<wchar_t>& fu_hao_tong) {
	if (shu_tong.size() < 2 || fu_hao_tong.empty()) return;

	double b = shu_tong.top(); shu_tong.pop(); // 后进去的数
	double a = shu_tong.top(); shu_tong.pop(); // 先进去的数
	wchar_t op = fu_hao_tong.top(); fu_hao_tong.pop();

	if (op == L'+') shu_tong.push(a + b);
	else if (op == L'-') shu_tong.push(a - b);
	else if (op == L'*') shu_tong.push(a * b);
	else if (op == L'/') {
		if (b == 0) {
			AfxMessageBox(L"不能除以0");
			shu_tong.push(0);
		}
		else {
			shu_tong.push(a / b);
		}
	}
}