
// CalculatorDlg.h: 头文件
//

#pragma once
#include <stack>


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数
	double num1 = 0;      // 存第一个数字
	CString fu_hao = L"";  // 存加减乘除符号
	bool is_new = true;   // 标记：是不是要开始输入新数字了
	// 核心计算功能
	int HuoQuYouXianJi(wchar_t op); // 判断加减乘除权力的函数
	void SuanYiXia(std::stack<double>& shu_tong, std::stack<wchar_t>& fu_hao_tong); // 算一下桶顶的两个数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClicked1();
	CString show_text;
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClickedJia();
	afx_msg void OnBnClickedJian();
	afx_msg void OnBnClickedCheng();
	afx_msg void OnBnClickedChu();
	afx_msg void OnBnClickedDeng();
	afx_msg void OnBnClickedQingchu();
	afx_msg void OnBnClickedZuo();
	afx_msg void OnBnClickedYou();
	afx_msg void OnBnClickedTuige();
};
