// InitializeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chess.h"
#include "InitializeDlg.h"

#include "JiuGongQi.h"
#include "JiuGongQi_rj.h"
#include "Othello.h"
#include "Othello_rj.h"

#include <stack>

extern	int ChessType;
extern	int human;
extern  int computer;
extern	int OkButton;
extern	std::stack< JiuGongQi >	st1;
extern	std::stack< JiuGongQi_rj >	st2;
extern	std::stack< Othello >	st3;
extern	std::stack< Othello_rj >	st4;


// CInitializeDlg dialog

IMPLEMENT_DYNAMIC(CInitializeDlg, CDialog)

CInitializeDlg::CInitializeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitializeDlg::IDD, pParent)
	, m_iAnswer(0)
	, m_iAnswer1(0)
{
}

CInitializeDlg::~CInitializeDlg()
{
}

// 初始化对话框时的处理函数
BOOL CInitializeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CButton	*pButton = ( CButton* )GetDlgItem( IDC_JIUGONGQI );		// 得到第一个控件
	ASSERT( pButton );
	if ( pButton )
	{
		pButton->SetCheck( BST_CHECKED );	// 使第一个控件被选中
	}

	OnBnClickedJiugongqi();		// 调用第一个控件被选中时的函数

	return TRUE;
}

void CInitializeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// 两个 DDX 变量控件
	DDX_Radio( pDX, IDC_JIUGONGQI, m_iAnswer );
	DDX_Radio( pDX, IDC_BLACK, m_iAnswer1 );
}


BEGIN_MESSAGE_MAP(CInitializeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CInitializeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_JIUGONGQI, &CInitializeDlg::OnBnClickedJiugongqi)
	ON_BN_CLICKED(IDC_JIUGONGQI_RJ, &CInitializeDlg::OnBnClickedJiugongqiRj)
	ON_BN_CLICKED(IDC_OTHELLO, &CInitializeDlg::OnBnClickedOthello)
	ON_BN_CLICKED(IDC_OTHELLO_RJ, &CInitializeDlg::OnBnClickedOthelloRj)
END_MESSAGE_MAP()


// CInitializeDlg message handlers

/*****************************************************************************/
/*                               “确认”响应函数                            */
/*****************************************************************************/

void CInitializeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if ( UpdateData() )
	{
		// 第一组控件（游戏类型选择）
		switch( m_iAnswer )
		{
			case 0:
				ChessType = 1;
				break;
			case 1:
				ChessType = 2;
				break;
			case 2:
				ChessType = 3;
				break;
			case 3:
				ChessType = 4;
				break;
		}

		// 第二组控件（棋子颜色）
		switch( m_iAnswer1 )
		{
			case 0:
				human = 1;
				computer = 0;
				break;
			case 1:
				human = 0;
				computer = 1;
				break;
		}
	}
	
	OkButton = 1;	// 表明确认键被按下

	// 清空各个堆栈
	while ( st1.size() )
		st1.pop();
	while ( st2.size() )
		st2.pop();
	while ( st3.size() )
		st3.pop();
	while ( st3.size() )
		st3.pop();
	while ( st4.size() )
		st4.pop();

	OnOK();
}

/***********************************************************************/
/*                 各 Radio Button 被按下时的处理函数                  */
/***********************************************************************/

// 九宫棋（人人对战）
void CInitializeDlg::OnBnClickedJiugongqi()
{
	// TODO: Add your control notification handler code here
	// 得到第二组控件， 颜色都不可选
	CWnd	*pWnd;
	
	pWnd = GetDlgItem( IDC_BLACK );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( FALSE );

	pWnd = GetDlgItem( IDC_WHITE );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( FALSE );
}

// 九宫棋（人机对战）
void CInitializeDlg::OnBnClickedJiugongqiRj()
{
	// TODO: Add your control notification handler code here
	CWnd	*pWnd;

	pWnd = GetDlgItem( IDC_BLACK );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( TRUE );

	pWnd = GetDlgItem( IDC_WHITE );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( TRUE );

	// 默认选择黑色
	CButton	*pButton = ( CButton* )GetDlgItem( IDC_BLACK );
	ASSERT( pButton );
	if ( pButton )
	{
		pButton->SetCheck( BST_CHECKED );
	}
}

// 黑白棋（人人对战）
void CInitializeDlg::OnBnClickedOthello()
{
	// TODO: Add your control notification handler code here
	CWnd	*pWnd;

	pWnd = GetDlgItem( IDC_BLACK );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( FALSE );

	pWnd = GetDlgItem( IDC_WHITE );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( FALSE );
}

// 黑白棋(人机对战)
void CInitializeDlg::OnBnClickedOthelloRj()
{
	// TODO: Add your control notification handler code here
	CWnd	*pWnd;

	pWnd = GetDlgItem( IDC_BLACK );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( TRUE );

	pWnd = GetDlgItem( IDC_WHITE );
	ASSERT( pWnd );
	if( pWnd )
		pWnd->EnableWindow( TRUE );

	CButton	*pButton = ( CButton* )GetDlgItem( IDC_BLACK );
	ASSERT( pButton );
	if ( pButton )
	{
		pButton->SetCheck( BST_CHECKED );
	}
}
