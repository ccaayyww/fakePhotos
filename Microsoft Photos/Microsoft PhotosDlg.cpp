
// Microsoft PhotosDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Microsoft Photos.h"
#include "Microsoft PhotosDlg.h"
#include "afxdialogex.h"

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


// CMicrosoftPhotosDlg 对话框



CMicrosoftPhotosDlg::CMicrosoftPhotosDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MICROSOFTPHOTOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMicrosoftPhotosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMicrosoftPhotosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_BUTTONSELECTFILE, &CMicrosoftPhotosDlg::OnBnClickedButtonselectfile)
	ON_BN_CLICKED(IDC_BUTTONOUTPUTPATH, &CMicrosoftPhotosDlg::OnBnClickedButtonoutputpath)
	ON_BN_CLICKED(IDC_BUTTONMODIFYJPG, &CMicrosoftPhotosDlg::OnBnClickedButtonmodifyjpg)
END_MESSAGE_MAP()


// CMicrosoftPhotosDlg 消息处理程序

BOOL CMicrosoftPhotosDlg::OnInitDialog()
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
	FunInitDlg();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CMicrosoftPhotosDlg::FunInitDlg()
{
	CString strInfo;
	strInfo.Format("透明加密的JPG转换软件");
	SetDlgItemText(IDC_EDITINFO, strInfo);
}
void CMicrosoftPhotosDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMicrosoftPhotosDlg::OnPaint()
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
HCURSOR CMicrosoftPhotosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMicrosoftPhotosDlg::FunChangeJpgFile(TCHAR *szSrcJpg, TCHAR *szOutPath)
{
	if (strlen(szSrcJpg) == 0)return 0;
	TCHAR szOutTmp[MAX_PATH];  //临时文件输出路径
	TCHAR szFile[MAX_PATH];
	TCHAR szTmpFile[MAX_PATH];  //临时文件
	TCHAR szOut[MAX_PATH];  //文件输出路径
	//获取文件名
	char *p = strrchr(szSrcJpg, '\\');
	if (p == nullptr)return 0;
	memset(szFile, 0, sizeof(szFile));
	strcpy_s(szFile, sizeof(szFile), p+1);
		
	//临时文件为文件名替换.jpg为后缀.tmp
	memset(szTmpFile, 0, sizeof(szTmpFile));
	p =strrchr(szFile,'.');
	if (p != nullptr)
	{
		memcpy(szTmpFile, szFile,p-(char *)szFile);		
	}else
	{
		strcpy_s(szTmpFile, sizeof(szTmpFile), szFile);
	}
	strcat_s(szTmpFile, sizeof(szTmpFile), ".tmp");

	//文件输出路径
	if (strlen(szOutPath) == 0)
	{
		memset(szOut, 0, sizeof(szOut));
		char *p = strrchr(szSrcJpg, '\\');
		if (p != nullptr)
			memcpy(szOut, szSrcJpg, p - szSrcJpg);
		strcat_s(szOut, sizeof(szOut), "\\out\\");
		CreateDirectory(szOut,NULL);		
	}else
	{
		strcpy_s(szOut, sizeof(szOut), szOutPath);
		if(szOut[strlen(szOut)-1]!='\\')
		strcat_s(szOut, sizeof(szOut), "\\");		
	}
	//临时文件输出路径
	strcpy_s(szOutTmp, sizeof(szOutTmp), szOut);
	strcat_s(szOutTmp, sizeof(szOutTmp), szTmpFile);
	SetDlgItemText(IDC_EDITTMPFILE, szOutTmp);
		
	FILE *f;
	errno_t err = fopen_s(&f, szSrcJpg, "rb");
	
	if (err != 0)return 0;
	FILE *fw;
	err = fopen_s(&fw, szOutTmp, "w+b");	
	if (err != 0)
	{
		fclose(f);
		return 0;
	}
	int flen = 0;
	if (f)
	{
		BYTE buf[4096 + 1];
		while (true)
		{
			size_t ilen = fread_s(buf, 4096, sizeof(BYTE), 4096, f);
			if (ilen == 0)break;
			fwrite(buf, sizeof(BYTE), ilen, fw);
			buf[100] = 0;
			flen += ilen;
		}
		fclose(f);
		fclose(fw);
	}

	TCHAR szOutFile[MAX_PATH];  //输出文件路径	
	memset(szOutFile, 0, sizeof(szOutFile));
	strcpy_s(szOutFile, sizeof(szOutFile), szOut);
	strcat_s(szOutFile, sizeof(szOutFile), szFile);

	TCHAR szCmd[MAX_PATH];
	memset(szCmd, 0, sizeof(szCmd));
	strcpy_s(szCmd, sizeof(szCmd), "cmd /c  copy \"");
	strcat_s(szCmd, sizeof(szCmd), szOutTmp);
	strcat_s(szCmd, sizeof(szCmd), "\" \"");
	strcat_s(szCmd, sizeof(szCmd), szOutFile);
	strcat_s(szCmd, sizeof(szCmd), "\"");
	system(szCmd);
	return flen;
}


void CMicrosoftPhotosDlg::OnBnClickedButtonselectfile()
{
	// 选择文件
	TCHAR szFilters[] = _T("JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("jpg"), _T("*.jpg"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDITSOURCEFILE, pathName);
	}
}


void CMicrosoftPhotosDlg::OnBnClickedButtonoutputpath()
{
	// 输出路径
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		SetDlgItemText(IDC_EDITOUTPATH, pathName);
	}
}


void CMicrosoftPhotosDlg::OnBnClickedButtonmodifyjpg()
{
	// 解密JPG文件
	TCHAR szSrcJpg[MAX_PATH];
	TCHAR szOutPath[MAX_PATH];
	GetDlgItemText(IDC_EDITSOURCEFILE, szSrcJpg, MAX_PATH);
	GetDlgItemText(IDC_EDITOUTPATH, szOutPath, MAX_PATH);
	CString strInfo;
	if (strlen(szSrcJpg) == 0)
	{
		strInfo.Format("请选择文件,点击选择文件按钮");
	}else
	{
		int flen = FunChangeJpgFile(szSrcJpg, szOutPath);
		strInfo.Format("转换结束,文件名: 文件大小:%d", flen);
	}
	
	SetDlgItemText(IDC_EDITINFO, strInfo);
}
