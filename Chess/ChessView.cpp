// ChessView.cpp : CChessView 类的实现
//

#include "stdafx.h"
#include "Chess.h"
#include "ChessDoc.h"
#include "ChessView.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 四个全局变量
int	ChessType = 0;
int human = 0, computer = 0;
int OkButton = 0;
int StackSize;

// 声明在四个棋的实现类里面定义的堆栈
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

// CChessView 构造/析构

/******************************************************************/
/*                在CChessView 初始化时加载位图资源               */
/******************************************************************/

CChessView::CChessView()
	: CFormView(CChessView::IDD)
	, b_discs(0)
	, b_moves(0)
	, w_discs(0)
	, w_moves(0)
{
	// TODO: 在此处添加构造代码
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
	// 五个DDX 控件变量
	DDX_Text( pDX, IDC_B_DISCS, b_discs );
	DDX_Text( pDX, IDC_B_MOVES, b_moves );
	DDX_Text( pDX, IDC_W_DISCS, w_discs );
	DDX_Text( pDX, IDC_W_MOVES, w_moves );
	DDX_Control(pDX, IDC_LIST1, lbx);
}

BOOL CChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CChessView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CChessView 诊断

#ifdef _DEBUG
void CChessView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChessView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChessDoc* CChessView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*)m_pDocument;
}
#endif //_DEBUG


// CChessView 消息处理程序

/***********************************************************************/
/*                           游戏初始化部分                            */
/***********************************************************************/

// 响应 “新棋局”按键函数
void CChessView::OnFileNew()
{
	// TODO: Add your command handler code here
	CInitializeDlg	dlg;
	dlg.DoModal();		// 调用“游戏开始选项”对话框
	if ( OkButton == 1 )	// 当“确认”按钮按下时
	{
		OkButton = 0;
		Initialize();	// 初始化游戏，画出初始棋盘， 输出双方初始信息
	}
}

// 初始化游戏函数
void CChessView::Initialize()
{
	CClientDC	ClientDC( this );
	
	// 九宫棋（人人对战）
	if ( ChessType == 1 )
	{
		jiugongqi.Reset();		// 初始化棋的变量
		
		Draw_JiuGongQi( &ClientDC, 1 );		// 画出棋盘
		b_discs = 0;
		w_discs = 0;
		b_moves = 9;
		w_moves = 8;
		UpdateData( FALSE );	// 在四个 Edit Control 上输出初始信息
		lbx.ResetContent();		// 清空 List Box 上的信息
		st1.push( jiugongqi );	// 把第一个类的信息压入栈中
		Draw_Color( 1 );		// 在“轮到：”面板画出黑色棋子
	}

	// 九宫棋（人机对战）
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

		// 如果是电脑先下的话
		if ( computer == 1 )
		{
			jiugongqi_rj.Main( 0, 0, human, computer );		// 让电脑思考下在哪里
			
			Draw_JiuGongQi( &ClientDC, 2 );
			b_discs = 1;
			w_discs = 0;
			b_moves = 7;
			w_moves = 8;
			UpdateData( FALSE );
			lbx.ResetContent();
			
			// 在 List Box 上输出电脑下棋的信息
			CString	str;
			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "Black", 
					jiugongqi_rj.Gety() + 64, jiugongqi_rj.Getx() );			
			lbx.AddString( str );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );	// 始终让高亮部分在最后一步棋上
			st2.push( jiugongqi_rj );

			Draw_Color( 2 );	// 在“轮到：”面板画出白色棋子
		}
	}

	// 黑白棋（人人对战）
	if ( ChessType == 3 )
	{
		othello.Reset();
		
		Draw_Othello( &ClientDC, 1 );
		othello.SetKexing();	// 使 othello 的 Kexing 变量变一，使下一步棋能下
		b_discs = othello.GetFirstsum();
		w_discs = othello.GetSecondsum();
		b_moves = 4;
		w_moves = 0;
		UpdateData( FALSE );
		lbx.ResetContent();

		st3.push( othello );

		Draw_Color( 1 );
	}
		
	// 黑白棋（人机对战）
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
			othello_rj.SetBoard2();		// 使 othello_rj 的 数组 board2 变 0
			othello_rj.PanDuan_h();		// 下完这一步后的判断，确定下一步是否有子可下等信息
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
/*                          响应鼠标                               */
/*******************************************************************/

void CChessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC ClientDC( this );
	
	// 获得主界面的尺寸
	RECT	rect;
	GetClientRect( &rect );
	int h = rect.bottom;
	
	// 获得位图的两个主要尺寸
	BITMAP *pBitmapInfo = new BITMAP;
	m_Bitmaps[ 0 ].GetBitmap( pBitmapInfo );
	image1Width = pBitmapInfo->bmWidth;
	m_Bitmaps[ 1 ].GetBitmap( pBitmapInfo );
	image2Width = pBitmapInfo->bmWidth;

	// 九宫棋（人人对战)
	if (  ChessType == 1 )
	{
		boardWidth = image1Width * 2 + image2Width * 3;		// 棋盘大小
		y0 = ( h - boardWidth ) / 2;	// 棋盘左上顶点坐标
		x0 = y0;
		
		// 把鼠标在界面上的坐标值换成对应的棋盘上的坐标值
		double y1 = point.x - x0 - image1Width;
		double x1 = point.y - y0 - image1Width;
		int	y = ( point.x - x0 - image1Width ) / image2Width;
		int x = ( point.y - y0 - image1Width ) / image2Width;
		if ( y1 > 0 )
			y++;
		if ( x1 > 0 )
			x++;
	
		// 坐标合法时执行九宫棋的处理函数
		if ( x > 0 && x <= 3 && y > 0 && y <= 3 && jiugongqi.GetBoard( x, y ) == 0 
			&& jiugongqi.GetBushu() <= 9 && jiugongqi.GetWinner() == 0 )
			JiuGongQi_Do( x, y );
	}
	
	// 九宫棋(人机对战)
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

	// 黑白棋(人人对战)
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
	
	// 黑白棋(人机对战)
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
/*          响应界面变化信息,重画界面            */
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
/*                 画出“轮到：”面板的棋子                  */
/*************************************************************/

void CChessView::Draw_Color( int type )
{
	CClientDC	ClientDC( this );

	// 画黑色棋子
	if ( type == 1 )
	{
		CBrush	Brush( RGB( 0, 0, 0 ) );
		CBrush	*pOldBrush;
		pOldBrush = ClientDC.SelectObject( &Brush );
		ClientDC.Ellipse( 670, 370, 710, 410 );
		ClientDC.SelectObject( pOldBrush );
	}
	// 画白色棋子
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
/*                            画出九宫棋的棋盘                        */
/**********************************************************************/

void CChessView::Draw_JiuGongQi( CDC *pdc, int type )
{
	// 先把整个棋盘区填充跟主界面一样的颜色
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
	
	// 画出棋盘上边缘，有字母的
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

	// 画出棋盘右边缘
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
	
	// 画出棋盘下边缘
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
	
	// 画出棋盘左边缘，有数字的
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
	
	// 画出棋盘的格子
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
			// 九宫棋（人人对战）
			if ( type == 1 )
			{
				if ( jiugongqi.GetBoard( i, j ) == 1 )		// 画出黑棋
					n = 37;
				else
				{
					if ( jiugongqi.GetBoard( i, j ) == 2 )	// 画出白棋
						n = 39;
					else n = 36;
				}

				if ( i == jiugongqi.Getx() && j == jiugongqi.Gety() )	// 画出上一步双方下的棋子
				{
					if ( n == 37 )
						n = 38;
					else
						n = 40;
				}
			}
			// 九宫棋（人机对战）
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
/*                      九宫棋（人人对战）处理函数                   */
/*********************************************************************/

void CChessView::JiuGongQi_Do( int x, int y )
{
	CClientDC ClientDC( this );

	jiugongqi.Main( x, y );
	Draw_JiuGongQi( &ClientDC, 1 );
	jiugongqi.PanDuan_j();
	JiuGongQi_Message( x, y, 1 );
		
	st1.push( jiugongqi );
		
	// 提示胜负情况
	if ( jiugongqi.GetWinner() == 1 )
	{
		AfxMessageBox( "黑棋胜" );
	}
	if ( jiugongqi.GetWinner() == 2 )
	{
		AfxMessageBox( "白棋胜" );
	}
	if ( jiugongqi.GetWinner() == 3 )
	{
		AfxMessageBox( "和棋" );
	}
}

/*********************************************************************/
/*                 九宫棋（人人对战）输出信息函数                    */
/*********************************************************************/

void CChessView::JiuGongQi_Message( int x, int y, int z )
{
	CClientDC	ClientDC( this );
	CString	str;

	// 黑棋信息
	if ( jiugongqi.GetBushu() % 2 == 0 )
	{

		Draw_Color( 2 );
			
		str.Format( "%d     %s     %c%d", jiugongqi.GetBushu() - 1, "黑棋", 
			jiugongqi.Gety() + 64, jiugongqi.Getx() );
	}
	// 白棋信息
	else
	{

		Draw_Color( 1 );
		
		str.Format( "%d     %s     %c%d", jiugongqi.GetBushu() - 1, "白棋", 
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
/*                      九宫棋（人机对战）处理函数                   */
/*********************************************************************/

void CChessView::JiuGongQi_rj_Do( int x, int y, int human, int computer )
{
	CClientDC	ClientDC( this );

	// 黑棋部分
	jiugongqi_rj.Main( x, y, human, computer );
	Draw_JiuGongQi( &ClientDC, 2 );
	jiugongqi_rj.PanDuan_j();
	JiuGongQi_rj_Message( x, y, 1, 1, human, computer );
	st2.push( jiugongqi_rj );

	if ( jiugongqi_rj.GetWinner() == 1 )
	{
		AfxMessageBox( "黑棋胜" );
	}
	if ( jiugongqi_rj.GetWinner() == 2 )
	{
		AfxMessageBox( "白棋胜" );
	}
	if ( jiugongqi_rj.GetWinner() == 3 )
	{
		AfxMessageBox( "和棋" );
	}
	
	// 白棋部分
	if (  jiugongqi_rj.GetBushu() <= 9 )
	{
		jiugongqi_rj.Main( x, y, human, computer );
		Draw_JiuGongQi( &ClientDC, 2 );
		jiugongqi_rj.PanDuan_j();
		JiuGongQi_rj_Message( x, y, 1, 2, human, computer );
		st2.push( jiugongqi_rj );

		if ( jiugongqi_rj.GetWinner() == 1 )
		{
			AfxMessageBox( "黑棋胜" );
		}
		if ( jiugongqi_rj.GetWinner() == 2 )
		{
			AfxMessageBox( "白棋胜" );
		}
		if ( jiugongqi_rj.GetWinner() == 3 )
		{
			AfxMessageBox( "和棋" );
		}
	}
}


/*********************************************************************/
/*                 九宫棋（人机对战）输出信息函数                    */
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

	// 下完黑棋
	if ( z1 == 1 )
	{
		CString	str;
		// 先手
		if ( human )
		{
			Draw_Color( 2 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "黑棋", 
				y + 64, x );
		}
		// 后手
		else
		{
			Draw_Color( 1 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "白棋", 
				y + 64, x );
		}

		if ( z == 1 )
		{
			lbx.AddString( str );
			lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );	
		}
	}

	// 下完白棋
	if ( z1 == 2 )
	{
		CString	str;
		if ( computer )
		{
			Draw_Color( 2 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "黑棋", 
				jiugongqi_rj.Gety() + 64, jiugongqi_rj.Getx() );
		}
		else
		{
			Draw_Color( 1 );

			str.Format( "%d     %s     %c%d", jiugongqi_rj.GetBushu() - 1, "白棋", 
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
/*                            画出黑白棋的棋盘                        */
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
/*                      黑白棋（人人对战）处理函数                   */
/*********************************************************************/

void CChessView::Othello_Do( int x, int y )
{
	CClientDC	ClientDC( this );

	// 黑棋部分
	int prev = othello.GetBushu();
	if ( othello.GetKexingshu() > 0 )	// 如果这一步可行
		othello.SetKexing();

	othello.Main( x, y );	
	othello.SetBoard1();
	othello.PanDuan_h();
	if ( othello.GetBushu() > prev )	// 如果下的棋子有效
	{
		Draw_Othello( &ClientDC, 1 );
		Othello_Message( x, y, 1 );
				
		st3.push( othello );
	}

	CString str;
	if ( othello.GetWinner() == 1 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "黑棋胜", "黑棋", 
			othello.GetFirstsum(), "白棋", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 2 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "白棋胜", "黑棋", 
			othello.GetFirstsum(), "白棋", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 3 )
	{
		str.Format( "    %s\n %s: %d - %s: %d", "和棋", "黑棋", 
			othello.GetFirstsum(), "白棋", othello.GetSecondsum() );
		AfxMessageBox( str );
	}
	if ( othello.GetWinner() == 4 )
	{
		str.Format( "         %s\n %s\n %s: %d - %s: %d", "逼和", "双方都无棋子可下", "黑棋", 
			othello.GetFirstsum(), "白棋", othello.GetSecondsum() );
		AfxMessageBox( str );
	}

	// 如果下一步对方不能走的话，直接调用处理函数
	if ( othello.GetKexingshu() == 0 && othello.GetBushu() <= othello.GetBushusum() && othello.GetWinner() == 0 )
		Othello_Do( 0, 0 );
}


/*************************************************************************/
/*                      黑白棋（人人对战）输出信息函数                   */
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
			str.Format( "%d     %s", othello.GetBushu() - 5, "黑棋" );
		else
			str.Format( "%d     %s     %c%d", othello.GetBushu() - 5, "黑棋", y + 64, x );

	}
	else
	{
		b_moves = othello.GetKexingshu();
		w_moves = 0;
		if ( b_moves != 0 )
			othello.SetKexing();

		Draw_Color( 1 );

		if ( othello.Getx() == 0 )
			str.Format( "%d     %s", othello.GetBushu() - 5, "白棋" );
		else
			str.Format( "%d     %s     %c%d", othello.GetBushu() - 5, "白棋", y + 64, x );

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
/*                      黑白棋（人机对战）处理函数                       */
/*************************************************************************/

void CChessView::Othello_rj_Do( int x, int y, int human, int computer )
{
	CClientDC	ClientDC( this );

	// 黑棋部分
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
			str.Format( "         %s\n %s: %d - %s: %d", "黑棋胜", "黑棋", 
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 2 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "白棋胜", "黑棋", 
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 3 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "和棋", "黑棋", 
				othello_rj.GetFirstsum(),  "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 4 )
		{
			str.Format( "         %s\n %s\n %s: %d - %s: %d", "逼和", "双方都无棋子可下", "黑棋", 
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
	}
	
	// 白棋部分
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
			str.Format( "         %s\n %s: %d - %s: %d", "黑棋胜", "黑棋", 
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 2 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "白棋胜", "黑棋", 
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}
		if ( othello_rj.GetWinner() == 3 )
		{
			str.Format( "         %s\n %s: %d - %s: %d", "和棋", "黑棋",  
				othello_rj.GetFirstsum(), "白棋", othello_rj.GetSecondsum() );
			AfxMessageBox( str );
		}

		if ( othello_rj.GetKexingshu() == 0 && othello_rj.GetBushu() <= othello_rj.GetBushusum() )
			Othello_rj_Do( 0, 0, human, computer );
	}
}


/*****************************************************************************/
/*                      黑白棋（人机对战）输出信息函数                       */
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
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "黑棋" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "黑棋", y + 64, x );

		}
		else
		{
			b_moves = othello_rj.GetKexingshu();
			w_moves = 0;
			if ( b_moves != 0 )
				othello_rj.SetKexing();

			Draw_Color( 1 );

			if ( x == 0 )
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "白棋" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "白棋", y + 64, x );

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
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "黑棋" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "黑棋", 
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
				str.Format( "%d     %s", othello_rj.GetBushu() - 5, "白棋" );
			else
				str.Format( "%d     %s     %c%d", othello_rj.GetBushu() - 5, "白棋", 
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
/*                                   悔棋响应函数                             */
/******************************************************************************/

void CChessView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CClientDC	ClientDC( this );

	// 九宫棋（人人对战）
	if ( ChessType == 1 )
	{
		st1.pop();		// 弹出当前元素
		jiugongqi.Prev();		// 重新给类赋值
		lbx.DeleteString( jiugongqi.GetBushu() - 1 );	// 删除 List Box 最后一个信息
		lbx.SetCurSel( jiugongqi.GetBushu() - 2 );
		Draw_JiuGongQi( &ClientDC, 1 );
	    JiuGongQi_Message( jiugongqi.Getx(), jiugongqi.Gety(), 0 );
	}

	// 九宫棋（人机对战）
	if ( ChessType == 2 )
	{
			st2.pop();		// 连续弹出两个
			st2.pop();
			jiugongqi_rj.Prev();
			JiuGongQi_rj_Message( jiugongqi_rj.Getx(), jiugongqi_rj.Gety(), 0, 2, human, computer );
			lbx.DeleteString( jiugongqi_rj.GetBushu() );		// 连续删除两个棋谱信息
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

// 判断是否可以悔棋
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
/*                                    保存和载入处理                                 */
/*************************************************************************************/

/*******************************/
/*            载入             */
/*******************************/
void CChessView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CClientDC	ClientDC( this );

	CFileDialog	dlg(TRUE);		// “打开”窗口
	dlg.m_ofn.lpstrFilter = "Chess File (*.CHESS)\0*.chess\0\0";		// 默认后缀名

	UINT	nFlags = CFile::typeBinary | CFile::modeRead;	// 文件属性
  
	if (IDOK == dlg.DoModal())		// 调用“打开”窗口
	{
		if (IsValidFilename(dlg.GetFileName()))		// 如果合法文件名
		{
			m_strFilename = dlg.GetPathName();	// 得到文件的绝对路径
		
			if ( CanSerialize() )		// 如果能串行化
			{
				CFile	file;
				CFileException	fe;
				if ( file.Open( m_strFilename, nFlags, &fe ) )		// 如果能打开文件
				{
					CArchive	ar( &file, CArchive::load );
					Serialize( ar );	// 调用重载的串行化函数
				}
			}
			else
			{
				AfxMessageBox( "非法文件" );
			}
		}
	}
}

/*******************************/
/*            保存             */
/*******************************/

void CChessView::OnFileSave()
{
	// TODO: Add your command handler code here
	// 保存窗口，默认后缀名
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

// 判断能否保存
void CChessView::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( ChessType == 0 )
		pCmdUI->Enable( FALSE );
	else
		pCmdUI->Enable( TRUE );
}

// 判断文件名是否合法
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

// 是否可串行化
BOOL CChessView::CanSerialize()
{
	return (0 == _access(m_strFilename, 6));
}


/*************************************************/
/*                 串行化保存函数                */
/*************************************************/

void CChessView::Serialize(CArchive& ar)
{
	CClientDC	ClientDC( this );

	// 保存
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
	// 载入
	else
	{	
		ar >> ChessType;
		ar >> human;
		ar >> computer;
		ar >> StackSize;

		// 九宫棋（人人对战）
		if ( ChessType == 1 )
		{
			// 清空堆栈
			while ( !st1.empty() )
				st1.pop();
			while ( !st11.empty() )
				st11.pop();
	
			// 把数据载入栈中
			for ( int i = 1; i <= StackSize; i++ )
			{
				jiugongqi.Serialize2( ar, 0 );
				st11.push( jiugongqi );
			}

			// 改变顺序，恢复到当前栈中
			while ( !st11.empty() )
			{
				st1.push( st11.top() );
				st11.pop();
			}

			jiugongqi.Serialize2( ar, 1 );		// 数据赋给当前类

			Draw_JiuGongQi( &ClientDC, 1 );
			JiuGongQi_Message( jiugongqi.Getx(), jiugongqi.Gety(), 0 );
			LoadJiuGongQiLbx();		// 把保存的棋的棋谱输出到 List Box 上
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
/*                            输出棋谱到 List Box 上                          */
/******************************************************************************/

// 九宫棋（人人对战）
void CChessView::LoadJiuGongQiLbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < jiugongqi.GetBushu() - 1; i++ )
	{
		if ( i % 2 == 0 )
			str.Format( "%d     %s     %c%d", i + 1, "黑棋", 
				jiugongqi.Getrecord( i, 1 ) + 64, jiugongqi.Getrecord( i, 0 ) );
		else
			str.Format( "%d     %s     %c%d", i + 1, "白棋", 
				jiugongqi.Getrecord( i, 1 ) + 64, jiugongqi.Getrecord( i, 0 ) );

		lbx.AddString( str );
	}

	lbx.SetCurSel( jiugongqi.GetBushu() - 2 );
}

// 九宫棋（人机对战）
void CChessView::LoadJiuGongQi_rj_Lbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < jiugongqi_rj.GetBushu() - 1; i++ )
	{
		if ( i % 2 == 0 )
			str.Format( "%d     %s     %c%d", i + 1, "黑棋", 
				jiugongqi_rj.Getrecord( i, 1 ) + 64, jiugongqi_rj.Getrecord( i, 0 ) );
		else
			str.Format( "%d     %s     %c%d", i + 1, "白棋", 
				jiugongqi_rj.Getrecord( i, 1 ) + 64, jiugongqi_rj.Getrecord( i, 0 ) );

		lbx.AddString( str );
	}

	lbx.SetCurSel( jiugongqi_rj.GetBushu() - 2 );
}

// 黑白棋(人人对战)
void CChessView::LoadOthelloLbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < othello.GetBushu() - 5; i++ )
	{
		if ( i % 2 == 0 )
		{
			if ( othello.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "黑棋" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "黑棋", 
					othello.Getrecord( i, 1 ) + 64, othello.Getrecord( i, 0 ) );
		}
		else
		{
			if ( othello.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "白棋" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "白棋", 
					othello.Getrecord( i, 1 ) + 64, othello.Getrecord( i, 0 ) );
		}

		lbx.AddString( str );
	}

	lbx.SetCurSel( othello.GetBushu() - 6 );
}

// 黑白棋(人机对战)
void CChessView::LoadOthello_rj_Lbx()
{
	CString	str;
	
	lbx.ResetContent();
	for ( int i = 0; i < othello_rj.GetBushu() - 5; i++ )
	{
		if ( i % 2 == 0 )
		{
			if ( othello_rj.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "黑棋" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "黑棋", 
					othello_rj.Getrecord( i, 1 ) + 64, othello_rj.Getrecord( i, 0 ) );
		}
		else
		{
			if ( othello_rj.Getrecord( i, 1 ) == 0 )
				str.Format( "%d     %s", i + 1, "白棋" );
			else
				str.Format( "%d     %s     %c%d", i + 1, "白棋", 
					othello_rj.Getrecord( i, 1 ) + 64, othello_rj.Getrecord( i, 0 ) );
		}

		lbx.AddString( str );
	}

	lbx.SetCurSel( othello_rj.GetBushu() - 6 );
}