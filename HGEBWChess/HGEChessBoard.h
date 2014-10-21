#include <hge\hge.h>
#include <hge\hgesprite.h>

#include "ChessBoard.h"
#include "Const.h"

#ifndef HGECHESSBOARD_H
#define HGECHESSBOARD_H

class HGEChessBoard
{

private:

	int x;
	int y;
	int boxlen;
	bool hint;
	ChessBoard *board;
	HGE *hge;
	HTEXTURE BTxt;
	HTEXTURE WTxt;
	hgeSprite *BSpr;
	hgeSprite *WSpr;

	HGEChessBoard(HGEChessBoard &cb);
	HGEChessBoard &operator=(HGEChessBoard &cb);

	void loadsrc();
	void delsrc();

public:

	void Render();
	bool Clicked(int &x, int &y);

	HGEChessBoard(int xx, int yy, int ll, ChessBoard *b, HGE *p = 0);
	~HGEChessBoard();

	int get_x() const {return x;}
	void set_x(int xx) {x = xx;}
	int get_y() const {return y;}
	void set_y(int yy) {y = yy;}
	int get_len() const {return boxlen;}
	void set_len(int ll) {boxlen = ll;}
	//HGE *get_phge() const {return hge;}
	//void set_phge(HGE *p) {hge = p;}
	bool is_hinton() const {return hint;}
	void set_hint(bool h)  {hint = h;}

};
#endif