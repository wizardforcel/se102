#include "ChessBoard.h"
#include "HGEChessBoard.h"

#include "Const.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:

	ChessBoard *board;
	ChessClr clr;
	Role rol;
	HGEChessBoard *hgecb; //角色为人时需要

	PlayResult aiplay(); //无棋可下的时候返回Fail
	PlayResult manplay(); //无棋可下的时候返回Fail 用户未输入返回Nop

	

public:

	Player(ChessBoard *cb);
	//~AIPlayer();

	void setclr(ChessClr c) {clr = c;}
	ChessClr getclr() const {return clr;}
	void setrol(Role r) {rol = r;}
	Role getrol() const {return rol;}
	void setHGEBoard(HGEChessBoard *p) {hgecb = p;}

	PlayResult play(); 

};

#endif