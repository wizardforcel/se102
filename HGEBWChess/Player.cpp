#include "Player.h"
#include "Const.h"

Player::Player(ChessBoard *cb) : board(cb) {}

PlayResult Player::aiplay()
{
	int maxp = 0;
	int x, y;
	char dir[9];

	for(int i = 0; i < BOARDSIZE; i++)
	{
		for(int j = 0; j < BOARDSIZE; j++)
		{
			board->Power(j, i, clr, dir);
			if(dir[8] > maxp)
			{
				maxp = dir[8];
				x = j;
				y = i;
			}
		}
	}

	if(maxp != 0)
	{
		board->Power(x, y, clr, dir);
		board->SetChess(x, y, clr, dir);
		Sleep(500);
		return Succ;
	}
	else return Fail;
}

PlayResult Player::play()
{
	if(rol == Computer) return aiplay();
	else return manplay();
}

PlayResult Player::manplay()
{
	//判断是否能继续
	if(!board->JudgeContinue(clr)) return Fail;
	//读取鼠标操作
	int x, y;
	if(!hgecb->Clicked(x, y)) return Nop;
	char dir[9];
	board->Power(x, y, clr, dir);
	if(!dir[8]) return Nop;
	board->SetChess(x, y, clr, dir);
	return Succ;
}