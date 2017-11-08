// BatchPasswordGeneratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatchPasswordGenerator.h"
#include "BatchPasswordGeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBatchPasswordGeneratorDlg 对话框




CBatchPasswordGeneratorDlg::CBatchPasswordGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchPasswordGeneratorDlg::IDD, pParent)
    , m_nItemData(1)
    , m_bMinLetter(TRUE)
    , m_bMaxLetter(FALSE)
    , m_bDigital(TRUE)
    , m_bSpecialChar(FALSE)
    , m_bBatch(FALSE)
{
	m_hMaxIcon = AfxGetApp()->LoadIcon(IDI_MAX);
    m_hMinIcon = AfxGetApp()->LoadIcon(IDI_MIN);
    

}

void CBatchPasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER, m_wndSliderItem);
    DDX_Text(pDX, IDC_EDIT1, m_nItemData);
    DDV_MinMaxUInt(pDX, m_nItemData, 1, 256);
    DDX_Control(pDX, IDC_EDIT2, m_wndPassword);
    DDX_Check(pDX, IDC_MINLETTER, m_bMinLetter);
    DDX_Check(pDX, IDC_MAXLETTER, m_bMaxLetter);
    DDX_Check(pDX, IDC_DIGITAL, m_bDigital);
    DDX_Check(pDX, IDC_SPECIALCHAR, m_bSpecialChar);
    DDX_Control(pDX, IDC_EDIT1, m_wndEdit1);
    DDX_Control(pDX, IDC_PROGRESS, m_wndProgress);
    DDX_Control(pDX, IDC_BATCHDATA, m_wndBatchData);
    DDX_Control(pDX, IDC_OPENFILE, m_wndOpenFile);
    DDX_Control(pDX, IDC_CREATE, m_wndCreateData);
    DDX_Check(pDX, IDC_BATCH, m_bBatch);
    DDX_Control(pDX, IDC_NEW, m_wndNew);
    DDX_Control(pDX, IDC_COPY, m_wndCopy);
}

BEGIN_MESSAGE_MAP(CBatchPasswordGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_EN_KILLFOCUS(IDC_EDIT1, &CBatchPasswordGeneratorDlg::OnEnKillfocusEdit1)
    ON_WM_HSCROLL()
    ON_EN_UPDATE(IDC_EDIT1, &CBatchPasswordGeneratorDlg::OnEnUpdateEdit1)
    ON_BN_CLICKED(IDC_NEW, &CBatchPasswordGeneratorDlg::OnBnClickedNew)
    ON_BN_CLICKED(IDC_MINLETTER, &CBatchPasswordGeneratorDlg::OnBnClickedMinletter)
    ON_BN_CLICKED(IDC_MAXLETTER, &CBatchPasswordGeneratorDlg::OnBnClickedMaxletter)
    ON_BN_CLICKED(IDC_DIGITAL, &CBatchPasswordGeneratorDlg::OnBnClickedDigital)
    ON_BN_CLICKED(IDC_SPECIALCHAR, &CBatchPasswordGeneratorDlg::OnBnClickedSpecialchar)
    ON_BN_CLICKED(IDC_BATCH, &CBatchPasswordGeneratorDlg::OnBnClickedBatch)
    ON_BN_CLICKED(IDC_OPENFILE, &CBatchPasswordGeneratorDlg::OnBnClickedOpenfile)
    ON_BN_CLICKED(IDC_COPY, &CBatchPasswordGeneratorDlg::OnBnClickedCopy)
    ON_BN_CLICKED(IDC_CREATE, &CBatchPasswordGeneratorDlg::OnBnClickedCreate)
END_MESSAGE_MAP()


// CBatchPasswordGeneratorDlg 消息处理程序

BOOL CBatchPasswordGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hMaxIcon, TRUE);			// 设置大图标
	SetIcon(m_hMinIcon, FALSE);		// 设置小图标

	// 初始化操作
    //设置滑块的起始位置与终止位置
    m_wndSliderItem.SetRange(1,256);
    EnableToolTips(TRUE);
    m_Tip.Create(this);
    m_Tip.Activate(TRUE);

    
    m_Tip.AddTool(GetDlgItem(IDC_BATCHDATA),TEXT("填写批量生成密码的个数")); //添加


    //初始化 是否是批量生成信息
    JudgeBatch();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBatchPasswordGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBatchPasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hMaxIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CBatchPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hMaxIcon);
}


BOOL CBatchPasswordGeneratorDlg::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_MOUSEMOVE)
        m_Tip.RelayEvent(pMsg);
    
    return CDialog::PreTranslateMessage(pMsg);
}
//失去输入焦点,将数字放入变量
void CBatchPasswordGeneratorDlg::OnEnKillfocusEdit1()
{   
    //将控件的内容放入到变量
    UpdateData();
    //移动滑块位置
    m_wndSliderItem.SetPos(m_nItemData);
}
//************************************    
// 函数名称：OnHScroll    
// 函数说明：点击水平滚动条    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数:     
//************************************    
void CBatchPasswordGeneratorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    //获取窗口上的水平滑块
    CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
    //获取滑块位置
    int nPosData = pSlider->GetPos();
    //滑块的位置设置到Edit框里
    CString str;
    str.Format(TEXT("%d"),nPosData);
    //更新控件数据 将变量的数据放入控件
    m_wndEdit1.SetWindowText(str);
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
//************************************    
// 函数名称：OnEnUpdateEdit1    
// 函数说明：密码位数即将显示    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数:     
//************************************    
void CBatchPasswordGeneratorDlg::OnEnUpdateEdit1()
{
    //获取新变量
    UpdateData();
    //移动滑块位置
    m_wndSliderItem.SetPos(m_nItemData);
}

//************************************    
// 函数名称：GetDigitalData    
// 函数说明：获取随机数字    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：返回随机数    
// 参    数:     
//************************************    
int CBatchPasswordGeneratorDlg::GetDigitalData(int nBit)
{
    int nData;
    //进行格式化 nBit : 51 则0~50
    nData = rand()%nBit;
    return nData;
}

//************************************    
// 函数名称：DataMaxLetter();    
// 函数说明：生成大写字母随机字母    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数:     
//************************************ 
UCHAR CBatchPasswordGeneratorDlg::DataMaxLetter()
{
    //A从65开始
    UCHAR cChar = 65;
    //获取随机数 0~25
    int nData = GetDigitalData(26);
    //A+获取到的随机数,产生随机大写字母
    cChar += nData;
    //返回这个大写字母 
    return cChar;
}

//************************************    
// 函数名称：DataMaxLetter();    
// 函数说明：生成小写字母随机字母    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：字符    
// 参    数:     
//************************************    
UCHAR CBatchPasswordGeneratorDlg::DataMinLetter()
{
    //a从97开始
    UCHAR cChar = 97;
    //获取随机数 0~25
    int nData = GetDigitalData(26);
    //a+获取到的随机数,产生随机小写字母
    cChar += nData;
    //返回这个小写字母 
    return cChar;
}

//************************************
// 函数名称：DataDigitalChar    
// 函数说明：获取数字字符    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数：    
//************************************
UCHAR CBatchPasswordGeneratorDlg::DataDigitalChar()
{
    //A从65开始
    UCHAR cChar = 48;
    //获取随机数0~9
    int nData = GetDigitalData(10);
    //A+获取到的随机数,产生随机大写字母
    cChar += nData;
    //返回这个大写字母 
    return cChar;
}

//************************************    
// 函数名称：DataCharacter();    
// 函数说明：生成随机字符    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：字符    
// 参    数:     
//************************************    
UCHAR CBatchPasswordGeneratorDlg::DataCharacter()
{
    //获取随机数
    int nData= GetDigitalData(32);
    switch(nData)
    {
        case 0://!
            return 33;
            break;
        case 1://"
            return 34; 
            break;
        case 2://#
            return 35;
            break;
        case 3://$
            return 36;
            break;
        case 4://%
            return 37;
            break;
        case 5://&
            return 38;
            break;
        case 6://'
            return 39;
            break;
        case 7://(
            return 40;
            break;
        case 8://)
            return 41;
            break;
        case 9://*
            return 42;
            break;
        case 10://+
            return 43;
            break;
        case 11://
            return 44;
            break;
        case 12://-
            return 45;
            break;
        case 13://.
            return 46;
            break;
        case 14:///
            return 47;
            break;
        case 15://:
            return 58;
            break;
        case 16://;
            return 59;
            break;
        case 17://<
            return 60;
            break;
        case 18://=
            return 61;
            break;
        case 19://>
            return 62;
            break;
        case 20://?
            return 63;
            break;
        case 21://@
            return 64;
            break;
        case 22://[
            return 91;
            break;
        case 23:/*/*/
            return 92;
            break;
        case 24://]
            return 93;
            break;
        case 25://^
            return 94;
            break;
        case 26://_
            return 95;
            break;
        case 27://`
            return 96;
            break;
        case 28://{
            return 123;
            break;
        case 29://|
            return 124;
            break;
        case 30://}
            return 125;
            break;
        case 31://~
            return 126;
            break;
    }
    //其他都不是返回!字符
    return 33;
}

//************************************    
// 函数名称：OnBnClickedNew    
// 函数说明：点击新按钮    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数:     
//************************************    
void CBatchPasswordGeneratorDlg::OnBnClickedNew()
{
    CString strPassword = GetPassword();
    //将字符串设置到Edit中
    m_wndPassword.SetWindowText(strPassword);
}
//************************************    
// 函数名称：GetPasswordBit    
// 函数说明：获取密码的位数    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：返回密码的位数    
// 参    数:     
//************************************    
int CBatchPasswordGeneratorDlg::GetPasswordBit()
{
    //返回密码位数
    return m_nItemData;
}

//点击小写字母选项
void CBatchPasswordGeneratorDlg::OnBnClickedMinletter()
{
    //获取到最新数据
    UpdateData();
    //判断其他三个是否勾选
    /*
    if (m_bMaxLetter!=TRUE||m_bDigital!=TRUE||m_bSpecialChar!=TRUE)
    {
        AfxMessageBox(TEXT("您不能什么都不勾选,就让我生成!您可以选择:小写字母|大写字母|数字|特殊字符"));
    }
    */

}
//点击大写字母选项
void CBatchPasswordGeneratorDlg::OnBnClickedMaxletter()
{
    // TODO: 在此添加控件通知处理程序代码
}
//点击数字选项
void CBatchPasswordGeneratorDlg::OnBnClickedDigital()
{
    // TODO: 在此添加控件通知处理程序代码
}
//点击特殊字符
void CBatchPasswordGeneratorDlg::OnBnClickedSpecialchar()
{
    // TODO: 在此添加控件通知处理程序代码
}

//************************************ 
// 函数名称：JudgeBatch    
// 函数说明：判断是否是批量生成密码    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数：    
//************************************ 
void CBatchPasswordGeneratorDlg::JudgeBatch()
{
    //获取对话框的最新数据
    UpdateData();
    //判断是否勾选批量按钮
    if(m_bBatch!=TRUE)
    {//没有勾选批量生成
        //显示非批量处理的信息 
        //显示密码Edit框
        m_wndPassword.ShowWindow(SW_SHOW);
        //显示拷贝按钮
        m_wndCopy.ShowWindow(SW_SHOW);
        //显示更换密码按钮
        m_wndNew.ShowWindow(SW_SHOW);
   
        //隐藏批量处理的信息
        //隐藏进度条
        m_wndProgress.ShowWindow(SW_HIDE);
        //隐藏生成按钮
        m_wndCreateData.ShowWindow(SW_HIDE);
        //隐藏输入生成多少密码的输入框
        m_wndBatchData.ShowWindow(SW_HIDE);
        //隐藏打开文件按钮
        m_wndOpenFile.ShowWindow(SW_HIDE);
    }else
    {//勾选批量生成
        //隐藏非批量处理的信息 
        //隐藏密码Edit框
        m_wndPassword.ShowWindow(SW_HIDE);
        //隐藏拷贝按钮
        m_wndCopy.ShowWindow(SW_HIDE);
        //隐藏更换密码按钮
        m_wndNew.ShowWindow(SW_HIDE);

        //显示批量处理的信息
        //显示进度条
        m_wndProgress.ShowWindow(SW_SHOW);
        //显示生成按钮
        m_wndCreateData.ShowWindow(SW_SHOW);
        //显示输入生成多少密码的输入框
        m_wndBatchData.ShowWindow(SW_SHOW);
        //显示打开文件按钮
        m_wndOpenFile.ShowWindow(SW_SHOW);
    }
}
//点击批量按钮
void CBatchPasswordGeneratorDlg::OnBnClickedBatch()
{
    JudgeBatch();
}
//点击选择要保存的文件位置
void CBatchPasswordGeneratorDlg::OnBnClickedOpenfile()
{
    //构造文件对话框
    CFileDialog FileDialog(FALSE,TEXT("*.txt"),TEXT("PasswordData.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,TEXT("文本文件(*.txt)|*.txt||"),GetDlgItem(IDD_BATCHPASSWORDGENERATOR_DIALOG));
    //显示窗口 并判断是否点击保存
    if (FileDialog.DoModal()!=IDOK)
    {//不是点击保存
        return ;//跳出
    }
    //保存窗口名称
    CString strWindowsName;
    WCHAR szText[100] = {0};
    //获取窗口名称
    LoadString(AfxGetApp()->m_hInstance,IDS_WINDOWSNAME,szText,100);
    strWindowsName.Format(TEXT("%s"),szText);
    //获取保存的文件名名称
    CString strFileName = FileDialog.GetFileTitle();
    //保存新窗口名称
    CString strNewWinName;
    //构造新窗口名称
    strNewWinName.Format(TEXT("%s   %s"),strWindowsName,strFileName);
    //将新窗口名称设置到窗口
    SetWindowText(strNewWinName);
    //获取文件的全路径,复制到变量中
    m_strFilePath = FileDialog.GetPathName();

}
//************************************    
// 函数名称：Write    
// 函数说明：写到黏贴板    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数：    
//************************************    
void CBatchPasswordGeneratorDlg::Write(CString& strText)
{
       /*
    OpenClipboard打开剪切板：指定关联到打开的剪切板的窗口句柄，传入NULL表示关联到当前任务。每次只允许一
    个进程打开并访问。每打开一次就要关闭，否则其他进程无法访问剪切板。
    EmptyClipboard清空剪切板：写入前必须先清空，得到占有权
    */
    if (::OpenClipboard(m_hWnd) &&::EmptyClipboard())
    {
        //根据环境变量获取数据长度
        size_t cbStr = (strText.GetLength() + 1) * sizeof(TCHAR);

        //在堆上动态分配以字节为单位的全局内存区域。成功则指向该内存，失败NULL。参数：1.分配内存属性，2.大小
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr); 

        if (hMem == NULL) 
        {
            //关闭剪切板,释放剪切板所有权，关闭后就不能写入数据
            CloseClipboard();
            return; 
        }

        //锁定由GlobalAlloc分配的内存，并将内存对象的锁定计数器+1；成功返回指向内存对象起始地址的指针。失败NULL
        LPTSTR lpDest = (LPTSTR)GlobalLock(hMem);
        /*
        系统为每个全局内存对象维护一个锁定计数器，初始为0，GlobalLock使计数器+1，
        */

        //拷贝数据到剪贴板内存。
        memcpy_s(lpDest, cbStr, strText.LockBuffer(), cbStr);
        strText.UnlockBuffer();

        //解除内存锁定，将属性为GMEM_MOVEABLE的内存对象计数器-1.
        GlobalUnlock(hMem); 
        /*
        GlobalUnLock计数器-1.一旦计数器值大于0，这块内存区域将不允许被移动或删除，只
        有当为0时，才解除对这块内存的锁定。如果分配时GMEM_FIXED属性，计数器一直为0

        */

        //根据环境变量设置数据格式
        UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR))?CF_UNICODETEXT:CF_TEXT;

        //设置数据到剪贴板。执行成功，返回数据句柄，否则返回NULL
        if(SetClipboardData(uiFormat, hMem) == NULL)
        {
            CloseClipboard();
            return;
        }

        CloseClipboard();
    }
}
//点击复制按钮
void CBatchPasswordGeneratorDlg::OnBnClickedCopy()
{
    //获取密码
    CString strPassword;
    m_wndPassword.GetWindowText(strPassword);
    //判断获取到的密码是否为空
    if (strPassword==TEXT(""))
    {
        //密码为空,无法复制
        AfxMessageBox(TEXT("密码为空,不能进行复制"));
        return ;
    }
    //拷贝到黏贴板
    Write(strPassword);
}
//************************************    
// 函数名称：ThreadProc    
// 函数说明：MFC工作线程处理函数    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：    
// 参    数：    
//************************************    
UINT CBatchPasswordGeneratorDlg::ThreadProc(LPVOID pParam)
{
    //获取指针
    CBatchPasswordGeneratorDlg* pDlg =  (CBatchPasswordGeneratorDlg*)pParam;
    //获取需要生成多少
    CString strBatchData;
    //获取数字
    pDlg->m_wndBatchData.GetWindowText(strBatchData);
    int nData = _ttoi(strBatchData);
    //设置进度条开始与终止
    pDlg->m_wndProgress.SetRange32(0,nData);
    //打开文件
    if (pDlg->m_strFilePath==TEXT(""))//判断是否设置目录
    {
        AfxMessageBox(TEXT("您没有选择文件保存的位置,请点击“...”按钮,选择文件存放位置"));
        return 0;
    }
    
    CFile File;
    //以写入的方式打开文件
    File.Open(pDlg->m_strFilePath,CFile::modeCreate | CFile::modeWrite);
    //设置生成按钮灰色
    pDlg->m_wndCreateData.EnableWindow(FALSE);
    //用于保存密码
    for (int nIndex = 0;nIndex<nData;nIndex++)
    {
        //205
        CString strPassword;
        strPassword = pDlg->GetPassword();
        //获取到Unicode 码的字符串
        char szText[MAX_PATH] = {0};
        strPassword+= TEXT("\r\n");
        //转换成Ascii码
        WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strPassword, -1,szText,sizeof(szText), NULL,NULL);
        //写入到文件
        File.Write(szText,strlen(szText));
        //增加进度条
        //获取进度条当前位置
        int nPos = pDlg->m_wndProgress.GetPos();
        //增加一个进度
        nPos++;
        //设置进度条新位置
        pDlg->m_wndProgress.SetPos(nPos);
    }
    //将生成按钮取消灰色
    pDlg->m_wndCreateData.EnableWindow(TRUE);
    //关闭文件
    File.Close();
    //批量生成密码完毕
    AfxMessageBox(TEXT("批量生成密码完毕"));
    return 0;
    
}

//************************************    
// 函数名称：GetPassword()    
// 函数说明：获取随机密码    
// 函数作者：Robin    
// 做成日期：2015/04/12    
// 返 回 值：生成后的密码    
// 参    数：    
//************************************    
CString CBatchPasswordGeneratorDlg::GetPassword()
{
    UpdateData(TRUE);//将控件内容放置到变量
    //判断四个选项是否勾选中
    //if (m_bMinLetter==FALSE||m_bMaxLetter==FALSE||m_bDigital==FALSE||m_bSpecialChar==FALSE)
    //{//全部都没有勾选
    //    AfxMessageBox(TEXT("您必须选中一项,您可以选择:小写字母|大写字母|数字|特殊字符"));
    //    return NULL;
    //}
    //获取密码的位数
    int nPasswordBit =  GetPasswordBit();
    CString str1;//记录字符串
    CString str2;//临时字符串
    //循环获取字符
    for (int nIndex = 0;nIndex<nPasswordBit;nIndex++)
    {

        int nItem = GetDigitalData(4); //获取随机数0~3
        switch(nItem)
        {
        case 0:
            {
                //判断是否能获取小写字母
                if(m_bMinLetter==TRUE)
                {//选中
                    //获取小写字母
                    str2 = (char)DataMinLetter();
                }else
                {//没有勾选中
                    //减掉本次的判断
                    nIndex--;
                    //跳出循环
                    continue;
                }
            }
            break;
        case 1:
            {
                //判断是否能获取大写字母
                if(m_bMaxLetter==TRUE)
                {
                    //获取大写字母
                    str2 = (char)DataMaxLetter();
                }else
                {//没有勾选中
                    //减掉本次的判断
                    nIndex--;
                    //跳出循环
                    continue;
                }
            }
            break;
        case 2:
            {
                //判断是否能获取数字
                if(m_bDigital==TRUE)
                {   
                    //获取数字字符
                    str2 = (char)DataDigitalChar();

                }else
                {//没有勾选中
                    //减掉本次的判断
                    nIndex--;
                    //跳出循环
                    continue;
                }
            }
            break;
        case 3:
            {
                //判断是否能获取特殊字符
                if(m_bSpecialChar==TRUE)
                {
                    //获取特殊字符
                    str2 = (char)DataCharacter();
                }else
                {//没有勾选中
                    //减掉本次的判断
                    nIndex--;
                    //跳出循环
                    continue;
                }
            }
            break;
        }

        str1 += str2;//将临时的与记录的字符串相加
    }
    return str1;
}
void CBatchPasswordGeneratorDlg::OnBnClickedCreate()
{
    AfxBeginThread(ThreadProc,this);
}


void CBatchPasswordGeneratorDlg::AssertValid() const
{
//    CDialog::AssertValid();
//        if (m_hWnd == NULL)
//        return;     // null (unattached) windows are valid
//
//// check for special wnd??? values
//    ASSERT(HWND_TOP == NULL);       // same as desktop
//    if (m_hWnd == HWND_BOTTOM)
//        ASSERT(this == &CWnd::wndBottom);
//    else if (m_hWnd == HWND_TOPMOST)
//        ASSERT(this == &CWnd::wndTopMost);
//    else if (m_hWnd == HWND_NOTOPMOST)
//        ASSERT(this == &CWnd::wndNoTopMost);
//    else
//    {
//        // should be a normal window
//        ASSERT(::IsWindow(m_hWnd));

// should also be in the permanent or temporary handle map
/*        CHandleMap* pMap = afxMapHWND();
        ASSERT(pMap != NULL);

CObject* p;
        ASSERT((p = pMap->LookupPermanent(m_hWnd)) != NULL ||
            (p = pMap->LookupTemporary(m_hWnd)) != NULL);
        ASSERT((CWnd*)p == this);   // must be us
*/
    // TODO: 在此添加专用代码和/或调用基类
        // Note: if either of the above asserts fire and you are
        // writing a multithreaded application, it is likely that
        // you have passed a C++ object from one thread to another
        // and have used that object in a way that was not intended.
        // (only simple inline wrapper functions should be used)
        //
        // In general, CWnd objects should be passed by HWND from
        // one thread to another.  The receiving thread can wrap
        // the HWND with a CWnd object by using CWnd::FromHandle.
        //
        // It is dangerous to pass C++ objects from one thread to
        // another, unless the objects are designed to be used in
        // such a manner.
   // }
}
