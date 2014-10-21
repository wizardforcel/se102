#include "HGETimer.h"


HGETimer::HGETimer(int xx, int yy, HGE *h, hgeFont *f)
	: x(xx), y(yy), hge(h), fnt(f)
{
	Reset();
}

void HGETimer::Reset()
{
	timebase = time(0);
}

void HGETimer::Render()
{
	if(fnt)
	{
		int ntime = time(0);
		ntime -= timebase;
		int hr = ntime / 3600;
		int min = ntime % 3600 / 60;
		int sec = ntime % 3600 % 60;
		fnt->printf(x, y, 0, "Time %d:%d:%d", hr, min, sec);
	}
}