#pragma once


class Othello_rj
{
public:
	Othello_rj(void);
	~Othello_rj(void);

public:
	int	Main( int x1, int y1, int human, int computer );
	void Reset();
	int GetBoard( int, int );
	void PanDuan_h();
	void Run();
	void Count();
	int	GetBushu();
	int	GetBushusum();
	int	GetWinner();
	void ZhiNeng_h2();
	void Save();
	void Load();
	void GongJiao_1(int a,int b,int a1,int b1);
	void GongJiao_2(int a,int b,int a1,int b1);
	void ZhiNeng_h1();
	void ZhiNeng_h0();
	void SetKexing();
	int	GetKexingshu();
	int GetFirstsum();
	int GetSecondsum();
	int Getx();
	int Gety();
	int GetBoard2( int, int );
	void SetBoard2();
	void Prev();
	virtual void Serialize1(CArchive& ar);
	virtual void Serialize2(CArchive& ar, int );
	int Getrecord( int x, int y );

private:
	int	Shunxu,Bushu,x,y,x1,y1,Firstsum,Secondsum,Kexing,Bihe,Youxiao,Bubian,Bushusum, winner, ch, ch1, ch2, ch3,
		Kexingshu, x3, y3;
	int	board[ 9 ][ 9 ];
	int board1[ 9 ][ 9 ];
	int board2[ 9 ][ 9 ];
	int record[ 100 ][ 2 ];
};
