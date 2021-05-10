#pragma once


class JiuGongQi
{
public:
	JiuGongQi(void);
	~JiuGongQi(void);

public:
	void Main( int x, int y );		// 接口函数
	int	GetBoard( int x, int y );	// 得到棋盘格子的信息
	void PanDuan_j();		// 判断函数
	int GetWinner();		
	void Reset();
	int GetBushu();
	int Getx();
	int Gety();
	void Prev();	// 恢复当前类的信息
	// 两个串行化函数
	virtual void Serialize1(CArchive& ar);
	virtual void Serialize2(CArchive& ar, int type );
	int Getrecord( int x, int y );
	
private:
	int error, Shunxu, Bushu, x, y, x1, y1, Firstsum, Secondsum, Qizishu, ch, ch1, winner;
	int board[ 4 ][ 4 ];
	int record[ 9 ][ 2 ];
};
