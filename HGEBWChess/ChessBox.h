#include <hge\hge.h>

#ifndef CHESSBOX_H
#define CHESSBOX_H

#define PI 3.14

class ChessBox
{
private:

	int x;
	int y;
	int xi;
	int yi;
	UINT clr;
	int len;

public:

	ChessBox() {len = 50;}

	int get_x() const {return x;}
	void set_x(int nx) {x = nx;}
	int get_y() const {return y;}
	void set_y(int ny) {y = ny;}
	int get_xi() const {return xi;}
	void set_xi(int nxi) {xi = nxi;}
	int get_yi() const {return yi;}
	void set_yi(int nyi) {yi = nyi;}
	UINT get_c() const {return clr;}
	void set_c(UINT nc) {clr = nc;}
	int get_len() const {return len;}
	void set_len(int nl) {len = nl;}

	void Render(HGE *hge);
};
#endif