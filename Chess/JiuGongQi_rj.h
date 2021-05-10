#pragma once


class JiuGongQi_rj
{
public:
	JiuGongQi_rj(void);
	~JiuGongQi_rj(void);

public:
	void Main( int x, int y, int huamn, int computer );
	int	GetBoard( int x, int y );
	void PanDuan_j();
	int GetWinner();
	void Reset();
	// 两个人机对战函数
	void ZhiNeng_j0(int c);		
	void ZhiNeng_j1(int c1, int c2);
	int GetBushu();
	int Getx();
	int Gety();
	void Prev();
	virtual void Serialize1(CArchive& ar);
	virtual void Serialize2(CArchive& ar, int );
	int Getrecord( int x, int y );

private:
	int error, Shunxu, Bushu, x, y, x1, y1, x2, y2, Firstsum, Secondsum, Qizishu, ch, ch1, ch2, winner;
	int board[ 4 ][ 4 ];
	int record[ 9 ][ 2 ];
};
