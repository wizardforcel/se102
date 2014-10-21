#include "HGEButton.h"

HGEButton::HGEButton(int xx, int yy, int ww, int hh, UINT c, const string &s, HGE *p, hgeFont *f)
	: x(xx), y(yy), wid(ww), hei(hh), str(s), hge(p), fnt(f), clr(c), mouseon(false), lastck(false)
{
	htxt = 0;
	spr = 0;
}

HGEButton::~HGEButton()
{
	rmpic();
}

void HGEButton::Render()
{

	if(spr) //图片模式
	{
		spr->Render(x, y);
		if(mouseon)
		{
			hge->Gfx_RenderLine(x, y, x + wid, y, 0xFFFF0000);
			hge->Gfx_RenderLine(x, y, x, y + hei, 0xFFFF0000);
			hge->Gfx_RenderLine(x, y + hei, x + wid, y + hei, 0xFFFF0000);
			hge->Gfx_RenderLine(x + wid, y, x + wid, y + hei, 0xFFFF0000);
		}
	}
	else //无图模式
	{
		UINT nclr;
		if(mouseon) nclr = 0xFFFF0000;
		else nclr = clr;
		hge->Gfx_RenderLine(x, y, x + wid, y, nclr);
		hge->Gfx_RenderLine(x, y, x, y + hei, nclr);
		hge->Gfx_RenderLine(x, y + hei, x + wid, y + hei, nclr);
		hge->Gfx_RenderLine(x + wid, y, x + wid, y + hei, nclr);
		if(fnt) fnt->Render(x, y, 0, str.c_str());
	}
}

bool HGEButton::Clicked()
{
	bool ck;
	if(hge->Input_GetKeyState(HGEK_LBUTTON))
	{
		float xx, yy;
		hge->Input_GetMousePos(&xx, &yy);
		ck = (xx >= x && xx <= x + wid && yy >= y && yy <= y + hei);
	}
	else ck = false;

	bool retn = lastck && !ck;
	lastck = ck;
	return retn;
}

bool HGEButton::setpic(const string &fname)
{
	rmpic();

	htxt = hge->Texture_Load(fname.c_str());
	if(!htxt) return false;
	spr = new hgeSprite(htxt, 0, 0, wid, hei);
	/*if(!spr)
	{
		hge->Texture_Free(htxt);
		return false;
	}*/
	return true;
	
}

void HGEButton::rmpic()
{
	if(spr)
	{
		delete spr;
		spr = 0;
	}
	if(htxt)
	{
		hge->Texture_Free(htxt);
		htxt = 0;
	}
}

void HGEButton::JdgMsOn()
{
	float xx, yy;
	hge->Input_GetMousePos(&xx, &yy);
	mouseon = (xx >= x && xx <= x + wid && yy >= y && yy <= y + hei);
}