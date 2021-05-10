#pragma once


class Othello
{
public:
	Othello(void);
	~Othello(void);

public:
	int	Main( int x1, int y1 );
	void Reset();
	int GetBoard( int, int );
	void PanDuan_h();
	void Run();
	void Count();
	int	GetBushu();
	int	GetBushusum();
	int	GetWinner();
	int GetFirstsum();
	int GetSecondsum();
	int GetKexingshu();
	void SetKexing();
	int Getx();
	int Gety();
	int GetBoard1( int, int );
	void SetBoard1();
	void Prev();
	virtual void Serialize1(CArchive& ar);
	virtual void Serialize2(CArchive& ar, int );
	int Getrecord( int x, int y );

private:
	int	Shunxu,Bushu,x,y,Firstsum,Secondsum,Kexing,Bihe,Youxiao,Bubian,Bushusum, winner, ch, ch1, ch2,
		Kexingshu, x2, y2;
	int	board[ 9 ][ 9 ], board1[ 9 ][ 9 ];
	int record[ 100 ][ 2 ];
};
