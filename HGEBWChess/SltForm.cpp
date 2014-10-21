#include "SltForm.h"
#include <Windows.h>

SltForm::SltForm() : Fl_Window(500, 200, 300, 400, "Please Selete Mode")
{
	mode = 0;

	color(WCOLOR);
	begin();

	PVC = new Fl_Button(80, 50, 150, 50, "Player vs Computer");
	PVC->color(WCOLOR);
	PVC->callback((Fl_Callback *)PVC_OnClick, this);

	PVP = new Fl_Button(80, 150, 150, 50, "Player vs Player");
	PVP->color(WCOLOR);
	PVP->callback((Fl_Callback *)PVP_OnClick, this);

	Esc = new Fl_Button(80, 250, 150, 50, "Exit");
	Esc->color(WCOLOR);
	Esc->callback((Fl_Callback *)Esc_OnClick, this);

	end();

}

SltForm::~SltForm()
{
	delete PVC, PVP, Esc;
}

void *SltForm::PVC_OnClick(Fl_Widget *w, void *d)
{
	SltForm *p = (SltForm *)d;
	if(MessageBoxA(0, "是否要先手？", "", MB_YESNO) == IDYES)
		p->mode = MODE_PVCFIR;
	else p->mode = MODE_PVCLAS;
	p->hide();
	return 0;
}

void *SltForm::PVP_OnClick(Fl_Widget *w, void *d)
{
	SltForm *p = (SltForm *)d;
	p->mode = MODE_PVP;
	p->hide();
	return 0;
}

void *SltForm::Esc_OnClick(Fl_Widget *w, void *d)
{
	SltForm *p = (SltForm *)d;
	p->mode = MODE_ESC;
	p->hide();
	return 0;
}

int SltForm::getmode() const
{
	return mode;
}

void SltForm::setmode(int m)
{
	mode = m;
}