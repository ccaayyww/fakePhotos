
// Microsoft PhotosDlg.h: 头文件
//

#pragma once


// CMicrosoftPhotosDlg 对话框
class CMicrosoftPhotosDlg : public CDialogEx
{
// 构造
public:
	CMicrosoftPhotosDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MICROSOFTPHOTOS_DIALOG };
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
	
	afx_msg void OnBnClickedButtonselectfile();
	void FunInitDlg();
	int FunChangeJpgFile(TCHAR *szSrcJpg,TCHAR *szOutPath);
	afx_msg void OnBnClickedButtonoutputpath();
	afx_msg void OnBnClickedButtonmodifyjpg();
};
