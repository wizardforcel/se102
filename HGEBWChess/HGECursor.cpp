#include "HGECursor.h"

#include "Const.h"

HGECursor::HGECursor(int xx, int yy, int ll, UINT c, HGE *p)
	: x(xx), y(yy), len(ll), hge(p), xi(0), yi(0), clr(c) {}

void HGECursor::Render()
{
	int xx = x + xi * len,
		yy = y + yi * len;
	hge->Gfx_RenderLine(xx, yy, xx + len, yy, clr);
	hge->Gfx_RenderLine(xx, yy, xx, yy + len, clr);
	hge->Gfx_RenderLine(xx, yy + len, xx + len, yy + len, clr);
	hge->Gfx_RenderLine(xx + len, yy, xx + len, yy + len, clr);
}

void HGECursor::Move()
{

	//键盘模式
	/*const UINT timedelay = 100;

	if(hge->Input_GetKeyState(HGEK_LEFT))
	{
		if(xi > 0) xi -= 1;
		Sleep(timedelay);
	}
	else if(hge->Input_GetKeyState(HGEK_RIGHT))
	{
		if(xi < BOARDSIZE - 1) xi += 1;
		Sleep(timedelay);
	}

	if(hge->Input_GetKeyState(HGEK_UP))
	{
		if(yi > 0) yi -= 1;
		Sleep(timedelay);
	}
	else if(hge->Input_GetKeyState(HGEK_DOWN))
	{
		if(yi < BOARDSIZE - 1) yi += 1;
		Sleep(timedelay);
	}*/

	//鼠标模式
	float x0, y0;
	hge->Input_GetMousePos(&x0, &y0);
	if(x0 >= x && y0 >= y  && x0 < x + BOARDSIZE * len && y0 < y + BOARDSIZE * len)
	{
		int xx = (x0 - x) / len;
		int yy = (y0 - y) / len;
		xi = xx;
		yi = yy;
	}

}