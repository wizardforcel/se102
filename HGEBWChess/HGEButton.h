#include <hge\hge.h>
#include <hge\hgefont.h>

#include <string>
using namespace std;

#ifndef HGEBUTTON_H
#define HGEBUTTON_H

class HGEButton
{
private:

	int x;
	int y;
	int wid;
	int hei;
	UINT clr;
	bool mouseon;
	bool lastck;
	HGE *hge;
	hgeFont *fnt;
	string str;

	HTEXTURE htxt;
	hgeSprite *spr;

	HGEButton(HGEButton &b);
	HGEButton &operator=(HGEButton &b);

public:

	int get_x() const {return x;}
	void set_x(int xx) {x = xx;}
	int get_y() const {return y;}
	void set_y(int yy) {y = yy;}
	int get_w() const {return wid;}
	void set_w(int ww) {wid = ww;}
	int get_h() const {return hei;}
	void set_h(int hh) {hei = hh;}
	//HGE *get_phge() const {return hge;}
	//void set_phge(HGE *p) {hge = p;}
	hgeFont *get_fnt() const {return fnt;}
	void set_fnt(hgeFont *f) {fnt = f;}
	string get_str() const {return str;}
	void set_str(const string &s) {str = s;}
	UINT get_clr() const {return clr;}
	void set_clr(UINT c) {clr = c;}

	void Render();
	bool Clicked(); //前一帧点击且后一帧没点击

	HGEButton(int xx, int yy, int ww, int hh, UINT c, const string &s = "", HGE *p = 0, hgeFont *f = 0);
	~HGEButton();

	bool setpic(const string &fname);
	void rmpic();

	void JdgMsOn();

};
#endif