#include "StdAfx.h"
#include "Othello.h"

#include <stack>
std::stack< Othello >	st3, st33;

extern int StackSize;


/*****************************************************************/
/*                          ��Ϸ��ʼ��                           */
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
/*                             �ӿں���                          */
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
	
		if (Kexing==1)  /*����ʱ*/
		{	
			x = x1; y = y1;
			Bihe=0; Youxiao=0;  /*�ƺ�ֵΪ0*/
			Bubian=1; /*��ִ�����̲����仯��ֻ�жϸ����ܲ����γɳ���*/
			Run();
			if (Youxiao==1) /*���µ�����Чʱ*/
			{
				board[x][y]=ch;
				x2 = x; y2 = y;
				record[ Bushu - 5 ][ 0 ] = x; record[ Bushu - 5 ][ 1 ] = y;
				Bubian=0; /*���в����仯�����ѳԵ��ӱ���Լ������ӵ���ɫ*/
				Run();
			}
			else
				return 0;
		}
		else
		{
			Bihe=1;
			Bushusum++;  /*�ܲ�������*/
			x2 = 0; y2 = 0;
			record[ Bushu - 5 ][ 0 ] = 0; record[ Bushu - 5 ][ 1 ] = 0;
			if (ch==1) 
				AfxMessageBox( "���岻����,�׷�����" );
			else
				AfxMessageBox( "���岻����, �������" );
		}

		Firstsum=0; Secondsum=0;
		Count();  /*ͳ��˫�����ӵ���Ŀ*/     
		//Draw_h(); /*�������*/
		if (Firstsum==0) winner = 2;
		if (Secondsum==0) winner = 1;
		if ( Bushu == Bushusum )
		{
			if (Firstsum>Secondsum) winner = 1;  /*�ж�˭ʤ*/
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
/*                            �жϺ���                           */
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
/*                            ִ�к���                           */
/*****************************************************************/

void Othello::Run()
{
	int i,a=x,b=y;  /*�����������ֵ����a,b*/
 if (board[a][b+1]==ch2) /*���ң����µ��ӵĺ�һ���ǶԷ�������ʱ*/
 {
  b++;
  while (board[a][b]==ch2)  /*����һ�����ǶԷ�������ʱ*/
   b++;
  if (board[a][b]==ch1) /*�������Լ�������ʱ����������Чʱ*/
  {
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
   /*����ʱ����ֵ��������������Ч������goto*/
   else   /*�����ı�*/
   {
    for(i=1;i<=b-y;i++)
     board[a][y+i]=ch1;
   }
  }
 }
 a=x; b=y; /*����*/
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
 a=x; b=y; /*����*/
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
 a=x; b=y;  /*����*/
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
 a=x; b=y; /*������*/
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
 a=x; b=y;  /*������*/
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
 a=x; b=y;  /*������*/
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
 a=x; b=y;  /*������*/
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
/*                            ͳ�ƺ���                           */
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
/*                         ��ñ�������                          */
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
/*                       �ָ���ǰ���ֵ                          */
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
/*                    �������л�����                             */
/*****************************************************************/

// ����
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

// ����
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