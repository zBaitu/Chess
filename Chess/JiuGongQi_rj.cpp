#include "StdAfx.h"
#include "JiuGongQi_rj.h"

#include <stack>
std::stack< JiuGongQi_rj >	st2, st22;

extern	int StackSize;

/*****************************************************************/
/*                          游戏初始化                           */
/*****************************************************************/

JiuGongQi_rj::JiuGongQi_rj(void)
{
	Bushu=1; x=0; y=0; x1=0; y1=0; Firstsum=0; Secondsum=0; Qizishu=0; winner = 0; x2 = 0; y2 = 0;
	for ( int i = 1; i <= 3; i++ )
	{
		for ( int j = 1; j <= 3; j++ )
		board[ i ][ j ] = 0;
	}

	
}

JiuGongQi_rj::~JiuGongQi_rj(void)
{
}

void JiuGongQi_rj::Reset()
{
	Bushu=1; x=0; y=0; x1=0; y1=0; Firstsum=0; Secondsum=0; Qizishu=0; winner = 0; x2 = 0; y2 = 0;
	for ( int i = 1; i <= 3; i++ )
	{
		for ( int j = 1; j <= 3; j++ )
		board[ i ][ j ] = 0;
	}
}


/*****************************************************************/
/*                             接口函数                          */
/*****************************************************************/

void JiuGongQi_rj::Main( int x, int y, int human, int computer )
{
	if ( Bushu <= 9 )
	{
		if (Bushu%2==0) 
		{
			ch=2;
			ch1=2;
			ch2 = 1;
		}
		else
		{
			ch=1;
			ch1=1;
			ch2 = 2;
		}
		
		if ( human )
			Shunxu = 1;
		else
			Shunxu = 0;
		
		// 人类玩家
		if ( Bushu % 2 == human )
		{
			board[ x ][ y ] = ch;
			record[ Bushu - 1 ][ 0 ] = x; record[ Bushu - 1 ][ 1 ] = y;
			Bushu++;
		}
		// 电脑玩家
		else
		{
			ZhiNeng_j0(ch1); // 自己是否能立刻赢  
			
			if (x1==0)		// 不能立刻赢时
			ZhiNeng_j0(ch2);  // 阻止电脑赢
			if ((x1==0)&&(board[2][2] == 0)) // 中间格
			{
				x1=2;
				y1=2;
				goto f;
			}
			if (Shunxu==1&&Bushu==4) // 特殊情况
			{
				if (((board[1][1]==ch2&&board[3][3]==ch2))||((board[1][3]==ch2&&board[3][1]==ch2)))
				{
					x1=1;
					y1=2;
					goto f;
				}
				if (board[2][2]==ch2&&board[3][3]==ch2)
				{
					x1=1;
					y1=3;
					goto f;
				}
			}
   if (x1==0)
    ZhiNeng_j1(ch1,ch2);  // 自己能否形成22
   if (x1==0)
    ZhiNeng_j1(ch2,ch1);  // 电脑能否形成22
   if (x1==0)
   {
   for(int i=1;i<4;i++)  // 随便下
   {
    for(int j=1;j<4;j++)
    {
     if (board[i][j]==0)
     {
      x1=i;
      y1=j;
      goto f;
     }
    }
   }
   }
f:
   board[x1][y1]=ch; // 电脑赋值
   x2 = x1; y2 = y1;
   record[ Bushu - 1 ][ 0 ] = x1; record[ Bushu - 1 ][ 1 ] = y1;
	x1 = 0; y1 = 0;
   Bushu++;
  }
  
		
}

}


/*****************************************************************/
/*                            判断函数                           */
/*****************************************************************/

void JiuGongQi_rj::PanDuan_j()
{
 int i,j;
 for(i=1;i<4;i++) /*横向*/
 {
  for(j=1;j<4;j++)
  {
   if (board[ i ][ j ]==ch1) Qizishu++;
  }
  if (Qizishu==3) goto a;
  else Qizishu=0;
 }
 for(i=1;i<4;i++) /*纵向*/
 {
  for(j=1;j<4;j++)
  {
   if (board[j][i]==ch1) Qizishu++;
  }
  if (Qizishu==3) goto a;
  else Qizishu=0;
 }
 for(i=1;i<4;i++) /*左上到右下*/
  if (board[i][i]==ch1) Qizishu++;
 if (Qizishu==3) goto a;
 else Qizishu=0;
 for(i=3;i>0;i--)  /*右上到左下*/
  if (board[i][4-i]==ch1) Qizishu++;
 if (Qizishu==3) goto a;
 else Qizishu=0;
a:;
 if (Bushu%2==1) Secondsum=Qizishu;
  else Firstsum=Qizishu;
  if (Firstsum==3)  /*判断谁胜并输出*/ 
  {
   winner = 1;
  }
  else
  {
	if (Secondsum==3)
	{
		winner = 2;
	}
	else
		if ( Bushu == 10 )
			winner = 3;
  }
}


/*****************************************************************/
/*                    人机对战算法函数                           */
/*****************************************************************/

// 第一种算法:判断是自己或人类玩家是否立刻能赢
void JiuGongQi_rj::ZhiNeng_j0( int c )
{
	int i,j,k;
 for(i=1;i<4;i++)  /*横向*/
 {
  for(j=1;j<4;j++)
   if (board[i][j]==c) Qizishu++;
  if (Qizishu==2) /*有的话找空格*/
  {
   for(k=1;k<4;k++)
    if (board[i][k]==0)
    {
     x1=i;
     y1=k;
     goto a;
    }
  }
  Qizishu=0;  /*归0*/
 }
 for(i=1;i<4;i++) /*纵向*/
 {
  for(j=1;j<4;j++)
   if (board[j][i]==c) Qizishu++;
  if (Qizishu==2)
  {
   for(k=1;k<4;k++)
    if (board[k][i]==0)
    {
     x1=k;
     y1=i;
     goto a;
    }
  }
 Qizishu=0;
 }
 for(i=1;i<4;i++)  /*左上到右下*/
  if (board[i][i]==c) Qizishu++;
  if (Qizishu==2)
  {
   for(i=1;i<4;i++)
    if (board[i][i]==0)
    {
     x1=i;
     y1=i;
     goto a;
    }
   }
  Qizishu=0;
 for(i=1;i<4;i++)  /*右上到左下*/
  if (board[i][4-i]==c) Qizishu++;
  if (Qizishu==2)
  {
   for(i=1;i<4;i++)
    if (board[i][4-i]==0)
    {
     x1=i;
     y1=4-i;
     goto a;
    }
  }
a:;
Qizishu=0;
}

// 第二种算法: 判断自己或人类玩家能否形成 22
void JiuGongQi_rj::ZhiNeng_j1( int c1, int c2 )
{
	int i,j,g,h,k;
	g = 0; h = 0;
 for(i=1;i<4;i++)
 {
  for(j=1;j<4;j++)
  {
   if (board[i][j]==0)  /*是否是空格*/
   {
    for(k=1;k<4;k++)  /*在横向上能否形成12*/
    {
     if (board[i][k]==c1) { g=0; break; }
     if (board[i][k]==c2) g=1;
    }
    for(k=1;k<4;k++)  /*在纵向上能否形成12*/
    {
     if (board[k][j]==c1) { h=0; break; }
     if (board[k][j]==c2) h=1;
    }
    if (g==1&&h==1) /*是否在两个方向上同时能形成12,即能否形成22*/
    {
     x1=i;
     y1=j;
     goto a; /*行的话立刻退出*/
    }
     h=0; g=0;
   }
  }
 }
a:;
}


/*****************************************************************/
/*                       获得变量函数                            */
/*****************************************************************/

int JiuGongQi_rj::GetBoard( int x, int y )
{
	return board[ x ][ y ];
}

int JiuGongQi_rj::GetWinner()
{
	return winner;
}

int JiuGongQi_rj::GetBushu()
{
	return Bushu;
}

int JiuGongQi_rj::Getx()
{
	return x2;
}

int JiuGongQi_rj::Gety()
{
	return y2;
}

int JiuGongQi_rj::Getrecord( int x, int y )
{
	return record[ x ][ y ];
}

/*****************************************************************/
/*                        恢复当前类的值                         */
/*****************************************************************/

void JiuGongQi_rj::Prev()
{
	error = st2.top().error;
	Shunxu = st2.top().Shunxu;
	Bushu = st2.top().Bushu;
	x = st2.top().x;
	y = st2.top().y;
	x1 = st2.top().x1;
	y1 = st2.top().y1;
	x2 = st2.top().x2;
	y2 = st2.top().y2;
	Firstsum = st2.top().Firstsum;
	Secondsum = st2.top().Secondsum;
	Qizishu = st2.top().Qizishu;
	ch = st2.top().ch;
	ch1 = st2.top().ch1;
	ch2 = st2.top().ch2;
	winner = st2.top().winner;

	for ( int i = 1; i <= 4; i++ )
	{
		for ( int j = 1; j <= 4; j++ )
			board[ i ][ j ] = st2.top().board[ i ][ j ];
	}
}


/*****************************************************************/
/*                    两个串行化函数                             */
/*****************************************************************/

// 保存
void JiuGongQi_rj::Serialize1(CArchive& ar)
{
	StackSize = st2.size();
	ar << StackSize;
		while ( !st2.empty() )
		{
			ar << st2.top().error;
			ar << st2.top().Shunxu;
			ar << st2.top().Bushu;
			ar << st2.top().x;
			ar << st2.top().y;
			ar << st2.top().x1;
			ar << st2.top().y1;
			ar << st2.top().x2; 
			ar << st2.top().y2;
			ar << st2.top().Firstsum;
			ar << st2.top().Secondsum;
			ar << st2.top().Qizishu;
			ar << st2.top().ch;
			ar << st2.top().ch1;
			ar << st2.top().ch2;
			ar << st2.top().winner;

			for ( int i = 1; i <= 4; i++ )
			{
				for ( int j = 1; j <= 4; j++ )
					ar << st2.top().board[ i ][ j ];
			}

			st22.push( st2.top() );
			st2.pop();
		}

		 while ( !st22.empty() )
		{
			st2.push( st22.top() );
			st22.pop();
		}

		ar << st2.top().error;
		ar << st2.top().Shunxu;
		ar << st2.top().Bushu;
		ar << st2.top().x;
		ar << st2.top().y;
		ar << st2.top().x1;
		ar << st2.top().y1;
		ar << st2.top().x2; 
		ar << st2.top().y2;
		ar << st2.top().Firstsum;
		ar << st2.top().Secondsum;
		ar << st2.top().Qizishu;
		ar << st2.top().ch;
		ar << st2.top().ch1;
		ar << st2.top().ch2;
		ar << st2.top().winner;

		for ( int i = 1; i <= 4; i++ )
		{
			for ( int j = 1; j <= 4; j++ )
				ar << st2.top().board[ i ][ j ];
		}

		for ( int i = 0; i < st2.top().Bushu - 1; i++ )
		{
			for ( int j = 0; j <= 1; j++ )
				ar << st2.top().record[ i ][ j ];
		}
}

// 载入
void JiuGongQi_rj::Serialize2(CArchive& ar, int type )
{
		ar >> error;
		ar >> Shunxu;
		ar >> Bushu;
		ar >> x;
		ar >> y;
		ar >> x1;
		ar >> y1;
		ar >> x2;
		ar >> y2;
		ar >> Firstsum;
		ar >> Secondsum;
		ar >> Qizishu;
		ar >> ch;
		ar >> ch1;
		ar >> ch2;
		ar >> winner;

		for ( int i = 1; i <= 4; i++ )
		{
			for ( int j = 1; j <= 4; j++ )
				ar >> board[ i ][ j ];
		}

		if ( type == 1 )
		{
			for ( int i = 0; i < st2.top().Bushu - 1; i++ )
			{
				for ( int j = 0; j <= 1; j++ )
					ar >> record[ i ][ j ];
			}
		}
}