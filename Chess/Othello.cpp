#include "StdAfx.h"
#include "Othello.h"

#include <stack>
std::stack< Othello >	st3, st33;

extern int StackSize;


/*****************************************************************/
/*                          游戏初始化                           */
/*****************************************************************/
Othello::Othello(void)
{
	Bushu=5; Bushusum=64; Firstsum=2; Secondsum=2; winner = 0; Kexingshu = 4; x2 = 0; y2 = 0;	
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			board[ i ][ j ] = 0;
			board1[ i ][ j ] = 0;
		}
	}
	board[4][4]=1; board[4][5]=2; board[5][4]=2; board[5][5]=1;
	board1[ 3 ][ 5 ] = 3; board1[ 4 ][ 6 ] = 3;	board1[ 5 ][ 3 ] = 3; board1[ 6 ][ 4 ] = 3;
}

Othello::~Othello(void)
{
}

void Othello::Reset()
{
	Bushu=5; Bushusum=64; Firstsum=2; Secondsum=2; winner = 0;Kexingshu = 4;	x2 = 0; y2 = 0;	
	
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			board[ i ][ j ] = 0;
			board1[ i ][ j ] = 0;
		}
	}

	board[4][4]=1; board[4][5]=2; board[5][4]=2; board[5][5]=1;
	board1[ 3 ][ 5 ] = 3; board1[ 4 ][ 6 ] = 3;	board1[ 5 ][ 3 ] = 3; board1[ 6 ][ 4 ] = 3;


}


/*****************************************************************/
/*                             接口函数                          */
/*****************************************************************/

int	Othello::Main( int x1, int y1 )
{
	if (Bushu<=Bushusum) 
	{



		if (Bushu%2==0)
		{
			ch=2;
			ch1=2;
			ch2=1;
		}
		else
		{
			ch=1;
			ch1=1;
			ch2=2;
		}
	
		if (Kexing==1)  /*可下时*/
		{	
			x = x1; y = y1;
			Bihe=0; Youxiao=0;  /*逼和值为0*/
			Bubian=1; /*不执行棋盘操作变化，只判断该子能不能形成吃子*/
			Run();
			if (Youxiao==1) /*当下的子有效时*/
			{
				board[x][y]=ch;
				x2 = x; y2 = y;
				record[ Bushu - 5 ][ 0 ] = x; record[ Bushu - 5 ][ 1 ] = y;
				Bubian=0; /*进行操作变化，即把吃的子变成自己的棋子的颜色*/
				Run();
			}
			else
				return 0;
		}
		else
		{
			Bihe=1;
			Bushusum++;  /*总步数增加*/
			x2 = 0; y2 = 0;
			record[ Bushu - 5 ][ 0 ] = 0; record[ Bushu - 5 ][ 1 ] = 0;
			if (ch==1) 
				AfxMessageBox( "黑棋不能走,白方继续" );
			else
				AfxMessageBox( "白棋不能走, 黑棋继续" );
		}

		Firstsum=0; Secondsum=0;
		Count();  /*统计双方棋子的数目*/     
		//Draw_h(); /*输出棋盘*/
		if (Firstsum==0) winner = 2;
		if (Secondsum==0) winner = 1;
		if ( Bushu == Bushusum )
		{
			if (Firstsum>Secondsum) winner = 1;  /*判断谁胜*/
			else
			{
				if (Firstsum<Secondsum) winner = 2;
				else  winner = 3;
			}
		}

		Bushu++;
	}
}


/*****************************************************************/
/*                            判断函数                           */
/*****************************************************************/

void Othello::PanDuan_h()
{
	int i,j;
 Bubian=1;	Kexingshu = 0; Kexing = 0;
 if (Bushu%2==0)
		{
			ch=2;
			ch1=2;
			ch2=1;
		}
		else
		{
			ch=1;
			ch1=1;
			ch2=2;
		}
 for(i=1;i<=8;i++)
 {
  for(j=1;j<=8;j++)
  {
   if (board[i][j]==0)
   {
    x=i; y=j;
    Run();
    if (Kexing==1)
	{
		Kexingshu++;
		board1[ i ][ j ] = 3;
	}
	Kexing = 0;
   }
  }
 }

 if ( Kexingshu == 0 && Bihe == 1 )
	 winner = 4;
}


/*****************************************************************/
/*                            执行函数                           */
/*****************************************************************/

void Othello::Run()
{
	int i,a=x,b=y;  /*把输入的坐标值赋给a,b*/
 if (board[a][b+1]==ch2) /*向右，当下的子的后一个是对方的棋子时*/
 {
  b++;
  while (board[a][b]==ch2)  /*当再一个还是对方的棋子时*/
   b++;
  if (board[a][b]==ch1) /*当出现自己的棋子时，即该子有效时*/
  {
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
   /*不变时，赋值给变量，该子有效，立刻goto*/
   else   /*发生改变*/
   {
    for(i=1;i<=b-y;i++)
     board[a][y+i]=ch1;
   }
  }
 }
 a=x; b=y; /*向左*/
 if (board[a][b-1]==ch2)
 {
  b--;
  while (board[a][b]==ch2)
   b--;
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1;goto a; }
   else
   {
    for(i=1;i<=y-b;i++)
     board[a][y-i]=ch1;
   }
  }
 }
 a=x; b=y; /*向上*/
 if (board[a-1][b]==ch2)
 {
  a--;
  while (board[a][b]==ch2)
   a--;
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
   else
   {
    for(i=1;i<=x-a;i++)
     board[x-i][b]=ch1;
   }
  }
 }
 a=x; b=y;  /*向下*/
 if (board[a+1][b]==ch2)
 {
  a++;
  while (board[a][b]==ch2)
   a++;
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1 ; goto a; }
   else
   {
    for(i=1;i<=a-x;i++)
     board[x+i][b]=ch1;
   }
  }
 }
 a=x; b=y; /*向右上*/
 if (board[a-1][b+1]==ch2)
 {
  a--; b++;
  while (board[a][b]==ch2)
  {
   a--;
   b++;
  }
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1;goto a; }
   else
   {
    for(i=1;i<=x-a;i++)
     board[x-i][y+i]=ch1;
   }
  }
 }
 a=x; b=y;  /*向左上*/
 if (board[a-1][b-1]==ch2)
 {
  a--; b--;
  while (board[a][b]==ch2)
  {
   a--;
   b--;
  }
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1;  goto a; }
   else
   {
    for(i=1;i<x-a;i++)
     board[x-i][y-i]=ch1;
   }
  }
 }
 a=x; b=y;  /*向左下*/
 if (board[a+1][b-1]==ch2)
 {
  a++; b--;
  while (board[a][b]==ch2)
  {
   a++;
   b--;
  }
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
   else
   {
    for(i=1;i<=a-x;i++)
     board[x+i][y-i]=ch1;
   }
  }
 }
 a=x; b=y;  /*向右下*/
 if (board[a+1][b+1]==ch2)
 {
  a++; b++;
  while (board[a][b]==ch2)
  {
   a++;
   b++;
  }
  if (board[a][b]==ch1)
  {
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
   else
   {
    for(i=1;i<=a-x;i++)
     board[x+i][y+i]=ch1;
   }
  }
 }
a:;
}


/*****************************************************************/
/*                            统计函数                           */
/*****************************************************************/

void Othello::Count()
{
	int i,j;
 for(i=1;i<=8;i++)
 {
  for(j=1;j<=8;j++)
  {
   if (board[i][j]==1) Firstsum++;
   if (board[i][j]==2) Secondsum++;
  }
 }
}


/*****************************************************************/
/*                         获得变量函数                          */
/*****************************************************************/

int	Othello::GetBushu()
{
	return Bushu;
}

int	Othello::GetBushusum()
{
	return Bushusum;
}

int Othello::GetWinner()
{
	return winner;
}

int Othello::GetFirstsum()
{
	return Firstsum;
}

int Othello::GetSecondsum()
{
	return Secondsum;
}

int Othello::GetKexingshu()
{
	return Kexingshu;	
}

void Othello::SetKexing()
{
	Kexing = 1;
}

int Othello::Getx()
{
	return x2;
}

int Othello::Gety()
{
	return y2;
}

int	Othello::GetBoard( int x, int y )
{
	return board[ x ][ y ];
}

int Othello::GetBoard1( int x, int y )
{
	return board1[ x ][ y ];
}

int Othello::Getrecord( int x, int y )
{
	return record[ x ][ y ];
}

void Othello::SetBoard1()
{
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			board1[ i ][ j ] = 0;
	}
}


/*****************************************************************/
/*                       恢复当前类的值                          */
/*****************************************************************/

void Othello::Prev()
{
	Shunxu = st3.top().Shunxu;
	Bushu = st3.top().Bushu;
	x = st3.top().x;
	y = st3.top().y;
	x2 = st3.top().x2;
	y2 = st3.top().y2;
	Firstsum = st3.top().Firstsum;
	Secondsum = st3.top().Secondsum;
	Kexing = st3.top().Kexing;
	Bihe = st3.top().Bihe;
	Youxiao = st3.top().Youxiao;
	Bubian = st3.top().Bubian;
	ch = st3.top().ch;
	ch1 = st3.top().ch1;
	ch2 = st3.top().ch2;
	winner = st3.top().winner;
	Kexingshu = st3.top().Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			board[ i ][ j ] = st3.top().board[ i ][ j ];
	}

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			board1[ i ][ j ] = st3.top().board1[ i ][ j ];
	}
}


/*****************************************************************/
/*                    两个串行化函数                             */
/*****************************************************************/

// 保存
void Othello::Serialize1( CArchive& ar )
{
	StackSize = st3.size();
	ar << StackSize;
		while ( !st3.empty() )
		{
			ar << st3.top().Shunxu;
			ar << st3.top().Bushu;
			ar << st3.top().x;
			ar << st3.top().y;
			ar << st3.top().x2; 
			ar << st3.top().y2;
			ar << st3.top().Firstsum;
			ar << st3.top().Secondsum;
			ar << st3.top().Kexing;
			ar << st3.top().Bihe;
			ar << st3.top().Youxiao;
			ar << st3.top().Bubian;
			ar << st3.top().ch;
			ar << st3.top().ch1;
			ar << st3.top().ch2;
			ar << st3.top().winner;
			ar << st3.top().Kexingshu;

			for ( int i = 1; i <= 8; i++ )
			{
				for ( int j = 1; j <= 8; j++ )
					ar << st3.top().board[ i ][ j ];
			}

			for ( int i = 1; i <= 8; i++ )
			{
				for ( int j = 1; j <= 8; j++ )
					ar << st3.top().board1[ i ][ j ];
			}

			st33.push( st3.top() );
			st3.pop();
		}

		 while ( !st33.empty() )
		{
			st3.push( st33.top() );
			st33.pop();
		}

	ar << st3.top().Shunxu;
	ar << st3.top().Bushu;
	ar << st3.top().x;
	ar << st3.top().y;
	ar << st3.top().x2;
	ar << st3.top().y2;
	ar << st3.top().Firstsum;
	ar << st3.top().Secondsum;
	ar << st3.top().Kexing;
	ar << st3.top().Bihe;
	ar << st3.top().Youxiao;
	ar << st3.top().Bubian;
	ar << st3.top().ch;
	ar << st3.top().ch1;
	ar << st3.top().ch2;
	ar << st3.top().winner;
	ar << st3.top().Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			ar << st3.top().board[ i ][ j ];
	}

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			ar << st3.top().board1[ i ][ j ];
	}

	for ( int i = 0; i < st3.top().Bushu - 5; i++ )
	{
		for ( int j = 0; j <= 1; j++ )
			ar << st3.top().record[ i ][ j ];
	}
}

// 载入
void Othello::Serialize2( CArchive& ar, int type )
{
	ar >> Shunxu;
	ar >> Bushu;
	ar >> x;
	ar >> y;
	ar >> x2;
	ar >> y2;
	ar >> Firstsum;
	ar >> Secondsum;
	ar >> Kexing;
	ar >> Bihe;
	ar >> Youxiao;
	ar >> Bubian;
	ar >> ch;
	ar >> ch1;
	ar >> ch2;
	ar >> winner;
	ar >> Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			ar >> board[ i ][ j ];
	}

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			ar >> board1[ i ][ j ];
	}

	if ( type == 1 )
	{
		for ( int i = 0; i < st3.top().Bushu - 5; i++ )
		{
			for ( int j = 0; j <= 1; j++ )
				ar >> record[ i ][ j ];
		}
	}
}