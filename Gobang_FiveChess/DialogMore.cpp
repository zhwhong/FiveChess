// DialogMore.cpp : 实现文件
//

#include "stdafx.h"
#include "Gobang_FiveChess.h"
#include "DialogMore.h"
#include "afxdialogex.h"


// CDialogMore 对话框

IMPLEMENT_DYNAMIC(CDialogMore, CDialogEx)

CDialogMore::CDialogMore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogMore::IDD, pParent)
{
    m_pChess  = NULL;
}

CDialogMore::~CDialogMore()
{
}

void CDialogMore::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_AI, m_comboxAI);
    DDX_Control(pDX, IDC_COMBO_VS_MODE, m_comboxVSMode);
}


BEGIN_MESSAGE_MAP(CDialogMore, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDialogMore::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogMore 消息处理程序


void CDialogMore::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    if(m_pChess)
    {
        m_pChess->SetAIDepth(m_comboxAI.GetCurSel());

        switch(m_comboxVSMode.GetCurSel())
        {
        case    0:
            m_pChess->SetVSMode(PERSON_VS_MACHINE);
            break;
        case    1:
            m_pChess->SetVSMode(PERSON_VS_PERSON);
            break;
         case    2:
            m_pChess->SetVSMode(MACHINE_VS_MACHINE);
            break;
        default:
            break;
        }       
    }
   
    CDialogEx::OnOK();
}


BOOL CDialogMore::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化       
    m_comboxAI.SetCurSel(2);            // 中级
    m_comboxVSMode.SetCurSel(0);		// 人机
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void    CDialogMore::SetChess(CChess  *pChess)
{
    m_pChess    = pChess;
}