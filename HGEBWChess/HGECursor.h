#include <hge\hge.h>


#ifndef HGECURSOR_H
#define HGECURSOR_H

class HGECursor
{
private:
	int x;
	int y;
	int len;
	int xi;
	int yi;
	UINT clr;
	HGE *hge;

public:
	void Render();
	void Move();

	int get_x() const {return x;}
	void set_x(int xx) {x = xx;}
	int get_y() const {return y;}
	void set_y(int yy) {y = yy;}
	int get_len() const {return len;}
	void set_len(int ll) {len = ll;}
	int get_xi() const {return xi;}
	void set_xi(int nxi) {xi = nxi;}
	int get_yi() const {return yi;}
	void set_yi(int nyi) {yi = nyi;}
	UINT get_clr() const {return clr;}
	void set_clr(UINT c) {clr = c;}

	HGECursor(int xx, int yy, int ll, UINT c, HGE *p);


};
#endif