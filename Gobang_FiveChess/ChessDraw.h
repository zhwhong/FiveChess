#pragma once
//  ChessDraw.h
//  Build   on  2015.11.15  
//  Copyright(C) by Hong Zhiwei, Liu Weishun, Sun Zhiwei
//  Email: 1359434736@qq.com
//
//  License
//  This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)
//  本项目所有源码均采用CPOL开源协议，详细内容请于Code Project 查阅


class CChessDraw
{
public:
	CChessDraw(void);
	~CChessDraw(void);

	void    InitBoard(CRect	rect, UINT uiRows, UINT	uiCols, UINT uiBoardWidth, UINT	uiPieceRadius);

	void	SetDC(CDC*	pDC);									// 设置绘图DC
	void	DrawBackground();							        // 画背景
	void	DrawBoard();									    // 画棋盘
//画棋子函数重载
	BOOL	DrawPiece(CPoint pt, BOOL bBlack);					// 画棋子
	BOOL	DrawPiece(UINT uiX,	UINT uiY, BOOL bBlack);			// 画棋子		
//给当前棋子做标记函数重载
	void	DrawPieceCur(CPoint	pt);							// 给当前的棋子加上标记
	void	DrawPieceCur(UINT uiX, UINT	uiY);					// 给当前的棋子加上标记

	CRect	GetRectBoard();	// 获取棋盘区域	
	BOOL	GetCoordinateWithPoint(CPoint& pt, UINT* puiX = NULL, UINT*	puiY = NULL);	// 已知pt，获取棋盘坐标点(puiX,	puiY)	
	BOOL	GetPointWithCoordinate(CPoint& pt, UINT	uiX, UINT uiY);                     // 已知棋盘坐标点(puiX,	puiY)，获取pt

//	void	    SetColorBK(COLORREF crBegin, COLORREF crEnd, BOOL bVertical = FALSE);		    // 设置背景颜色
//	void	    SetColorBoard(COLORREF cr);		// 设置棋盘颜色
//	void	    SetColorPiece(COLORREF cr);		// 设置棋子颜色

private:
	CDC*		m_pDC;					// 绘图DC
	CRect		m_rcBK;					// 背景区域	
	CRect		m_rcBoard;				// 棋盘区域	

	UINT		m_uiBoardCols;			// 棋盘的列数
	UINT		m_uiBoardRows;		    // 棋盘的行数
	UINT		m_uiPieceRadius;		// 棋子半径
	UINT		m_uiBoardWidth;		    // 每一格棋盘的边长(正方形格子)

	COLORREF	m_crBKBegin;			// 渐变色起始端
	COLORREF	m_crBKEnd;				// 结尾端
	COLORREF	m_crBoard;				// 棋盘线条的颜色

	void		DrawSpecialPoints();	// 画指定的点，如五子棋中的天元等5个点	这里每种棋的规则都不一样，因此需单独修改
};

