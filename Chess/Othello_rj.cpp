#include "StdAfx.h"
#include "Othello_rj.h"

#include <stack>
std::stack< Othello_rj >	st4, st44;

extern int StackSize;


/*****************************************************************/
/*                          游戏初始化                           */
/*****************************************************************/

Othello_rj::Othello_rj(void)
{
	Bushu=5; Bushusum=64; Firstsum=2; Secondsum=2; winner = 0; Kexingshu = 4;	x3 = 0; y3 = 0;
	
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			board[ i ][ j ] = 0;
			board2[ i ][ j ] = 0;
		}
	}
	board[4][4]=1; board[4][5]=2; board[5][4]=2; board[5][5]=1;
	board2[ 3 ][ 5 ] = 3; board2[ 4 ][ 6 ] = 3;	board2[ 5 ][ 3 ] = 3; board2[ 6 ][ 4 ] = 3;

}

Othello_rj::~Othello_rj(void)
{
}

void Othello_rj::Reset()
{
	Bushu=5; Bushusum=64; Firstsum=2; Secondsum=2; winner = 0; Kexingshu = 4;	x3 = 0; y3 = 0;
	
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			board[ i ][ j ] = 0;
			board2[ i ][ j ] = 0;
		}
	}

	board[4][4]=1; board[4][5]=2; board[5][4]=2; board[5][5]=1;
	board2[ 3 ][ 5 ] = 3; board2[ 4 ][ 6 ] = 3;	board2[ 5 ][ 3 ] = 3; board2[ 6 ][ 4 ] = 3;

}


/*****************************************************************/
/*                             接口函数                          */
/*****************************************************************/

int	Othello_rj::Main( int x2, int y2, int human, int computer )
{
	if (Bushu<=Bushusum) 
	{
		if (Bushu%2==0)
		{
			ch=2;
			ch1=2;
			ch2=1;
			ch3 = 1;
		}
		else
		{
			ch=1;
			ch1=1;
			ch2=2;
			ch3=2;
		}

		if ( human )
			Shunxu = 1;
		else
			Shunxu = 0;

		if (Kexing==1)
		{
			Bihe=0;
			if (Bushu%2==Shunxu)
			{
				x = x2; y = y2;
				Youxiao=0;
				Bubian=1;
				Run();
				if (Youxiao==1)
				{
					board[x][y]=ch;
					x3 = x; y3 = y;
					record[ Bushu - 5 ][ 0 ] = x; record[ Bushu - 5 ][ 1 ] = y;
					Bubian=0;
					Run();
					//QiPu();
				}
				else
				{
					//if (Bushu%2==Shunxu)
					//printf("the human cannot run,please enter xy\n");
					return 0;
				}
			}

			else
			{
				x1=0; y1=0;
				ZhiNeng_h2();
				if (x1==0) ZhiNeng_h1();
				board[x1][y1]=ch;
				x3 = x1; y3 = y1;
				record[ Bushu - 5 ][ 0 ] = x; record[ Bushu - 5 ][ 1 ] = y;
				Bubian=0;
				x=x1; y=y1;
				Run();
			}
		}

		else
		{
			Bihe=1;
			Bushusum++;
			
			x3 = 0; y3 = 0;
			record[ Bushu - 5 ][ 0 ] = 0; record[ Bushu - 5 ][ 1 ] = 0;
			if (Bushu%2==Shunxu) 
				AfxMessageBox( "你不能走了,我继续" );
			else 
				AfxMessageBox( "我不能走了,请继续" );
		}
	
		Firstsum=0; Secondsum=0;
		Count();  /*统计双方棋子的数目*/     
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

void Othello_rj::PanDuan_h()
{
	int i,j;
Bubian=1;	Kexingshu = 0; Kexing = 0;
 if (Bushu%2==0)
		{
			ch=2;
			ch1=2;
			ch2=1;
			ch3 = 1;
		}
		else
		{
			ch=1;
			ch1=1;
			ch2=2;
			ch3=2;
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
		board2[ i ][ j ] = 3;
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

void Othello_rj::Run()
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
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
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
   if (Bubian==1) { Kexing=1; Youxiao=1 ;goto a; }
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
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
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
   if (Bubian==1) { Kexing=1; Youxiao=1; goto a; }
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
/*                        人机对战算法                           */
/*****************************************************************/

/****************************/
/*         攻角算法         */
/****************************/

void Othello_rj::ZhiNeng_h2() /*攻占4个角*/
{
 int i,a,b,a1,b1;
 Save();
 for(i=0;i<4;i++) /*循环４次，分别对４个角进行攻击*/
 {
  switch(i) /*每一次要占的角的坐标*/
  {
   case 0: x=1; y=1; break;
   case 1: x=1; y=8; break;
   case 2: x=8; y=1; break;
   case 3: x=8; y=8; break;
  }
  Bubian=1;  /*对这4个角进行判断,看能不能直接攻占*/
 if (board[x][y]==0)
 {
  Youxiao=0;
  Run(); /*看这个格子是否有效*/
  if (Youxiao==1)
  {
   x1=x;
   y1=y;
   goto a;
  }
 }
 }
 a=2; b=2; a1=2; b1=2;  /*当不能直接攻占4个角时*/
 if (board[a][b]==ch2)   /*当用户在那4个不好的点有他的棋子时,进行攻击*/
 {
  a++; b++;
  if (board[a][b]==ch2) /*当用户在对角线上还有自己的棋子且跟那个不好的棋子相连时*/
  {
   while(board[a][b]==ch2&&a<7) /*依次进攻用户每一个对角线上棋子*/
   {
    GongJiao_1(a,b,a1,b1);  /*开始攻击,传递这个要进攻的格子的数据*/
    if (x1!=0)  /*行的话立刻退出*/
     goto a;
    a++; b++;
   }
  }
 }
 a=7; b=7; a1=7; b1=7;
 if (board[a][b]==ch2)
 {
  a--; b--;
  if (board[a][b]==ch2)
  {
   while (board[a][b]==ch2&&a>2)
   {
    GongJiao_1(a,b,a1,b1);
    if (x1!=0)
     goto a;
    a--; b--;
   }
  }
 }
 a=2; b=7; a1=2; b1=7;
 if (board[a][b]==ch2)
 {
  a++; b--;
  if (board[a][b]==ch2)
  {
   while (board[a][b]==ch2&&a<7)
   {
    GongJiao_2(a,b,a1,b1);
    if (x!=0)
     goto a;
    a++; b--;
   }
  }
 }
 a=7; b=2; a1=7; b1=7;
 if (board[a][b]==ch2)
 {
  a--; b++;
  if (board[a][b]==ch2)
  {
   while (board[a][b]==ch2&&a>2)
   {
    GongJiao_2(a,b,a1,b1);
    if (x!=0)
     goto a;
    a--; b++;
   }
  }
 }
a:;
Load();
}

void Othello_rj::GongJiao_1(int a,int b,int a1,int b1)  /*第一种进攻角*/
{
 int i,j,k,l,p,q,z;
 for(i=1;i<9;i++) /*横向*/
 {
  if (board[a][i]==0)
  {
   Load();
   x=a; y=i;
   Bubian=1;
   Youxiao=0;
   Run();
   if (Youxiao==1) /*当这个格子有效时*/
   {
    Bubian=0; /*占领这个格子,改变*/
    board[a][i]=ch;
    Run();
    if (board[a][b]==ch) /*看能否把要进攻的这个格子的棋子的颜色变成自己的颜色*/
    {
     if (board[a1][b1]!=ch) /*且不能改变用户在那个不好的格子的棋子的颜色*/
     {
       x1=a;
       y1=i;
       goto a;
     }
    }
   }
  }
  if (board[i][b]==0) /*纵向*/
  {
   Load();
   x=i; y=b;
   Bubian=1;
   Youxiao=0;
   Run();
   if (Youxiao==1)
   {
    Bubian=0;
    board[i][b]=ch;
    Run();
    if (board[a][b]==ch)
    {
     if (board[a1][b1]!=ch)
     {
      x1=i;
      y1=b;
      goto a;
     }
    }
   }
  }
  if (i>2&&i<7) /*看能否在用户连续的棋后面的空格中下自己的棋子*/
  {
   if (board[i][i]==0)
   {
    Load();
    x=i; y=i;
    Bubian=1;
    Youxiao=0;
    Run();
    if (Youxiao==1)
    {
     Bubian=0;
     board[i][i]=ch;
     Run();
     if (board[a][b]==ch)
     {
      if (board[a1][b1]!=ch)
      {
       x1=i;
       y1=i;
       goto a;
      }
     }
    }
   }
  }
 }
  if (a>2&&a<7)  /*从右上到左下*/
  {
   p=a; q=b;
   while (p>1&&q<8)
   {
    p--;
    q++;
   }
   z=q-p+1;
   for(l=0;l<z;l++,p++,q--)
   {
    if (board[p][q]==0)
    {
     Load();
     x=p; y=q;
     Bubian=1;
     Youxiao=0;
     Run();
     if (Youxiao==1)
     {
      Bubian=0;
      board[p][q]=ch;
      Run();
      if (board[a][b]==ch)
      {
       if (board[a1][b1]!=ch)
       {
        x1=p;
        y1=q;
        goto a;
       }
      }
     }
    }
   }
  }
a:
Load();
}

void Othello_rj::GongJiao_2(int a,int b,int a1,int b1) /*第二种进攻角*/
{
 int i,j,k,l,p,q,z;
 for(i=1;i<9;i++)
 {
  if (board[a][i]==0) /*横向*/
  {
   Load();
   x=a; y=i;
   Bubian=1;
   Youxiao=0;
   Run();
   if (Youxiao==1)
   {
    Bubian=0;
    board[a][i]=ch;
    Run();
    if (board[a][b]==ch)
    {
     if (board[a1][b1]!=ch)
     {
       x1=a;
       y1=i;
       goto a;
     }
    }
   }
  }
  if (board[i][b]==0)  /*纵向*/
  {
   Load();
   x=i; y=b;
   Bubian=1;
   Youxiao=0;
   Run();
   if (Youxiao==1)
   {
    Bubian=0;
    board[i][b]=ch;
    Run();
    if (board[a][b]==ch)
    {
     if (board[a1][b1]!=ch)
     {
      x1=i;
      y1=b;
      goto a;
     }
    }
   }
  }
  if (i>2&&i<7)  /*看能否在用户连续的棋后面的空格中下自己的棋子*/
  {
   p=i; q=9-p;
   if (board[p][q]==0)
   {
    Load();
    x=p; y=q;
    Bubian=1;
    Youxiao=0;
    Run();
    if (Youxiao==1)
    {
     Bubian=0;
     board[p][q]=ch;
     Run();
     if (board[a][b]==ch)
     {
      if (board[a1][b1]!=ch)
      {
       x1=p;
       y1=q;
       goto a;
      }
     }
    }
   }
  }
 }
  if (a>2&&a<7) /*从左上到右下*/
  {
   p=a; q=b;
   while (p>1&&q>1)
   {
    p--;
    q--;
   }
   z=10-p-q;
   for(l=0;l<z;l++,p++,q++)
   {
    if (board[p][q]==0)
    {
     Load();
     x=p; y=q;
     Bubian=1;
     Youxiao=0;
     Run();
     if (Youxiao==1)
     {
      Bubian=0;
      board[p][q]=ch;
      Run();
      if (board[a][b]==ch)
      {
       if (board[a1][b1]!=ch)
       {
        x1=p;
        y1=q;
        goto a;
       }
      }
     }
    }
   }
  }
a:
Load();
}


/****************************/
/*   限制对方行动力算法     */
/****************************/

void Othello_rj::ZhiNeng_h1() /*寻找能够使用户可下格子数最少的一步*/
{
int i,j,k,l,sum,t=100,jd,bh,bh1;
 Save();
 Bubian=1; bh=1; bh1=0;
a:for(i=1;i<=8;i++)  /*开始寻找*/
 {
  for(j=1;j<=8;j++)
  {
   sum=0;
   Load(); ch2=ch3; ch1=ch; jd=0;
   if (board[i][j]==0)
   {
    if (bh==1) /*如果除了那12点不好的点之外还有棋子可下时*/
    if ((i==1&&j==2)||(i==2&&j==1)||(i==2&&j==2)
        ||(i==1&&j==7)||(i==2&&j==7)||(i==2&&j==8)
        ||(i==7&&j==1)||(i==7&&j==2)||(i==8&&j==2)
        ||(i==7&&j==7)||(i==7&&j==8)||(i==8&&j==7))
      jd=1;  /*当坐标为这12个不好的点时不对这些点作考虑，先不能下这些点*/
    if (jd==0) /*当坐标不是这12个点时*/
    {
     x=i;
     y=j;
     Youxiao=0;
     Run(); /*看这一点是否有效*/
     if (Youxiao==1)
     {
       Bubian=0;  /*改变*/
       Run();
       Bubian=1;  /*对改变之后的棋盘作判断，看用户有多少格子可下*/
       for(k=1;k<=8;k++)
       {
        for(l=1;l<=8;l++)
        {
         if (board[k][l]==0)
         {
          x=k;
          y=l;
          ch2=ch;
          ch1=ch3;
          Youxiao=0;
          Run();  /*判断用户在这一格是否有子可下*/
          if (Youxiao==1)
           sum++;
         }
        }
       }
      if (sum<t)  /*保存那个使用户有最少格子可下的棋子的坐标*/
      {
       t=sum;
       x1=i;
       y1=j;
       bh1=1;  /*不在那12个点电脑有格子可下*/
      }
     }
    }
   }
  }
 }
if (bh1==0) { bh=0; goto a; }
/*当不在那12个格子时没有格子可下，返回去，把那12个点包括进去*/
Load();
}

/****************************/
/*        吃最多子算法      */
/****************************/

void Othello_rj::ZhiNeng_h0() /*寻找能够吃子最多的一步*/
{
 int i,j,sum=-100,t;
 Save();  /*先把当前的棋盘保存起来*/
 Bubian=1;
 for(i=1;i<=8;i++)
 {
  for(j=1;j<=8;j++)
  {
   Load();
   if (board[i][j]==0)
   {
     x=i;
     y=j;
     Bubian=1;  /*判断这个棋子是否有效*/
     Youxiao=0;
     Run();
     if (Youxiao==1) /*有效时改变棋盘*/
     {
       board[i][j]=ch;
       Bubian=0;
       Run();
       Count(); /*统计这招棋下完之后电脑跟用户棋子数的差数*/
        if (Shunxu==1) t=Secondsum-Firstsum;
        if (Shunxu==0) t=Firstsum-Secondsum;
       if (t>sum) /*比原来的大的话就保存这时的坐标值*/
       {
        x1=i;
        y1=j;
        sum=t;
       }
     }
   }
  }
 }
Load(); /*恢复原来的棋盘*/
}


/*********************************************/
/*                  统计函数                 */
/*********************************************/

void Othello_rj::Count()
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

/*********************************************/
/*            保存装载棋盘                   */
/*********************************************/

void Othello_rj::Save() /*把当前的棋盘保存到另外一个数组中*/
{
 int i,j;
 for(i=1;i<=8;i++)
 {
  for(j=1;j<=8;j++)
   board1[i][j]=board[i][j];
 }
}

void Othello_rj::Load() /*把储存在另外一个数组里面的信息装载到原来的棋盘中*/
{
 int i,j;
 for(i=1;i<=8;i++)
 {
  for(j=1;j<=8;j++)
   board[i][j]=board1[i][j];
 }
}


/*****************************************************************/
/*                         获得变量函数                          */
/*****************************************************************/

int	Othello_rj::GetBushu()
{
	return Bushu;
}

int	Othello_rj::GetBushusum()
{
	return Bushusum;
}

int Othello_rj::GetWinner()
{
	return winner;
}

void Othello_rj::SetKexing()
{
	Kexing = 1;
}

int Othello_rj::GetKexingshu()
{
	return Kexingshu;
}

int Othello_rj::GetFirstsum()
{
	return Firstsum;
}

int Othello_rj::GetSecondsum()
{
	return Secondsum;
}

int Othello_rj::Getx()
{
	return x3;
}

int Othello_rj::Gety()
{
	return y3;
}

int Othello_rj::GetBoard2( int x, int y )
{
	return board2[ x ][ y ];
}

int	Othello_rj::GetBoard( int x, int y )
{
	return board[ x ][ y ];
}

int Othello_rj::Getrecord( int x, int y )
{
	return record[ x ][ y ];
}

void Othello_rj::SetBoard2()
{
	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
			board2[ i ][ j ] = 0;
	}
}


/*****************************************************************/
/*                       恢复当前类的值                          */
/*****************************************************************/

void Othello_rj::Prev()
{
	Shunxu = st4.top().Shunxu;
	Bushu = st4.top().Bushu;
	x = st4.top().x;
	y = st4.top().y;
	x1 = st4.top().x1;
	y1 = st4.top().y1;
	x3 = st4.top().x3;
	y3 = st4.top().y3;
	Firstsum = st4.top().Firstsum;
	Secondsum = st4.top().Secondsum;
	Kexing = st4.top().Kexing;
	Bihe = st4.top().Bihe;
	Youxiao = st4.top().Youxiao;
	Bubian = st4.top().Bubian;
	Bushusum = st4.top().Bushusum;
	ch = st4.top().ch;
	ch1 = st4.top().ch1;
	ch2 = st4.top().ch2;
	ch3 = st4.top().ch3;
	winner = st4.top().winner;
	Kexingshu = st4.top().Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			board[ i ][ j ] = st4.top().board[ i ][ j ];
			board1[ i ][ j ] = st4.top().board1[ i ][ j ];
			board2[ i ][ j ] = st4.top().board2[ i ][ j ];
		}
	}
}


/*****************************************************************/
/*                    两个串行化函数                             */
/*****************************************************************/

// 保存
void Othello_rj::Serialize1(CArchive &ar)
{
	StackSize = st4.size();
	ar << StackSize;
		while ( !st4.empty() )
		{
			ar << st4.top().Shunxu;
			ar << st4.top().Bushu;
			ar << st4.top().x;
			ar << st4.top().y;
			ar << st4.top().y;
			ar << st4.top().x1;
			ar << st4.top().x3;
			ar << st4.top().y3;
			ar << st4.top().Firstsum;
			ar << st4.top().Secondsum;
			ar << st4.top().Kexing;
			ar << st4.top().Bihe;
			ar << st4.top().Youxiao;
			ar << st4.top().Bubian;
			ar << st4.top().Bushusum;
			ar << st4.top().ch;
			ar << st4.top().ch1;
			ar << st4.top().ch2;
			ar << st4.top().ch3;
			ar << st4.top().winner;
			ar << st4.top().Kexingshu;

			for ( int i = 1; i <= 8; i++ )
			{
				for ( int j = 1; j <= 8; j++ )
				{		
					ar << st4.top().board[ i ][ j ];
					ar << st4.top().board1[ i ][ j ];
					ar << st4.top().board2[ i ][ j ];
				}
			}

			st44.push( st4.top() );
			st4.pop();
		}

		 while ( !st44.empty() )
		{
			st4.push( st44.top() );
			st44.pop();
		}
	
	ar << st4.top().Shunxu;
	ar << st4.top().Bushu;
	ar << st4.top().x;
	ar << st4.top().y;
	ar << st4.top().x1;
	ar << st4.top().y1;
	ar << st4.top().x3;
	ar << st4.top().y3;
	ar << st4.top().Firstsum;
	ar << st4.top().Secondsum;
	ar << st4.top().Kexing;
	ar << st4.top().Bihe;
	ar << st4.top().Youxiao;
	ar << st4.top().Bubian;
	ar << st4.top().Bushusum;
	ar << st4.top().ch;
	ar << st4.top().ch1;
	ar << st4.top().ch2;
	ar << st4.top().ch3;
	ar << st4.top().winner;
	ar << st4.top().Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			ar << st4.top().board[ i ][ j ];
			ar << st4.top().board1[ i ][ j ];
			ar << st4.top().board2[ i ][ j ];
		}
	}

	for ( int i = 0; i < st4.top().Bushu - 5; i++ )
	{
		for ( int j = 0; j <= 1; j++ )
			ar << st4.top().record[ i ][ j ];
	}

}

// 载入
void Othello_rj::Serialize2(CArchive &ar, int type )
{
	ar >> Shunxu;
	ar >> Bushu;
	ar >> x;
	ar >> y;
	ar >> x1;
	ar >> y1;
	ar >> x3;
	ar >> y3;
	ar >> Firstsum;
	ar >> Secondsum;
	ar >> Kexing;
	ar >> Bihe;
	ar >> Youxiao;
	ar >> Bubian;
	ar >> Bushusum;
	ar >> ch;
	ar >> ch1;
	ar >> ch2;
	ar >> ch3;
	ar >> winner;
	ar >> Kexingshu;

	for ( int i = 1; i <= 8; i++ )
	{
		for ( int j = 1; j <= 8; j++ )
		{
			ar >> board[ i ][ j ];
			ar >> board1[ i ][ j ];
			ar >> board2[ i ][ j ];
		}
	}

	if ( type == 1 )
	{
		for ( int i = 0; i < st4.top().Bushu - 5; i++ )
		{
			for ( int j = 0; j <= 1; j++ )
				ar >> record[ i ][ j ];
		}
	}

}

