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

// ��ʼ���Ի���ʱ�Ĵ�����
BOOL CInitializeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CButton	*pButton = ( CButton* )GetDlgItem( IDC_JIUGONGQI );		// �õ���һ���ؼ�
	ASSERT( pButton );
	if ( pButton )
	{
		pButton->SetCheck( BST_CHECKED );	// ʹ��һ���ؼ���ѡ��
	}

	OnBnClickedJiugongqi();		// ���õ�һ���ؼ���ѡ��ʱ�ĺ���

	return TRUE;
}

void CInitializeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// ���� DDX �����ؼ�
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
/*                               ��ȷ�ϡ���Ӧ����                            */
/*****************************************************************************/

void CInitializeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if ( UpdateData() )
	{
		// ��һ��ؼ�����Ϸ����ѡ��
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

		// �ڶ���ؼ���������ɫ��
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
	
	OkButton = 1;	// ����ȷ�ϼ�������

	// ��ո�����ջ
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
/*                 �� Radio Button ������ʱ�Ĵ�����                  */
/***********************************************************************/

// �Ź��壨���˶�ս��
void CInitializeDlg::OnBnClickedJiugongqi()
{
	// TODO: Add your control notification handler code here
	// �õ��ڶ���ؼ��� ��ɫ������ѡ
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

// �Ź��壨�˻���ս��
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

	// Ĭ��ѡ���ɫ
	CButton	*pButton = ( CButton* )GetDlgItem( IDC_BLACK );
	ASSERT( pButton );
	if ( pButton )
	{
		pButton->SetCheck( BST_CHECKED );
	}
}

// �ڰ��壨���˶�ս��
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

// �ڰ���(�˻���ս)
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
