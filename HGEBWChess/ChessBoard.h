#include "Const.h"

#include <vector>
using namespace std;

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

struct BoardItem
{
	char board[BOARDSIZE][BOARDSIZE];
	unsigned char bnum;
	unsigned char wnum;
	ChessClr cclr;
};

class ChessBoard
{
private:

	char board[BOARDSIZE][BOARDSIZE];
	unsigned char bnum;
	unsigned char wnum;
	ChessClr cclr; //current color

	vector<char> replay;
	vector<BoardItem> history;

	//悔棋用
	void record();

public:

	ChessBoard();
	void Reset();
	
	int get_lx() const;
	int get_ly() const;

	ChessClr get_cclr() const {return cclr;}
	void set_cclr(ChessClr c) {cclr = c;}

	ChessClr GetClr(int x, int y); //不做下标检查
	ChessClr GetClrCK(int x, int y);//下标越界抛异常

	int GetBNum() const {return bnum;}
	int GetWNum() const {return wnum;}

	//只是置棋子，不进行判断 x,y,s,dir必须与Power中取出来的完全一致
	bool SetChess(int x, int y, ChessClr s, char dir[9]);
	//做下标检查的版本
	bool SetChessCK(int x, int y, ChessClr s, char dir[9]);

	WinLose JudgeWin(); //判断是否有胜负
	bool JudgeContinue(ChessClr s); //判断一方是否可继续下棋
	WinLose JudgeWinByNum(); //无棋可下时判断谁的棋子多来定输赢
	
	//计算指定位置的权重 即最多能翻转多少个格子 无法落子时权重为0
	//dir中分别为各个方向以及总权重
	void Power(int x, int y, ChessClr s, char dir[9]);
	//带下标检查的版本
	void PowerCK(int x, int y, ChessClr s, char dir[9]);

	static char *GetWinMsg(WinLose s);
	
	//load&save
	void Load();
	void Save();
	void SaveReplay();

	//悔棋用
	bool undo(int step);
};

#endif
