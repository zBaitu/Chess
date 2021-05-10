// ChessView.h : CChessView ��Ľӿ�
//
#pragma once
#include "afxwin.h"

#include "JiuGongQi.h"
#include "JiuGongQi_rj.h"
#include "Othello.h"
#include "Othello_rj.h"
#include "InitializeDlg.h"
#include <stack>


class CChessView : public CFormView
{
protected: // �������л�����
	CChessView();
	DECLARE_DYNCREATE(CChessView)

public:
	enum{ IDD = IDD_CHESS_FORM };

// ����
public:
	CChessDoc* GetDocument() const;

	CBitmap	m_Bitmaps[ 42 ];	// ����λͼ
	int	image1Width;	// λͼ��������Ҫ�ߴ�
	int image2Width;
	int	boardWidth;		// ���̴�С
	int x0, y0;
	CString m_strFilename;		// Ҫ�����������ļ���
	
	JiuGongQi	jiugongqi;		// �ĸ��������Ĭ�ϳ�ʼ��
	JiuGongQi_rj	jiugongqi_rj;
	Othello		othello;
	Othello_rj		othello_rj;


// ����
public:
	void Initialize();		// ��ʼ����Ϸ��������ʼ���̣� ���˫���ĳ�ʼ��Ϣ
	
	void Draw_Color( int type );	// �����������·��ġ��ֵ�������廭����ɫ���ɫ��Բ�Σ� ��ʾ����

	// �Ź��壨�������˶�ս���˻���ս���Ļ����̣����������Ϣ
	void Draw_JiuGongQi( CDC *, int type );		
	void JiuGongQi_Do( int, int );
	void JiuGongQi_Message( int, int, int );
	void JiuGongQi_rj_Do( int, int, int, int );
	void JiuGongQi_rj_Message( int, int, int, int, int, int );

	// �ڰ��壨�������˶�ս���˻���ս���Ļ����̣����������Ϣ��
	void Draw_Othello( CDC *, int );
	void Othello_Do( int, int );
	void Othello_Message( int, int, int );
	void Othello_rj_Do( int, int, int, int );
	void Othello_rj_Message( int, int, int, int, int, int );

	// �ļ��Ĵ��л����������
	BOOL IsValidFilename(CString const& strFilename);
	BOOL CanSerialize();
	virtual void Serialize(CArchive& ar);

	// ��������֡�ʱ�� List Box ���������������
	void LoadOthelloLbx();
	void LoadOthello_rj_Lbx();
	void LoadJiuGongQiLbx();
	void LoadJiuGongQi_rj_Lbx();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CChessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	// ���DDX�ؼ�����
	int b_discs;
	int b_moves;
	int w_discs;
	int w_moves;
	CListBox lbx;

	// ���Ͳ˵���ť����Ӧ����
	afx_msg void OnFileNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // ChessView.cpp �еĵ��԰汾
inline CChessDoc* CChessView::GetDocument() const
   { return reinterpret_cast<CChessDoc*>(m_pDocument); }
#endif

