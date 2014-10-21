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
	HGEChessBoard *hgecb; //��ɫΪ��ʱ��Ҫ

	PlayResult aiplay(); //������µ�ʱ�򷵻�Fail
	PlayResult manplay(); //������µ�ʱ�򷵻�Fail �û�δ���뷵��Nop

	

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