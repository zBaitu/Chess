// ChessView.cpp : CChessView ���ʵ��
//

#include "stdafx.h"
#include "Chess.h"
#include "ChessDoc.h"
#include "ChessView.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �ĸ�ȫ�ֱ���
int	ChessType = 0;
int human = 0, computer = 0;
int OkButton = 0;
int StackSize;

// �������ĸ����ʵ�������涨��Ķ�ջ
extern std::stack< JiuGongQi >	st1;
extern std::stack< JiuGongQi >	st11;

extern std::stack< JiuGongQi_rj >	st2;
extern std::stack< JiuGongQi_rj >	st22;

extern std::stack< Othello >	st3;
extern std::stack< Othello >	st33;

extern std::stack< Othello_rj >	st4;
extern std::stack< Othello_rj >	st44;



// CChessView

IMPLEMENT_DYNCREATE(CChessView, CFormView)

BEGIN_MESSAGE_MAP(CChessView, CFormView)
	ON_COMMAND(ID_FILE_NEW, &CChessView::OnFileNew)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_COMMAND(ID_EDIT_UNDO, &CChessView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CChessView::OnUpdateEditUndo)
	ON_COMMAND(ID_FILE_OPEN, &CChessView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChessView::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CChessView::OnUpdateFileSave)
END_MESSAGE_MAP()

// CChessView ����/����

/******************************************************************/
/*                ��CChessView ��ʼ��ʱ����λͼ��Դ               */
/******************************************************************/

CChessView::CChessView()
	: CFormView(CChessView::IDD)
	, b_discs(0)
	, b_moves(0)
	, w_discs(0)
	, w_moves(0)
{
	// TODO: �ڴ˴���ӹ������
	m_Bitmaps[ 0 ].LoadBitmap( IDB_BITMAP1 );
	m_Bitmaps[ 1 ].LoadBitmap( IDB_BITMAP2 );
	m_Bitmaps[ 2 ].LoadBitmap( IDB_BITMAP3 );
	m_Bitmaps[ 3 ].LoadBitmap( IDB_BITMAP4 );
	m_Bitmaps[ 4 ].LoadBitmap( IDB_BITMAP5 );
	m_Bitmaps[ 5 ].LoadBitmap( IDB_BITMAP6 );
	m_Bitmaps[ 6 ].LoadBitmap( IDB_BITMAP7 );
	m_Bitmaps[ 7 ].LoadBitmap( IDB_BITMAP8 );
	m_Bitmaps[ 8 ].LoadBitmap( IDB_BITMAP9 );
	m_Bitmaps[ 9 ].LoadBitmap( IDB_BITMAP10 );
	m_Bitmaps[ 10 ].LoadBitmap( IDB_BITMAP11 );
	m_Bitmaps[ 11 ].LoadBitmap( IDB_BITMAP12 );
	m_Bitmaps[ 12 ].LoadBitmap( IDB_BITMAP13 );
	m_Bitmaps[ 13 ].LoadBitmap( IDB_BITMAP14 );
	m_Bitmaps[ 14 ].LoadBitmap( IDB_BITMAP15 );
	m_Bitmaps[ 15 ].LoadBitmap( IDB_BITMAP16 );
	m_Bitmaps[ 16 ].LoadBitmap( IDB_BITMAP17 );
	m_Bitmaps[ 17 ].LoadBitmap( IDB_BITMAP18 );
	m_Bitmaps[ 18 ].LoadBitmap( IDB_BITMAP19 );
	m_Bitmaps[ 19 ].LoadBitmap( IDB_BITMAP20 );
	m_Bitmaps[ 20 ].LoadBitmap( IDB_BITMAP21 );
	m_Bitmaps[ 21 ].LoadBitmap( IDB_BITMAP22 );
	m_Bitmaps[ 22 ].LoadBitmap( IDB_BITMAP23 );
	m_Bitmaps[ 23 ].LoadBitmap( IDB_BITMAP24 );
	m_Bitmaps[ 24 ].LoadBitmap( IDB_BITMAP25 );
	m_Bitmaps[ 25 ].LoadBitmap( IDB_BITMAP26 );
	m_Bitmaps[ 26 ].LoadBitmap( IDB_BITMAP27 );
	m_Bitmaps[ 27 ].LoadBitmap( IDB_BITMAP28 );
	m_Bitmaps[ 28 ].LoadBitmap( IDB_BITMAP29 );
	m_Bitmaps[ 29 ].LoadBitmap( IDB_BITMAP30 );
	m_Bitmaps[ 30 ].LoadBitmap( IDB_BITMAP31 );
	m_Bitmaps[ 31 ].LoadBitmap( IDB_BITMAP32 );
	m_Bitmaps[ 32 ].LoadBitmap( IDB_BITMAP33 );
	m_Bitmaps[ 33 ].LoadBitmap( IDB_BITMAP34 );
	m_Bitmaps[ 34 ].LoadBitmap( IDB_BITMAP35 );
	m_Bitmaps[ 35 ].LoadBitmap( IDB_BITMAP36 );
	m_Bitmaps[ 36 ].LoadBitmap( IDB_BITMAPemptyRT );
	m_Bitmaps[ 37 ].LoadBitmap( IDB_BITMAPblackRT );
	m_Bitmaps[ 38 ].LoadBitmap( IDB_BITMAPblackNRT );
	m_Bitmaps[ 39 ].LoadBitmap( IDB_BITMAPwhiteRT );
	m_Bitmaps[ 40 ].LoadBitmap( IDB_BITMAPwhiteNRT );
	m_Bitmaps[ 41 ].LoadBitmap( IDB_BITMAPattackRT );
}

CChessView::~CChessView()
{
}

void CChessView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	// ���DDX �ؼ�����
	DDX_Text( pDX, IDC_B_DISCS, b_discs );
	DDX_Text( pDX, IDC_B_MOVES, b_moves );
	DDX_Text( pDX, IDC_W_DISCS, w_discs );
	DDX_Text( pDX, IDC_W_MOVES, w_moves );
	DDX_Control(pDX, IDC_LIST1, lbx);
}

BOOL CChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CChessView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CChessView ���

#ifdef _DEBUG
void CChessView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChessView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChessDoc* CChessView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*)m_pDocument;
}
#endif //_DEBUG


// CChessView ��Ϣ�������

/***********************************************************************/
/*                           ��Ϸ��ʼ������                            */
/***********************************************************************/

// ��Ӧ ������֡���������
void CChessView::OnFileNew()
{
	// TODO: Add your command handler code here
	CInitializeDlg	dlg;
	dlg.DoModal();		// ���á���Ϸ��ʼѡ��Ի���
	if ( OkButton == 1 )	// ����ȷ�ϡ���ť����ʱ
	{
		OkButton = 0;
		Initialize();	// ��ʼ����Ϸ��������ʼ���̣� ���˫����ʼ��Ϣ
	}
}

// ��ʼ����Ϸ����
void CChessView::Initialize()
{
	CClientDC	ClientDC( this );
	
	// �Ź��壨���˶�ս��
	if ( ChessType == 1 )
	{
		jiugongqi.Reset();		// ��ʼ����ı���
		
		Draw_JiuGongQi( &ClientDC, 1 );		// ��������
		b_discs = 0;
		w_discs = 0;
		b_moves = 9;
		w_moves = 8;
		UpdateData( FALSE );	// ���ĸ� Edit Control �������ʼ��Ϣ
		lbx.ResetContent();		// ��� List Box �ϵ���Ϣ
		st1.push( jiugongqi );	// �ѵ�һ�������Ϣѹ��ջ��
		Draw_Color( 1 );		// �ڡ��ֵ�������廭����ɫ����
	}

	// �Ź��壨�˻���ս��
	if ( ChessType == 2 )
	{
		jiugongqi_rj.Reset();
		
		Draw_JiuGongQi( &ClientDC, 2 );
		b_discs = 0;
		w_discs = 0;
		b_moves = 9;
		w_moves = 8;
		UpdateData( FALSE );
		lbx.ResetContent();
		st2.push( jiugongqi_rj );
		Draw_Color( 1 );

		// ����ǵ������µĻ�
		if ( computer == 1 )
		{
			jiugongqi_rj.Main( 0, 0, human, computer );		// �õ���˼����������
			
			Draw_JiuGongQi( &ClientDC, 2 );
			b_discs = 1;
			w_discs = 0;
			b_moves = 7;
			w_moves = 8;
			UpdateData( FALSE );
			lbx.ResetContent();
			
			// �� List Box ����������������Ϣ
			CString	str;
			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "Black", 
					jiugongqi_rj.Gety() + 64, jiugongqi_rj.Getx() );			
			lbx.AddString( str );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );	// ʼ���ø������������һ������
			st2.push( jiugongqi_rj );

			Draw_Color( 2 );	// �ڡ��ֵ�������廭����ɫ����
		}
	}

	// �ڰ��壨���˶�ս��
	if ( ChessType == 3 )
	{
		othello.Reset();
		
		Draw_Othello( &ClientDC, 1 );
		othello.SetKexing();	// ʹ othello �� Kexing ������һ��ʹ��һ��������
		b_discs = othello.GetFirstsum();
		w_discs = othello.GetSecondsum();
		b_moves = 4;
		w_moves = 0;
		UpdateData( FALSE );
		lbx.ResetContent();

		st3.push( othello );

		Draw_Color( 1 );
	}
		
	// �ڰ��壨�˻���ս��
	if ( ChessType == 4 )
	{
		othello_rj.Reset();
		
		Draw_Othello( &ClientDC, 2 );
		othello_rj.SetKexing();
		b_discs = othello_rj.GetFirstsum();
		w_discs = othello_rj.GetSecondsum();
		b_moves = 4;
		w_moves = 0;
		UpdateData( FALSE );
		lbx.ResetContent();
		
		st4.push( othello_rj );

		Draw_Color( 1 );

		if ( computer == 1 )
		{
			othello_rj.SetKexing();
			othello_rj.Main( 0, 0, human, computer );
			othello_rj.SetBoard2();		// ʹ othello_rj �� ���� board2 �� 0
			othello_rj.PanDuan_h();		// ������һ������жϣ�ȷ����һ���Ƿ����ӿ��µ���Ϣ
			Draw_Othello( &ClientDC, 2 );

			w_moves = othello_rj.GetKexingshu();
			b_moves = 0;
			if ( b_moves != 0 || w_moves != 0 )
				othello_rj.SetKexing();
			b_discs = othello_rj.GetFirstsum();
			w_discs = othello_rj.GetSecondsum();
			UpdateData( FALSE );

			lbx.ResetContent();
			CString	str;
			str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "Black", 
				othello_rj.Gety() + 64, othello_rj.Getx() );
			lbx.AddString( str );
			lbx.SetCurSel( othello_rj.GetBushu() - 6 );
			st4.push( othello_rj );

			Draw_Color( 2 );

		}
	}
}

/*******************************************************************/
/*                          ��Ӧ���                               */
/*******************************************************************/

void CChessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC ClientDC( this );
	
	// ���������ĳߴ�
	RECT	rect;
	GetClientRect( &rect );
	int h = rect.bottom;
	
	// ���λͼ��������Ҫ�ߴ�
	BITMAP *pBitmapInfo = new BITMAP;
	m_Bitmaps[ 0 ].GetBitmap( pBitmapInfo );
	image1Width = pBitmapInfo->bmWidth;
	m_Bitmaps[ 1 ].GetBitmap( pBitmapInfo );
	image2Width = pBitmapInfo->bmWidth;

	// �Ź��壨���˶�ս)
	if (  ChessType == 1 )
	{
		boardWidth = image1Width * 2 + image2Width * 3;		// ���̴�С
		y0 = ( h - boardWidth ) / 2;	// �������϶�������
		x0 = y0;
		
		// ������ڽ����ϵ�����ֵ���ɶ�Ӧ�������ϵ�����ֵ
		double y1 = point.x - x0 - image1Width;
		double x1 = point.y - y0 - image1Width;
		int	y = ( point.x - x0 - image1Width ) / image2Width;
		int x = ( point.y - y0 - image1Width ) / image2Width;
		if ( y1 > 0 )
			y++;
		if ( x1 > 0 )
			x++;
	
		// ����Ϸ�ʱִ�оŹ���Ĵ�����
		if ( x > 0 && x <= 3 && y > 0 && y <= 3 && jiugongqi.GetBoard( x, y ) == 0 
			&& jiugongqi.GetBushu() <= 9 && jiugongqi.GetWinner() == 0 )
			JiuGongQi_Do( x, y );
	}
	
	// �Ź���(�˻���ս)
	if ( ChessType == 2 )
	{
		
		boardWidth = image1Width * 2 + image2Width * 3;
		y0 = ( h - boardWidth ) / 2;
		x0 = y0;
		
		double y1 = point.x - x0 - image1Width;
		double x1 = point.y - y0 - image1Width;
		int	y = ( point.x - x0 - image1Width ) / image2Width;
		int x = ( point.y - y0 - image1Width ) / image2Width;
		if ( y1 > 0 )
			y++;
		if ( x1 > 0 )
			x++;
		
		if ( x > 0 && x <= 3 && y > 0 && y <= 3 && jiugongqi_rj.GetBoard( x, y ) == 0 
			&& jiugongqi_rj.GetBushu() <= 9 && jiugongqi_rj.GetWinner() == 0 )
			JiuGongQi_rj_Do( x, y, human, computer );
	}

	// �ڰ���(���˶�ս)
	if ( ChessType == 3 )
	{
		boardWidth = image1Width * 2 + image2Width * 8;
		x0 = 0; y0 = 0;
	
		double y1 = point.x - x0 - image1Width;
		double x1 = point.y - y0 - image1Width;
		int	y = ( point.x - x0 - image1Width ) / image2Width;
		int x = ( point.y - y0 - image1Width ) / image2Width;
		if ( y1 > 0 )
			y++;
		if ( x1 > 0 )
			x++;
		
		if ( x > 0 && x <= 8 && y > 0 && y <= 8 && othello.GetBoard( x, y ) == 0 && 
			 othello.GetBushu() <= othello.GetBushusum() && othello.GetWinner() == 0 )
				Othello_Do( x, y );
	}
	
	// �ڰ���(�˻���ս)
	if ( ChessType == 4 )
	{
		boardWidth = image1Width * 2 + image2Width * 8;
		x0 = 0; y0 = 0;
	
		double y1 = point.x - x0 - image1Width;
		double x1 = point.y - y0 - image1Width;
		int	y = ( point.x - x0 - image1Width ) / image2Width;
		int x = ( point.y - y0 - image1Width ) / image2Width;
		if ( y1 > 0 )
			y++;
		if ( x1 > 0 )
			x++;

		if ( x > 0 && x <= 8 && y > 0 && y <= 8 && othello_rj.GetBoard( x, y ) == 0 && 
			 othello_rj.GetBushu() <= othello_rj.GetBushusum() && othello_rj.GetWinner() == 0 )
				Othello_rj_Do( x, y, human, computer );
	}

	CFormView::OnLButtonDown(nFlags, point);
}

/*************************************************/
/*          ��Ӧ����仯��Ϣ,�ػ�����            */
/*************************************************/

void CChessView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CClientDC ClientDC( this );

	if ( ChessType == 1 )
	{
		Draw_JiuGongQi( &ClientDC, 1 );
		JiuGongQi_Message( jiugongqi.Getx(), jiugongqi.Gety(), -1 );
	}
	if ( ChessType == 2 )
	{
		Draw_JiuGongQi( &ClientDC, 2 );
		JiuGongQi_rj_Message( jiugongqi_rj.Getx(), jiugongqi_rj.Gety(), -1, 2, human, computer );
	}
	if ( ChessType == 3 )
	{
		Draw_Othello( &ClientDC, 1 );
		Othello_Message( othello.Getx(), othello.Gety(), 0 );
	}
	if ( ChessType == 4 )
	{
		Draw_Othello( &ClientDC, 2 );	
		Othello_rj_Message( othello_rj.Getx(), othello_rj.Gety(), 0, 2, human, computer );
	}	
}

/*************************************************************/
/*                 �������ֵ�������������                  */
/*************************************************************/

void CChessView::Draw_Color( int type )
{
	CClientDC	ClientDC( this );

	// ����ɫ����
	if ( type == 1 )
	{
		CBrush	Brush( RGB( 0, 0, 0 ) );
		CBrush	*pOldBrush;
		pOldBrush = ClientDC.SelectObject( &Brush );
		ClientDC.Ellipse( 670, 370, 710, 410 );
		ClientDC.SelectObject( pOldBrush );
	}
	// ����ɫ����
	else
	{
		CBrush	Brush( RGB( 255, 255, 255 ) );
		CBrush	*pOldBrush;
		pOldBrush = ClientDC.SelectObject( &Brush );
		ClientDC.Ellipse( 670, 370, 710, 410 );
		ClientDC.SelectObject( pOldBrush );
	}
}
	

/**********************************************************************/
/*                            �����Ź��������                        */
/**********************************************************************/

void CChessView::Draw_JiuGongQi( CDC *pdc, int type )
{
	// �Ȱ���������������������һ������ɫ
	CClientDC	ClientDC( this );
	CBrush	Brush( RGB( 235, 235, 235 ) );
	CBrush	*pOldBrush;
	pOldBrush = ClientDC.SelectObject( &Brush );
	ClientDC.Rectangle( 0, 0, 448, 448 );
	ClientDC.SelectObject( pOldBrush );

	RECT	rect;
	GetClientRect( &rect );
	int h = rect.bottom;
	
	BITMAP *pBitmapInfo = new BITMAP;
	m_Bitmaps[ 0 ].GetBitmap( pBitmapInfo );
	image1Width = pBitmapInfo->bmWidth;
	m_Bitmaps[ 1 ].GetBitmap( pBitmapInfo );
	image2Width = pBitmapInfo->bmWidth;

	boardWidth = image1Width * 2 + image2Width * 3;
	y0 = ( h - boardWidth ) / 2;
	x0 = y0;
	
	// ���������ϱ�Ե������ĸ��
	int	width = x0, heigh = y0;
	for ( int i = 0; i <= 3; i++ )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			width += pBitmapInfo->bmWidth;
		}
	}

	// ���������ұ�Ե
	for ( int i = 9; i <= 12; i++ )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			heigh += pBitmapInfo->bmHeight;
		}
	}
	
	// ���������±�Ե
	width = x0 + image1Width;
	for ( int i = 21; i >= 18; i-- )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			width += pBitmapInfo->bmWidth;
		}
	}
	
	// �����������Ե�������ֵ�
	width = x0; heigh = y0 + image1Width;
	for ( int i = 35; i >= 32; i-- )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		if ( i == 32 )	i = 27;
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			heigh += pBitmapInfo->bmHeight;
		}
	}
	
	// �������̵ĸ���
	heigh = y0 + image1Width;	width = heigh;
	for ( int i = 1; i <= 3; i++ )
	{
		width = x0 + image1Width;
		for ( int j = 1; j <= 3; j++ )
		{
			
			CDC	MemDC;
			CBitmap	*pOldBitmap;
			MemDC.CreateCompatibleDC( pdc );
			
			int n;
			// �Ź��壨���˶�ս��
			if ( type == 1 )
			{
				if ( jiugongqi.GetBoard( i, j ) == 1 )		// ��������
					n = 37;
				else
				{
					if ( jiugongqi.GetBoard( i, j ) == 2 )	// ��������
						n = 39;
					else n = 36;
				}

				if ( i == jiugongqi.Getx() && j == jiugongqi.Gety() )	// ������һ��˫���µ�����
				{
					if ( n == 37 )
						n = 38;
					else
						n = 40;
				}
			}
			// �Ź��壨�˻���ս��
			if ( type == 2 )
			{
				if ( jiugongqi_rj.GetBoard( i, j ) == 1 )
					n = 37;
				else
				{
					if ( jiugongqi_rj.GetBoard( i, j ) == 2 )
						n = 39;
					else n = 36;
				}

				if ( i == jiugongqi_rj.Getx() && j == jiugongqi_rj.Gety() )
				{
					if ( n == 37 )
						n = 38;
					else
						n = 40;
				}
			}


			pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ n ] );

			int	iSuccess = m_Bitmaps[ n ].GetBitmap( pBitmapInfo );
			ASSERT( iSuccess );
			if ( iSuccess )
			{
				pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
				MemDC.SelectObject( pOldBitmap );
				width += pBitmapInfo->bmWidth;
			}
		}

		heigh += image2Width;
	}
}


/*********************************************************************/
/*                      �Ź��壨���˶�ս��������                   */
/*********************************************************************/

void CChessView::JiuGongQi_Do( int x, int y )
{
	CClientDC ClientDC( this );

	jiugongqi.Main( x, y );
	Draw_JiuGongQi( &ClientDC, 1 );
	jiugongqi.PanDuan_j();
	JiuGongQi_Message( x, y, 1 );
		
	st1.push( jiugongqi );
		
	// ��ʾʤ�����
	if ( jiugongqi.GetWinner() == 1 )
	{
		AfxMessageBox( "����ʤ" );
	}
	if ( jiugongqi.GetWinner() == 2 )
	{
		AfxMessageBox( "����ʤ" );
	}
	if ( jiugongqi.GetWinner() == 3 )
	{
		AfxMessageBox( "����" );
	}
}

/*********************************************************************/
/*                 �Ź��壨���˶�ս�������Ϣ����                    */
/*********************************************************************/

void CChessView::JiuGongQi_Message( int x, int y, int z )
{
	CClientDC	ClientDC( this );
	CString	str;

	// ������Ϣ
	if ( jiugongqi.GetBushu() % 2 == 0 )
	{

		Draw_Color( 2 );
			
		str.Format( "%d     %s     %c%d", jiugongqi.GetBushu() - 1, "����", 
			jiugongqi.Gety() + 64, jiugongqi.Getx() );
	}
	// ������Ϣ
	else
	{

		Draw_Color( 1 );
		
		str.Format( "%d     %s     %c%d", jiugongqi.GetBushu() - 1, "����", 
			jiugongqi.Gety() + 64, jiugongqi.Getx() );

	}

	b_discs = jiugongqi.GetBushu() / 2;
	w_discs = ( jiugongqi.GetBushu() - 1 ) / 2;
	b_moves = 9 - b_discs * 2;
	w_moves = 9 - w_discs * 2 - 1;
	if ( b_moves < 0 )
		b_moves = 0;
	UpdateData( FALSE );

	if ( z == 1 )
	{
		lbx.AddString( str );
		lbx.SetCurSel( jiugongqi.GetBushu() - 2 );
	}
}


/*********************************************************************/
/*                      �Ź��壨�˻���ս��������                   */
/*********************************************************************/

void CChessView::JiuGongQi_rj_Do( int x, int y, int human, int computer )
{
	CClientDC	ClientDC( this );

	// ���岿��
	jiugongqi_rj.Main( x, y, human, computer );
	Draw_JiuGongQi( &ClientDC, 2 );
	jiugongqi_rj.PanDuan_j();
	JiuGongQi_rj_Message( x, y, 1, 1, human, computer );
	st2.push( jiugongqi_rj );

	if ( jiugongqi_rj.GetWinner() == 1 )
	{
		AfxMessageBox( "����ʤ" );
	}
	if ( jiugongqi_rj.GetWinner() == 2 )
	{
		AfxMessageBox( "����ʤ" );
	}
	if ( jiugongqi_rj.GetWinner() == 3 )
	{
		AfxMessageBox( "����" );
	}
	
	// ���岿��
	if (  jiugongqi_rj.GetBushu() <= 9 )
	{
		jiugongqi_rj.Main( x, y, human, computer );
		Draw_JiuGongQi( &ClientDC, 2 );
		jiugongqi_rj.PanDuan_j();
		JiuGongQi_rj_Message( x, y, 1, 2, human, computer );
		st2.push( jiugongqi_rj );

		if ( jiugongqi_rj.GetWinner() == 1 )
		{
			AfxMessageBox( "����ʤ" );
		}
		if ( jiugongqi_rj.GetWinner() == 2 )
		{
			AfxMessageBox( "����ʤ" );
		}
		if ( jiugongqi_rj.GetWinner() == 3 )
		{
			AfxMessageBox( "����" );
		}
	}
}


/*********************************************************************/
/*                 �Ź��壨�˻���ս�������Ϣ����                    */
/*********************************************************************/

void CChessView::JiuGongQi_rj_Message( int x, int y, int z, int z1, int human, int computer )
{
	CClientDC	ClientDC( this );

	b_discs = jiugongqi_rj.GetBushu() / 2;
	w_discs = ( jiugongqi_rj.GetBushu() - 1 ) / 2;
	b_moves = 9 - b_discs * 2;
	w_moves = 9 - w_discs * 2 - 1;
	if ( b_moves < 0 )
		b_moves = 0;
	UpdateData( FALSE );

	// �������
	if ( z1 == 1 )
	{
		CString	str;
		// ����
		if ( human )
		{
			Draw_Color( 2 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "����", 
				y + 64, x );
		}
		// ����
		else
		{
			Draw_Color( 1 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "����", 
				y + 64, x );
		}

		if ( z == 1 )
		{
			lbx.AddString( str );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );	
		}
	}

	// �������
	if ( z1 == 2 )
	{
		CString	str;
		if ( computer )
		{
			Draw_Color( 2 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "����", 
				jiugongqi_rj.Gety() + 64, jiugongqi_rj.Getx() );
		}
		else
		{
			Draw_Color( 1 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "����", 
				jiugongqi_rj.Gety() + 64, jiugongqi_rj.Getx() );
		}

		if ( z == 1 )
		{
			lbx.AddString( str );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );
		}
	}
}


/**********************************************************************/
/*                            �����ڰ��������                        */
/**********************************************************************/

void CChessView::Draw_Othello( CDC *pdc, int type )
{
	RECT	rect;
	GetClientRect( &rect );
	int h = rect.bottom;
	
	BITMAP *pBitmapInfo = new BITMAP;
	m_Bitmaps[ 0 ].GetBitmap( pBitmapInfo );
	image1Width = pBitmapInfo->bmWidth;
	
	m_Bitmaps[ 1 ].GetBitmap( pBitmapInfo );
	image2Width = pBitmapInfo->bmWidth;

	boardWidth = image1Width * 2 + image2Width * 8;

	x0 = 0; y0 = 0;
	
	int	width = x0, heigh = y0;
	for ( int i = 0; i <= 8; i++ )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			width += pBitmapInfo->bmWidth;
		}
	}

	for ( int i = 9; i <= 17; i++ )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			heigh += pBitmapInfo->bmHeight;
		}
	}
	
	width = x0 + image1Width;
	for ( int i = 26; i >= 18; i-- )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			width += pBitmapInfo->bmWidth;
		}
	}
	
	width = x0; heigh = y0 + image1Width;
	for ( int i = 35; i >= 27; i-- )
	{
		CDC	MemDC;
		CBitmap	*pOldBitmap;
		MemDC.CreateCompatibleDC( pdc );
		pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ i ] );

		int	iSuccess = m_Bitmaps[ i ].GetBitmap( pBitmapInfo );
		ASSERT( iSuccess );
		if ( iSuccess )
		{
			pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
			MemDC.SelectObject( pOldBitmap );
			heigh += pBitmapInfo->bmHeight;
		}
	}
	
	
	heigh = y0 + image1Width;	width = heigh;
	
	for ( int i = 1; i <= 8; i++ )
	{
		width = x0 + image1Width;
		for ( int j = 1; j <= 8; j++ )
		{
			
			CDC	MemDC;
			CBitmap	*pOldBitmap;
			MemDC.CreateCompatibleDC( pdc );
			
			int n;
			if ( type == 1 )
			{
				if ( othello.GetBoard( i, j ) == 1 )
					n = 37;
				else
				{
					if ( othello.GetBoard( i, j ) == 2 )
						n = 39;
					else
						n = 36;
				}

				if ( othello.GetBoard1( i, j ) == 3 )
					n = 41;
	
				if ( i == othello.Getx() && j == othello.Gety() )
				{
					if ( n == 37 )
						n = 38;
					else
						n = 40;
				}
			}
			else
			{
				if ( othello_rj.GetBoard( i, j ) == 1 )
					n = 37;
				else
				{
					if ( othello_rj.GetBoard( i, j ) == 2 )
						n = 39;
					else
						n = 36;
				}

				if ( othello_rj.GetBoard2( i, j ) == 3 )
					n = 41;
	
				if ( i == othello_rj.Getx() && j == othello_rj.Gety() )
				{
					if ( n == 37 )
						n = 38;
					else
						n = 40;
				}
			}

			pOldBitmap = MemDC.SelectObject( &m_Bitmaps[ n ] );

			int	iSuccess = m_Bitmaps[ n ].GetBitmap( pBitmapInfo );
			ASSERT( iSuccess );
			if ( iSuccess )
			{
				pdc->BitBlt( width, heigh, pBitmapInfo->bmWidth, pBitmapInfo->bmHeight, &MemDC, 0, 0, SRCCOPY );
				MemDC.SelectObject( pOldBitmap );
				width += pBitmapInfo->bmWidth;
			}
		}

		heigh += image2Width;
	}
}


/*********************************************************************/
/*                      �ڰ��壨���˶�ս��������                   */
/*********************************************************************/

void CChessView::Othello_Do( int x, int y )
{
	CClientDC	ClientDC( this );

	// ���岿��
	int prev = othello.GetBushu();
	if ( othello.GetKexingshu() > 0 )	// �����һ������
		othello.SetKexing();

	othello.Main( x, y );	
	othello.SetBoard1();
	othello.PanDuan_h();
	if ( othello.GetBushu() > prev )	// ����µ�������Ч
	{
		Draw_Othello( &ClientDC, 1 );
		Othello_Message( x, y, 1 );
				
		st3.push( othello );
	}

	CString str;
	if ( othello.GetWinner() == 1 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "����ʤ", "����", 
			othello.GetFirstsum(), "����", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 2 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "����ʤ", "����", 
			othello.GetFirstsum(), "����", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 3 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "����", "����", 
			othello.GetFirstsum(), "����", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 4 )
	{
		str.Format( "         %s\n %s\n %s: %d - %s: %d", "�ƺ�", "˫���������ӿ���", "����", 
			othello.GetFirstsum(), "����", othello.GetSecondsum() );
		AfxMessageBox( str );
	}

	// �����һ���Է������ߵĻ���ֱ�ӵ��ô�����
	if ( othello.GetKexingshu() == 0 && othello.GetBushu() <= othello.GetBushusum() && othello.GetWinner() == 0 )
		Othello_Do( 0, 0 );
}


/*************************************************************************/
/*                      �ڰ��壨���˶�ս�������Ϣ����                   */
/*************************************************************************/
void CChessView::Othello_Message( int x, int y, int z )
{
	CClientDC	ClientDC( this );

	CString	str;
	if ( othello.GetBushu() % 2 == 0 )
	{
		w_moves = othello.GetKexingshu();
		b_moves = 0;
		if ( w_moves != 0 )
			othello.SetKexing();

		Draw_Color( 2 );

		if ( othello.Getx() == 0 )
			str.Format( "%d     %s", othello.GetBushu() - 5, "����" );
		else
			str.Format( "%d     %s     %c%d", othello.GetBushu() - 5, "����", y + 64, x );

	}
	else
	{
		b_moves = othello.GetKexingshu();
		w_moves = 0;
		if ( b_moves != 0 )
			othello.SetKexing();

		Draw_Color( 1 );

		if ( othello.Getx() == 0 )
			str.Format( "%d     %s", othello.GetBushu() - 5, "����" );
		else
			str.Format( "%d     %s     %c%d", othello.GetBushu() - 5, "����", y + 64, x );

	}

	b_discs = othello.GetFirstsum();
	w_discs = othello.GetSecondsum();
	UpdateData( FALSE );

	if ( z == 1 )
	{
		lbx.AddString( str );
		lbx.SetCurSel( othello.GetBushu() - 6 );
	}
}


/*************************************************************************/
/*                      �ڰ��壨�˻���ս��������                       */
/*************************************************************************/

void CChessView::Othello_rj_Do( int x, int y, int human, int computer )
{
	CClientDC	ClientDC( this );

	// ���岿��
	int first = 0;
	int prev = othello_rj.GetBushu();
	if ( othello_rj.GetKexingshu() > 0 )
		othello_rj.SetKexing();
			
	othello_rj.Main( x, y, human, computer );
			
	if ( othello_rj.GetBushu() > prev )
	{
		othello_rj.SetBoard2();
		othello_rj.PanDuan_h();
		Draw_Othello( &ClientDC, 2 );
		Othello_rj_Message( x, y, 1, 1, human, computer );
			
		first = 1;
		st4.push( othello_rj );

		CString str;
		if ( othello_rj.GetWinner() == 1 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����ʤ", "����", 
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 2 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����ʤ", "����", 
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 3 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����", "����", 
				othello_rj.GetFirstsum(),  "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 4 )
		{
			str.Format( "         %s\n %s\n %s: %d - %s: %d", "�ƺ�", "˫���������ӿ���", "����", 
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
	}
	
	// ���岿��
	if ( first == 1 && othello_rj.GetBushu() <= othello_rj.GetBushusum() && othello_rj.GetWinner() == 0 )
	{
		othello_rj.SetBoard2();
		othello_rj.Main( x, y, human, computer );
		othello_rj.PanDuan_h();
		Draw_Othello( &ClientDC, 2 );
		Othello_rj_Message( x, y, 1, 2, human, computer );

		st4.push( othello_rj );

		CString str;
		if ( othello_rj.GetWinner() == 1 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����ʤ", "����", 
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 2 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����ʤ", "����", 
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 3 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "����", "����",  
				othello_rj.GetFirstsum(), "����", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}

		if ( othello_rj.GetKexingshu() == 0 && othello_rj.GetBushu() <= othello_rj.GetBushusum() )
			Othello_rj_Do( 0, 0, human, computer );
	}
}


/*****************************************************************************/
/*                      �ڰ��壨�˻���ս�������Ϣ����                       */
/*****************************************************************************/

void CChessView::Othello_rj_Message( int x, int y, int z, int z1, int human, int computer )
{
	CClientDC	ClientDC( this );

	if ( z1 == 1 )
	{
		CString	str;
		if ( human )
		{
			w_moves = othello_rj.GetKexingshu();
			b_moves = 0;
			if ( w_moves != 0 )
				othello_rj.SetKexing();

			Draw_Color( 2 );
				
			if ( x == 0 )
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "����" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "����", y + 64, x );

		}
		else
		{
			b_moves = othello_rj.GetKexingshu();
			w_moves = 0;
			if ( b_moves != 0 )
				othello_rj.SetKexing();

			Draw_Color( 1 );

			if ( x == 0 )
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "����" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "����", y + 64, x );

		}

		b_discs = othello_rj.GetFirstsum();
		w_discs = othello_rj.GetSecondsum();
		UpdateData( FALSE );
			
		if ( z == 1 )
		{
			lbx.AddString( str );
			lbx.SetCurSel( othello_rj.GetBushu() - 6 );
		}
	}

	if ( z1 == 2 )
	{
		CString	str;
		if ( computer )
		{
			w_moves = othello_rj.GetKexingshu();
			b_moves = 0;
			if ( w_moves != 0 )
				othello_rj.SetKexing();

			Draw_Color( 2 );

			if ( othello_rj.Getx() == 0 )
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "����" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "����", 
					othello_rj.Gety() + 64, othello_rj.Getx() );
		}
		else
		{
			b_moves = othello_rj.GetKexingshu();
			w_moves = 0;
			if ( b_moves != 0 )
				othello_rj.SetKexing();

			Draw_Color( 1 );

			if ( othello_rj.Getx() == 0 )
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "����" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "����", 
					othello_rj.Gety() + 64, othello_rj.Getx() );
		}
			
		b_discs = othello_rj.GetFirstsum();
		w_discs = othello_rj.GetSecondsum();
		UpdateData( FALSE );

		if ( z == 1 )
		{
			lbx.AddString( str );
			lbx.SetCurSel( othello_rj.GetBushu() - 6 );
		}
	}
}

/******************************************************************************/
/*                                   ������Ӧ����                             */
/******************************************************************************/

void CChessView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CClientDC	ClientDC( this );

	// �Ź��壨���˶�ս��
	if ( ChessType == 1 )
	{
		st1.pop();		// ������ǰԪ��
		jiugongqi.Prev();		// ���¸��ำֵ
		lbx.DeleteString( jiugongqi.GetBushu() - 1 );	// ɾ�� List Box ���һ����Ϣ
		lbx.SetCurSel( jiugongqi.GetBushu() - 2 );
		Draw_JiuGongQi( &ClientDC, 1 );
	    JiuGongQi_Message( jiugongqi.Getx(), jiugongqi.Gety(), 0 );
	}

	// �Ź��壨�˻���ս��
	if ( ChessType == 2 )
	{
			st2.pop();		// ������������
			st2.pop();
			jiugongqi_rj.Prev();
			JiuGongQi_rj_Message( jiugongqi_rj.Getx(), jiugongqi_rj.Gety(), 0, 2, human, computer );
			lbx.DeleteString( jiugongqi_rj.GetBushu() );		// ����ɾ������������Ϣ
			lbx.DeleteString( jiugongqi_rj.GetBushu() - 1 );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );
			Draw_JiuGongQi( &ClientDC, 2 );
	}

	if ( ChessType == 3 )
	{
		st3.pop();
		othello.Prev();
		Draw_Othello( &ClientDC, 1 );
		Othello_Message( othello.Getx(), othello.Gety(), 0 );
	    lbx.DeleteString( othello.GetBushu() - 5  );
		lbx.SetCurSel( othello.GetBushu() - 6 );
	}

	if ( ChessType == 4 )
	{
		st4.pop();
		st4.pop();
		othello_rj.Prev();
		Draw_Othello( &ClientDC, 2 );
		Othello_rj_Message( othello_rj.Getx(), othello_rj.Gety(), 0, 2, human, computer );
		lbx.DeleteString( othello_rj.GetBushu() - 4  );
	    lbx.DeleteString( othello_rj.GetBushu() - 5  );
		lbx.SetCurSel( othello_rj.GetBushu() - 6 );
	}
}

// �ж��Ƿ���Ի���
void CChessView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( ChessType == 0 )
		pCmdUI->Enable( FALSE );
	else
	{
		if ( ChessType == 1 )
			if ( st1.size() == 1 )
				pCmdUI->Enable( FALSE );
		if ( ChessType == 2 )
			if ( st2.size() <= 2 )
				pCmdUI->Enable( FALSE );
		if ( ChessType == 3 )
			if ( st3.size() == 1 )
				pCmdUI->Enable( FALSE );
		if ( ChessType == 4 )
			if ( st4.size() <= 2 )
				pCmdUI->Enable( FALSE );
	}
}

/*************************************************************************************/
/*                                    ��������봦��                                 */
/*************************************************************************************/

/*******************************/
/*            ����             */
/*******************************/
void CChessView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CClientDC	ClientDC( this );

	CFileDialog	dlg(TRUE);		// ���򿪡�����
	dlg.m_ofn.lpstrFilter = "Chess File (*.CHESS)\0*.chess\0\0";		// Ĭ�Ϻ�׺��

	UINT	nFlags = CFile::typeBinary | CFile::modeRead;	// �ļ�����
  
	if (IDOK == dlg.DoModal())		// ���á��򿪡�����
	{
		if (IsValidFilename(dlg.GetFileName()))		// ����Ϸ��ļ���
		{
			m_strFilename = dlg.GetPathName();	// �õ��ļ��ľ���·��
		
			if ( CanSerialize() )		// ����ܴ��л�
			{
				CFile	file;
				CFileException	fe;
				if ( file.Open( m_strFilename, nFlags, &fe ) )		// ����ܴ��ļ�
				{
					CArchive	ar( &file, CArchive::load );
					Serialize( ar );	// �������صĴ��л�����
				}
			}
			else
			{
				AfxMessageBox( "�Ƿ��ļ�" );
			}
		}
	}
}

/*******************************/
/*            ����             */
/*******************************/

void CChessView::OnFileSave()
{
	// TODO: Add your command handler code here
	// ���洰�ڣ�Ĭ�Ϻ�׺��
	TCHAR sFilter[50]=_T("Chess File (*.CHESS)|*.CHESS||");
	TCHAR sExt[10]=_T("CHESS");
	CFileDialog dlg(FALSE,sExt,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					sFilter);

	if (IDOK == dlg.DoModal())
	{
		if (IsValidFilename(dlg.GetFileName()))
		{
			m_strFilename = dlg.GetPathName();
	  
			UINT nFlags = CFile::typeBinary | CFile::modeWrite | CFile::modeCreate;

			CFile file;
			CFileException fe;
			if (file.Open(m_strFilename, nFlags, &fe))
			{
				CArchive ar(&file, CArchive::store);
				Serialize(ar);
			}
		}
	}
}

// �ж��ܷ񱣴�
void CChessView::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( ChessType == 0 )
		pCmdUI->Enable( FALSE );
	else
		pCmdUI->Enable( TRUE );
}

// �ж��ļ����Ƿ�Ϸ�
BOOL CChessView::IsValidFilename(CString const& strFilename)
{
	BOOL bSuccess = FALSE;
	if (6 < strFilename.GetLength())
	{
		CString str = strFilename.Right(6);
		if (0 == str.CompareNoCase(".CHESS"))
		bSuccess = TRUE;
	}
  return bSuccess;
}

// �Ƿ�ɴ��л�
BOOL CChessView::CanSerialize()
{
	return (0 == _access(m_strFilename, 6));
}


/*************************************************/
/*                 ���л����溯��                */
/*************************************************/

void CChessView::Serialize(CArchive& ar)
{
	CClientDC	ClientDC( this );

	// ����
	if (ar.IsStoring())
	{	
		ar << ChessType;
		ar << human;
		ar << computer;

		if ( ChessType == 1 )
			jiugongqi.Serialize1( ar );

		if ( ChessType == 2 )
			jiugongqi_rj.Serialize1( ar );

		if ( ChessType == 3 )
			othello.Serialize1( ar );

		if ( ChessType == 4 )
			othello_rj.Serialize1( ar );
	}
	// ����
	else
	{	
		ar >> ChessType;
		ar >> human;
		ar >> computer;
		ar >> StackSize;

		// �Ź��壨���˶�ս��
		if ( ChessType == 1 )
		{
			// ��ն�ջ
			while ( !st1.empty() )
				st1.pop();
			while ( !st11.empty() )
				st11.pop();
	
			// ����������ջ��
			for ( int i = 1; i <= StackSize; i++ )
			{
				jiugongqi.Serialize2( ar, 0 );
				st11.push( jiugongqi );
			}

			// �ı�˳�򣬻ָ�����ǰջ��
			while ( !st11.empty() )
			{
				st1.push( st11.top() );
				st11.pop();
			}

			jiugongqi.Serialize2( ar, 1 );		// ���ݸ�����ǰ��

			Draw_JiuGongQi( &ClientDC, 1 );
			JiuGongQi_Message( jiugongqi.Getx(), jiugongqi.Gety(), 0 );
			LoadJiuGongQiLbx();		// �ѱ���������������� List Box ��
		}

	   if ( ChessType == 2 )
	   {
			while ( !st2.empty() )
				st2.pop();
			while ( !st22.empty() )
				st22.pop();

			for ( int i = 1; i <= StackSize; i++ )
			{
				jiugongqi_rj.Serialize2( ar, 0 );
				st22.push( jiugongqi_rj );
			}

			while ( !st22.empty() )
			{
				st2.push( st22.top() );
				st22.pop();
			}

			jiugongqi_rj.Serialize2( ar, 1 );
	
			Draw_JiuGongQi( &ClientDC, 2 );
			JiuGongQi_rj_Message( jiugongqi_rj.Getx(), jiugongqi_rj.Gety(), 0, 2, human, computer );
			LoadJiuGongQi_rj_Lbx();
	   }

	   if ( ChessType == 3 )
	   {
			while ( !st3.empty() )
				st3.pop();
			while ( !st33.empty() )
				st33.pop();

			for ( int i = 1; i <= StackSize; i++ )
			{
				othello.Serialize2( ar, 0 );
				st33.push( othello );
			}

			while ( !st33.empty() )
			{
				st3.push( st33.top() );
				st33.pop();
			}

			othello.Serialize2( ar, 1 );
			Draw_Othello( &ClientDC, 1 );
			Othello_Message( othello.Getx(), othello.Gety(), 0 );
			LoadOthelloLbx();
	   }

	   if ( ChessType == 4 )
	   {
			while ( !st4.empty() )
				st4.pop();
			while ( !st44.empty() )
				st44.pop();

			for ( int i = 1; i <= StackSize; i++ )
			{
				othello_rj.Serialize2( ar, 0 );
				st44.push( othello_rj );
			}

			while ( !st44.empty() )
			{
				st4.push( st44.top() );
				st44.pop();
			}

			othello_rj.Serialize2( ar, 1 );
			Draw_Othello( &ClientDC, 2 );
			Othello_rj_Message( othello_rj.Getx(), othello_rj.Gety(), 0, 2, human, computer );
		   LoadOthello_rj_Lbx();
	   }
  }
}


/******************************************************************************/
/*                            ������׵� List Box ��                          */
/******************************************************************************/

// �Ź��壨���˶�ս��
void CChessView::LoadJiuGongQiLbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < jiugongqi.GetBushu() - 1; i++ )
	{
		if ( i % 2 == 0 )
			str.Format( "%d     %s     %c%d", i + 1, "����", 
				jiugongqi.Getrecord( i, 1 ) + 64, jiugongqi.Getrecord( i, 0 ) );
		else
			str.Format( "%d     %s     %c%d", i + 1, "����", 
				jiugongqi.Getrecord( i, 1 ) + 64, jiugongqi.Getrecord( i, 0 ) );

		lbx.AddString( str );
	}

	lbx.SetCurSel( jiugongqi.GetBushu() - 2 );
}

// �Ź��壨�˻���ս��
void CChessView::LoadJiuGongQi_rj_Lbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < jiugongqi_rj.GetBushu() - 1; i++ )
	{
		if ( i % 2 == 0 )
			str.Format( "%d     %s     %c%d", i + 1, "����", 
				jiugongqi_rj.Getrecord( i, 1 ) + 64, jiugongqi_rj.Getrecord( i, 0 ) );
		else
			str.Format( "%d     %s     %c%d", i + 1, "����", 
				jiugongqi_rj.Getrecord( i, 1 ) + 64, jiugongqi_rj.Getrecord( i, 0 ) );

		lbx.AddString( str );
	}

	lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );
}

// �ڰ���(���˶�ս)
void CChessView::LoadOthelloLbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < othello.GetBushu() - 5; i++ )
	{
		if ( i % 2 == 0 )
		{
			if ( othello.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "����" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "����", 
					othello.Getrecord( i, 1 ) + 64, othello.Getrecord( i, 0 ) );
		}
		else
		{
			if ( othello.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "����" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "����", 
					othello.Getrecord( i, 1 ) + 64, othello.Getrecord( i, 0 ) );
		}

		lbx.AddString( str );
	}

	lbx.SetCurSel( othello.GetBushu() - 6 );
}

// �ڰ���(�˻���ս)
void CChessView::LoadOthello_rj_Lbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < othello_rj.GetBushu() - 5; i++ )
	{
		if ( i % 2 == 0 )
		{
			if ( othello_rj.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "����" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "����", 
					othello_rj.Getrecord( i, 1 ) + 64, othello_rj.Getrecord( i, 0 ) );
		}
		else
		{
			if ( othello_rj.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "����" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "����", 
					othello_rj.Getrecord( i, 1 ) + 64, othello_rj.Getrecord( i, 0 ) );
		}

		lbx.AddString( str );
	}

	lbx.SetCurSel( othello_rj.GetBushu() - 6 );
}