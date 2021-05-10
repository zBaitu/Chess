// ChessView.h : CChessView 类的接口
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
protected: // 仅从序列化创建
	CChessView();
	DECLARE_DYNCREATE(CChessView)

public:
	enum{ IDD = IDD_CHESS_FORM };

// 属性
public:
	CChessDoc* GetDocument() const;

	CBitmap	m_Bitmaps[ 42 ];	// 保存位图
	int	image1Width;	// 位图的两个主要尺寸
	int image2Width;
	int	boardWidth;		// 棋盘大小
	int x0, y0;
	CString m_strFilename;		// 要保存和载入的文件名
	
	JiuGongQi	jiugongqi;		// 四个棋类的类默认初始化
	JiuGongQi_rj	jiugongqi_rj;
	Othello		othello;
	Othello_rj		othello_rj;


// 操作
public:
	void Initialize();		// 初始化游戏，画出初始棋盘， 输出双方的初始信息
	
	void Draw_Color( int type );	// 在主界面右下方的“轮到：”面板画出黑色或白色的圆形， 表示棋子

	// 九宫棋（包括人人对战和人机对战）的画棋盘，处理，输出信息
	void Draw_JiuGongQi( CDC *, int type );		
	void JiuGongQi_Do( int, int );
	void JiuGongQi_Message( int, int, int );
	void JiuGongQi_rj_Do( int, int, int, int );
	void JiuGongQi_rj_Message( int, int, int, int, int, int );

	// 黑白棋（包括人人对战和人机对战）的画棋盘，处理，输出信息，
	void Draw_Othello( CDC *, int );
	void Othello_Do( int, int );
	void Othello_Message( int, int, int );
	void Othello_rj_Do( int, int, int, int );
	void Othello_rj_Message( int, int, int, int, int, int );

	// 文件的串行化保存和载入
	BOOL IsValidFilename(CString const& strFilename);
	BOOL CanSerialize();
	virtual void Serialize(CArchive& ar);

	// “载入棋局”时在 List Box 输出保存的棋的棋谱
	void LoadOthelloLbx();
	void LoadOthello_rj_Lbx();
	void LoadJiuGongQiLbx();
	void LoadJiuGongQi_rj_Lbx();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CChessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	// 五个DDX控件变量
	int b_discs;
	int b_moves;
	int w_discs;
	int w_moves;
	CListBox lbx;

	// 鼠标和菜单按钮的响应函数
	afx_msg void OnFileNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // ChessView.cpp 中的调试版本
inline CChessDoc* CChessView::GetDocument() const
   { return reinterpret_cast<CChessDoc*>(m_pDocument); }
#endif

