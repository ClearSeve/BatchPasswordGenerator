// BatchPasswordGeneratorDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBatchPasswordGeneratorDlg 对话框
class CBatchPasswordGeneratorDlg : public CDialog
{
// 构造
public:
	CBatchPasswordGeneratorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BATCHPASSWORDGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
    CToolTipCtrl m_Tip;

// 实现
protected:
	HICON m_hMaxIcon;
    HICON m_hMinIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    // 滑块显示数字
    CSliderCtrl m_wndSliderItem;
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
    // 需要生成的密码位数
    UINT m_nItemData;
public:
    afx_msg void OnEnKillfocusEdit1();
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
    afx_msg void OnEnUpdateEdit1();
    //************************************    
    // 函数名称：GetDigitalData    
    // 函数说明：获取随机数字    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数:     
    //************************************    
    int GetDigitalData(int nBit);

    //************************************    
    // 函数名称：DataMaxLetter();    
    // 函数说明：生成大写字母随机字母    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：字符    
    // 参    数:     
    //************************************    
    UCHAR DataMaxLetter();
    
    //************************************    
    // 函数名称：DataMaxLetter();    
    // 函数说明：生成小写字母随机字母    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：字符    
    // 参    数:     
    //************************************    
    UCHAR DataMinLetter();
    
    //************************************    
    // 函数名称：DataCharacter();    
    // 函数说明：生成随机字符    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：字符    
    // 参    数:     
    //************************************    
    UCHAR DataCharacter();
    
    //************************************    
    // 函数名称：DataDigitalChar    
    // 函数说明：获取数字字符    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数：    
    //************************************    
    UCHAR DataDigitalChar();

    //************************************    
    // 函数名称：GetPasswordBit    
    // 函数说明：获取密码的位数    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数:     
    //************************************    
    int GetPasswordBit();
    


public:
    afx_msg void OnBnClickedNew();
public:
    // 密码显示位置
    CEdit m_wndPassword;
public:
    // 小写字母
    BOOL m_bMinLetter;
public:
    // 大写字母
    BOOL m_bMaxLetter;
public:
    //保存需要打开文件的路径
    CString m_strFilePath;
public:
    // 数字
    BOOL m_bDigital;
public:
    // 特殊字符
    BOOL m_bSpecialChar;
public:
    CEdit m_wndEdit1;
public:
    afx_msg void OnBnClickedMinletter();
public:
    afx_msg void OnBnClickedMaxletter();
public:
    afx_msg void OnBnClickedDigital();
public:
    afx_msg void OnBnClickedSpecialchar();
public:
    // 批量生成时候的进度条
    CProgressCtrl m_wndProgress;
public:
    // 获取批量生成的数字
    CEdit m_wndBatchData;
public:
    CButton m_wndOpenFile;
public:
    CButton m_wndCreateData;
    //************************************    
    // 函数名称：JudgeBatch    
    // 函数说明：判断是否是批量生成密码    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数：    
    //************************************    
    void JudgeBatch();
public:
    // 是否是批量生成密码
    BOOL m_bBatch;
public:
    afx_msg void OnBnClickedBatch();
public:
    // 换新密码按钮
    CButton m_wndNew;
public:
    CButton m_wndCopy;
public:
    afx_msg void OnBnClickedOpenfile();
    //************************************    
    // 函数名称：Write    
    // 函数说明：写到黏贴板    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数：    
    //************************************    
    void Write(CString& strText);
public:
    afx_msg void OnBnClickedCopy();

    //************************************    
    // 函数名称：ThreadProc    
    // 函数说明：MFC工作线程处理函数    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：    
    // 参    数：    
    //************************************    
    static UINT ThreadProc(LPVOID pParam);

    //************************************    
    // 函数名称：GetPassword()    
    // 函数说明：获取随机密码    
    // 函数作者：Robin    
    // 做成日期：2015/04/12    
    // 返 回 值：生成后的密码    
    // 参    数：    
    //************************************    
    CString GetPassword();

public:
    afx_msg void OnBnClickedCreate();
public:
    virtual void AssertValid() const;
};
