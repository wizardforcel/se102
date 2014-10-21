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

	//������
	void record();

public:

	ChessBoard();
	void Reset();
	
	int get_lx() const;
	int get_ly() const;

	ChessClr get_cclr() const {return cclr;}
	void set_cclr(ChessClr c) {cclr = c;}

	ChessClr GetClr(int x, int y); //�����±���
	ChessClr GetClrCK(int x, int y);//�±�Խ�����쳣

	int GetBNum() const {return bnum;}
	int GetWNum() const {return wnum;}

	//ֻ�������ӣ��������ж� x,y,s,dir������Power��ȡ��������ȫһ��
	bool SetChess(int x, int y, ChessClr s, char dir[9]);
	//���±���İ汾
	bool SetChessCK(int x, int y, ChessClr s, char dir[9]);

	WinLose JudgeWin(); //�ж��Ƿ���ʤ��
	bool JudgeContinue(ChessClr s); //�ж�һ���Ƿ�ɼ�������
	WinLose JudgeWinByNum(); //�������ʱ�ж�˭�����Ӷ�������Ӯ
	
	//����ָ��λ�õ�Ȩ�� ������ܷ�ת���ٸ����� �޷�����ʱȨ��Ϊ0
	//dir�зֱ�Ϊ���������Լ���Ȩ��
	void Power(int x, int y, ChessClr s, char dir[9]);
	//���±���İ汾
	void PowerCK(int x, int y, ChessClr s, char dir[9]);

	static char *GetWinMsg(WinLose s);
	
	//load&save
	void Load();
	void Save();
	void SaveReplay();

	//������
	bool undo(int step);
};

#endif
