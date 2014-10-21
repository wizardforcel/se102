#include <FL\Fl_Window.H>
#include <FL\Fl.H>
#include <FL\Fl_Button.H>

#define WCOLOR 53U

#define MODE_ESC 0
#define MODE_PVCFIR 1
#define MODE_PVCLAS 2
#define MODE_PVP 3

#ifndef SLTFORM_H
#define SLTFORM_H

class SltForm : public Fl_Window
{
private:
	Fl_Button *PVP;
	Fl_Button *PVC;
	Fl_Button *Esc;

	int mode;

	SltForm(SltForm &w);
	SltForm& operator=(SltForm &w);

	static void *PVC_OnClick(Fl_Widget *w, void *d);
	static void *PVP_OnClick(Fl_Widget *w, void *d);
	static void *Esc_OnClick(Fl_Widget *w, void *d);

public:
	SltForm();
	~SltForm();

	int getmode() const;
	void setmode(int m);


};
#endif