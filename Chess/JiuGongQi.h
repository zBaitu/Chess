#pragma once


class JiuGongQi
{
public:
	JiuGongQi(void);
	~JiuGongQi(void);

public:
	void Main( int x, int y );		// �ӿں���
	int	GetBoard( int x, int y );	// �õ����̸��ӵ���Ϣ
	void PanDuan_j();		// �жϺ���
	int GetWinner();		
	void Reset();
	int GetBushu();
	int Getx();
	int Gety();
	void Prev();	// �ָ���ǰ�����Ϣ
	// �������л�����
	virtual void Serialize1(CArchive& ar);
	virtual void Serialize2(CArchive& ar, int type );
	int Getrecord( int x, int y );
	
private:
	int error, Shunxu, Bushu, x, y, x1, y1, Firstsum, Secondsum, Qizishu, ch, ch1, winner;
	int board[ 4 ][ 4 ];
	int record[ 9 ][ 2 ];
};
