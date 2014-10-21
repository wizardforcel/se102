#include "HGEChessBoard.h"

HGEChessBoard::HGEChessBoard(int xx, int yy, int ll, ChessBoard *b, HGE *p)
	: x(xx), y(yy), boxlen(ll), hge(p), board(b), hint(false) {loadsrc();}

HGEChessBoard::~HGEChessBoard() {delsrc();}

void HGEChessBoard::loadsrc()
{
	BTxt = hge->Texture_Load("img//Black.png");
	WTxt = hge->Texture_Load("img//White.png");
	BSpr = new hgeSprite(BTxt, 0, 0, boxlen - 2, boxlen - 2);
	WSpr = new hgeSprite(WTxt, 0, 0, boxlen - 2, boxlen - 2);
}

void HGEChessBoard::delsrc()
{
	hge->Texture_Free(BTxt);
	hge->Texture_Free(WTxt);
	delete BSpr;
	delete WSpr;
}

void HGEChessBoard::Render()
{
	//Chessboard
	for(int i = 0; i < 9; i++)
	{
		hge->Gfx_RenderLine(x, y + i * boxlen, x + 8 * boxlen, y + i * boxlen, ARGB(255, 0, 0, 0));
		hge->Gfx_RenderLine(x + i * boxlen, y, x + i * boxlen, y + 8 * boxlen, ARGB(255, 0, 0, 0));
	}

	//chess
	for(int i = 0; i < BOARDSIZE; i++)//y
	{
		for(int j = 0; j < BOARDSIZE; j++)//x
		{
			int xx = x + j * boxlen;
			int yy = y + i * boxlen;
			ChessClr s = board->GetClr(j, i);
			if(s == Black)
			{
				BSpr->Render(xx, yy);
				//RenderCircle(hge, x + BOXLEN / 2, y + BOXLEN / 2, BOXLEN / 2 - 2, ARGB(255, 0, 0, 0));
			}
			else if(s == White)
			{
				WSpr->Render(xx, yy);
				//RenderCircle(hge, x + BOXLEN / 2, y + BOXLEN / 2, BOXLEN / 2 - 2, 0xFFFFFFFF);
			}
		}
	}

	//last
	int xx = board->get_lx();
	int yy = board->get_ly();
	const UINT clr = 0xFFFF0000; //Red
	if(xx >= 0 && xx < BOARDSIZE && yy >= 0 && yy <= BOARDSIZE)
	{
		xx = xx * boxlen + x;
		yy = yy * boxlen + y;
		hge->Gfx_RenderLine(xx, yy, xx, yy + boxlen, clr);
		hge->Gfx_RenderLine(xx, yy, xx + boxlen, yy, clr);
		hge->Gfx_RenderLine(xx + boxlen, yy, xx + boxlen, yy + boxlen, clr);
		hge->Gfx_RenderLine(xx, yy + boxlen, xx + boxlen, yy + boxlen, clr);
	}

	//hint
	const UINT clr2 = 0xFF00FF00; //Green
	if(hint)
	{
		for(int i = 0; i < BOARDSIZE; i++)
		{
			for(int j = 0; j < BOARDSIZE; j++)
			{
				char dir[9];
				board->Power(j, i, board->get_cclr(), dir);
				if(dir[8])
				{
					xx = x + boxlen * j;
					yy = y + boxlen * i;
					hge->Gfx_RenderLine(xx, yy, xx, yy + boxlen, clr2);
					hge->Gfx_RenderLine(xx, yy, xx + boxlen, yy, clr2);
					hge->Gfx_RenderLine(xx + boxlen, yy, xx + boxlen, yy + boxlen, clr2);
					hge->Gfx_RenderLine(xx, yy + boxlen, xx + boxlen, yy + boxlen, clr2);
				}

			}
		}
	}

}
bool HGEChessBoard::Clicked(int &xx, int &yy)
{
	//bool ck;
	if(hge->Input_GetKeyState(HGEK_LBUTTON))
	{

		float x0, y0;
		hge->Input_GetMousePos(&x0, &y0);
		if(x0 >= x && y0 >= y  && x0 < x + BOARDSIZE * boxlen && y0 < y + BOARDSIZE * boxlen)
		{
			int xi = (x0 - x) / boxlen;
			int yi = (y0 - y) / boxlen;
			xx = xi;
			yy = yi;
			hint = false;
			return true;
		}
		else return false;
	}
	else return false;

	//bool retn = lastck && !ck;
	//lastck = ck;
	//return retn;
}
