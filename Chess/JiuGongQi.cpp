#include "StdAfx.h"
#include "JiuGongQi.h"

#include <stack>
std::stack< JiuGongQi >	st1, st11;

extern int StackSize;

/*****************************************************************/
/*                           ���ݳ�ʼ��                          */
/*****************************************************************/

JiuGongQi::JiuGongQi(void)
{
	Bushu = 1;	x = 0;	y = 0;	x1 = 0;		y1 = 0; 
	Firstsum = 0;	Secondsum = 0;	Qizishu = 0;    winner = 0;
	for ( int i = 1; i <= 3; i++ )
	{
		for ( int j = 1; j <= 3; j++ )
		board[ i ][ j ] = 0;
	}
}

JiuGongQi::~JiuGongQi(void)
{
}

void JiuGongQi::Reset()
{
	Bushu = 1;	x = 0;	y = 0;	x1 = 0;	  y1 = 0; 
	Firstsum = 0;	Secondsum = 0;	 Qizishu = 0;    winner = 0;	
	for ( int i = 1; i <= 3; i++ )
	{
		for ( int j = 1; j <= 3; j++ )
		board[ i ][ j ] = 0;
	}
}

/*****************************************************************/
/*                             �ӿں���                          */
/*****************************************************************/

void JiuGongQi::Main( int x1, int y1 )
{
	if ( Bushu <= 9 )	// ����Ϸû����ʱ
	{
		if (Bushu%2==0)		// ����
		{
			ch=2;
			ch1=2;
		}
		else		// ����
		{
			ch=1;
			ch1=1;
		}
		
		board[ x1 ][ y1 ] = ch;		// ����������Ϣ
		x = x1; y = y1;
		record[ Bushu - 1 ][ 0 ] = x; record[ Bushu - 1 ][ 1 ] = y;		// ����ÿһ��������
	}
}


/*****************************************************************/
/*                            �жϺ���                           */
/*****************************************************************/

void JiuGongQi::PanDuan_j()
{
	int i,j;
	for( i = 1;i < 4;i++ )	// ����
	{
		for( j = 1;j < 4;j++ )
		{
			if ( board[ i ][ j ] == ch1 ) 
				Qizishu++;
		}
		
		if ( Qizishu==3 ) goto a;		// �����һ��������������,ֱ���˳�
		else Qizishu = 0;
	}
 
	for( i = 1;i < 4;i++ )	// ����
	{
		for( j = 1;j < 4;j++ )
		{
			if ( board[ j ][ i ] == ch1 ) 
				Qizishu++;
		}
		
		if ( Qizishu == 3 ) goto a;
		else Qizishu = 0;
	}
 
	for( i = 1;i < 4;i++ )	// ���ϵ�����
	{
		if ( board[ i ][ i ] == ch1 ) 
			Qizishu++;
	}
	
	if ( Qizishu == 3 ) goto a;
	else Qizishu = 0;
 
	for( i =3 ;i > 0;i-- )	// ���ϵ�����
	{
		if ( board[ i ][ 4-i ] == ch1 ) 
			Qizishu++;
	}
 
	if ( Qizishu == 3 ) goto a;
	else Qizishu = 0;

a:;
	if ( Bushu%2 == 0 )		// �жϵ�������ͳ��˭��������
		Secondsum = Qizishu;  
	else
		Firstsum = Qizishu;
  
	if ( Firstsum == 3 ) winner = 1;  // �ж�ʤ��
	else
	{
		if ( Secondsum == 3 ) winner = 2;
		else
			if ( Bushu == 9 )
				winner = 3;
	}

	Bushu++;
}


/*****************************************************************/
/*                       ��ñ�������                            */
/*****************************************************************/

int JiuGongQi::GetBoard( int x, int y )
{
	return board[ x ][ y ];
}

int JiuGongQi::GetWinner()
{
	return winner;
}

int JiuGongQi::GetBushu()
{
	return Bushu;
}

int JiuGongQi::Getx()
{
	return x;
}

int JiuGongQi::Gety()
{
	return y;
}

int JiuGongQi::Getrecord( int x, int y )
{
	return record[ x ][ y ];
}


/*****************************************************************/
/*                        �ָ���ǰ���ֵ                         */
/*****************************************************************/

void JiuGongQi::Prev()
{
	error = st1.top().error;
	Shunxu = st1.top().Shunxu;
	Bushu = st1.top().Bushu;
	x = st1.top().x;
	y = st1.top().y;
	x1 = st1.top().x1;
	y1 = st1.top().y1;
	Firstsum = st1.top().Firstsum;
	Secondsum = st1.top().Secondsum;
	Qizishu = st1.top().Qizishu;
	ch = st1.top().ch;
	ch1 = st1.top().ch1;
	winner = st1.top().winner;

	for ( int i = 1; i <= 4; i++ )
	{
		for ( int j = 1; j <= 4; j++ )
			board[ i ][ j ] = st1.top().board[ i ][ j ];
	}
}


/*****************************************************************/
/*                    �������л�����                             */
/*****************************************************************/

// ����
void JiuGongQi::Serialize1(CArchive& ar)
{
	StackSize = st1.size();		// �����ջ��Ԫ�ظ���
	ar << StackSize;
		
	// ���浱ǰ��ջ
	while ( !st1.empty() )		
	{
		ar << st1.top().error;
		ar << st1.top().Shunxu;
		ar << st1.top().Bushu;
		ar << st1.top().x;
		ar << st1.top().y;
		ar << st1.top().x1;
		ar << st1.top().y1;
		ar << st1.top().Firstsum;
		ar << st1.top().Secondsum;
		ar << st1.top().Qizishu;
		ar << st1.top().ch;
		ar << st1.top().ch1;
		ar << st1.top().winner;

		for ( int i = 1; i <= 4; i++ )
		{
			for ( int j = 1; j <= 4; j++ )
			{
				ar << st1.top().board[ i ][ j ];
				int a = st1.top().board[ i ][ j ];
			}
		}

		st11.push( st1.top() );
		st1.pop();
	}

	 while ( !st11.empty() )
	{
		st1.push( st11.top() );
		st11.pop();
	}

	// �ѵ�ǰ�മ�л�����
	ar << st1.top().error;
	ar << st1.top().Shunxu;
	ar << st1.top().Bushu;
	ar << st1.top().x;
	ar << st1.top().y;
	ar << st1.top().x1;
	ar << st1.top().y1;
	ar << st1.top().Firstsum;
	ar << st1.top().Secondsum;
	ar << st1.top().Qizishu;
	ar << st1.top().ch;
	ar << st1.top().ch1;
	ar << st1.top().winner;

	for ( int i = 1; i <= 4; i++ )
	{
		for ( int j = 1; j <= 4; j++ )
			ar << st1.top().board[ i ][ j ];
	}

	for ( int i = 0; i < st1.top().Bushu - 1; i++ )		// ������������
	{	
		for ( int j = 0; j <= 1; j++ )
			ar << st1.top().record[ i ][ j ];
	}
}

// ����
void JiuGongQi::Serialize2(CArchive& ar, int type )
{
	// �������뵽��ǰ��
	ar >> error;
	ar >> Shunxu;
	ar >> Bushu;
	ar >> x;
	ar >> y;
	ar >> x1;
	ar >> y1;
	ar >> Firstsum;
	ar >> Secondsum;
	ar >> Qizishu;
	ar >> ch;
	ar >> ch1;
	ar >> winner;

	for ( int i = 1; i <= 4; i++ )
	{
		for ( int j = 1; j <= 4; j++ )
			ar >> board[ i ][ j ];
	}

	if ( type == 1 )	// ������������
	{
		for ( int i = 0; i < st1.top().Bushu - 1; i++ )
		{	
			for ( int j = 0; j <= 1; j++ )
				ar >> record[ i ][ j ];
		}
	}
}