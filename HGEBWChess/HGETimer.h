#include <hge\hge.h>
#include <hge\hgefont.h>
#include <time.h>


#ifndef HGETIIMER_H
#define HGETIMER_H

class HGETimer
{
private:

	int timebase;
	int x;
	int y;
	HGE *hge;
	hgeFont *fnt;

public:

	HGETimer(int xx, int yy, HGE *h, hgeFont *f);

	void SetFont(hgeFont *f) {fnt = f;}
	hgeFont *GetFont() const {return fnt;}

	void Render();
	void Reset();


};
#endif