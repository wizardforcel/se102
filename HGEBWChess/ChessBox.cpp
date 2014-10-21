#include "ChessBox.h"

#include <math.h>

void ChessBox::Render(HGE *hge)
{
	hge->Gfx_RenderLine(x, y, x + len, y, clr);
	hge->Gfx_RenderLine(x, y, x, y + len, clr);
	hge->Gfx_RenderLine(x, y + len, x + len, y + len, clr);
	hge->Gfx_RenderLine(x + len, y, x + len, y + len, clr);

	int r = (len - 1) / 2;
	int cx = x + len / 2;
	int cy = y + len / 2;

	for(double t = 0; t <= 2 * PI; t += PI / 60)
	{
		hge->Gfx_RenderLine(cx + r * cos(t), cy + r * sin(t), cx + r * cos(t + PI / 60), cy + r * sin(t + PI / 60), clr);
	}
}