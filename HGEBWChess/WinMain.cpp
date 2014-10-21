#include <Windows.h>
#include <hge\hge.h>
#include <hge\hgegui.h>
#include <hge\hgefont.h>
#include <math.h>

#include <fstream>
#include <vector>
using namespace std;


#include "Const.h"
#include "ChessBoard.h"
#include "Player.h"
#include "HGEButton.h"
#include "HGEChessBoard.h"
#include "HGECursor.h"
#include "HGETimer.h"
#include "FileDlg.h"


HGE *HGEInit();
void HGEFinit(HGE *h);

//如果HGE的渲染和帧函数支持类成员 整个程序都可以封装成一个类
//欢迎界面
bool FrameFunc0();
bool RenderFunc0();
//游戏界面
bool FrameFunc();
bool RenderFunc();
//录像回放界面
bool FrameFunc2();
bool RenderFunc2();

void gmstart();
void gmstop(bool done);

void rplystart();
void rplystop(bool done);

//全局句柄
HGE *hge = 0;
HTEXTURE TiTxt;
hgeSprite *TiSpr;
hgeFont *HFont;

//棋盘对象
ChessBoard board;
Player bplayer(&board); //黑方
Player wplayer(&board); //白方

vector<char> replay;
int rplypos;

//有的时候控件的创建需要传入窗口句柄 动态创建易于调整次序

//欢迎界面
HGEButton *PVCFirBtn;//(PVCFIR_X, PVCFIR_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0));
HGEButton *PVCLasBtn;//(PVCLAS_X, PVCLAS_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0));
HGEButton *PVPBtn;//(PVP_X, PVP_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0));
HGEButton *RplyBtn;
HGEButton *EscBtn;//(ESC_X, ESC_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0));

//游戏界面
HGEChessBoard *HGECB;//(START_X, START_Y, BOXLEN, &board);
HGECursor *Cur;
HGEButton *SaveBtn;
HGEButton *LoadBtn;
HGEButton *UndoBtn;
HGEButton *ExitBtn;
HGEButton *HintBtn;
HGETimer *Timer;


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//引擎及句柄初始化
	hge = HGEInit();
	if(!hge->System_Initiate())
	{
		MessageBoxA(0, "HGE初始化失败！", 0, 0);
		return 0;
	}
	TiTxt = hge->Texture_Load("img//title.jpg");
	TiSpr = new hgeSprite(TiTxt, 0, 0, 319, 78);
	HFont = new hgeFont("img//hel.fnt");
	HFont->SetColor(ARGB(255, 0, 0, 0));

	//渲染控件初始化
	PVCFirBtn = new HGEButton(BTN1_X, PVCFIR_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0), "", hge);
	PVCFirBtn->setpic("img//PVCFir.png");
	PVCLasBtn = new HGEButton(BTN1_X, PVCLAS_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0), "", hge);
	PVCLasBtn->setpic("img//PVCLas.png");
	PVPBtn = new HGEButton(BTN1_X, PVP_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0), "" ,hge);
	PVPBtn->setpic("img//PVP.png");
	EscBtn = new HGEButton(BTN1_X, ESC_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0), "" ,hge);
	EscBtn->setpic("img//Esc.png");
	RplyBtn = new HGEButton(BTN1_X, RPLY_Y, BTN1_WID, BTN1_HEI, ARGB(255, 0, 0, 0), "" ,hge);
	RplyBtn->setpic("img//Replay.png");
	HGECB = new HGEChessBoard(START_X, START_Y, BOXLEN, &board, hge);
	Cur = new HGECursor(START_X, START_Y, BOXLEN, 0xFF0000FF, hge); //blue
	SaveBtn = new HGEButton(BTN2_X, SAVE_Y, BTN2_WID, BTN2_HEI, ARGB(255, 0, 0, 0), "Save", hge, HFont);
	LoadBtn = new HGEButton(BTN2_X, LOAD_Y, BTN2_WID, BTN2_HEI, ARGB(255, 0, 0, 0), "Load", hge, HFont);
	UndoBtn = new HGEButton(BTN2_X, UNDO_Y, BTN2_WID, BTN2_HEI, ARGB(255, 0, 0, 0), "Undo", hge, HFont);
	ExitBtn = new HGEButton(BTN2_X, EXIT_Y, BTN2_WID, BTN2_HEI, ARGB(255, 0, 0, 0), "Exit", hge, HFont);
	HintBtn = new HGEButton(BTN2_X, HINT_Y, BTN2_WID, BTN2_HEI, ARGB(255, 0, 0, 0), "Hint", hge, HFont);
	Timer = new HGETimer(BTN2_X, TIMER_Y, hge, HFont);

	//棋盘对象初始化
	bplayer.setclr(Black);
	bplayer.setHGEBoard(HGECB);
	wplayer.setclr(White);
	wplayer.setHGEBoard(HGECB);

	//Let's rock now!
	hge->System_Start();

	//release
	delete HFont;
	delete TiSpr;
	hge->Texture_Free(TiTxt);
	delete PVCFirBtn, PVCLasBtn, PVPBtn, RplyBtn, EscBtn, HGECB, Cur;
	delete UndoBtn, ExitBtn, LoadBtn, SaveBtn, HintBtn, Timer;
	HGEFinit(hge);
	return 0;
}

HGE *HGEInit()
{
	HGE *h = hgeCreate(HGE_VERSION);
	h->System_SetState(HGE_SCREENWIDTH, WWID);
	h->System_SetState(HGE_SCREENHEIGHT, WHEI);
	h->System_SetState(HGE_FRAMEFUNC, FrameFunc0);
	h->System_SetState(HGE_RENDERFUNC, RenderFunc0);
	h->System_SetState(HGE_WINDOWED, true);
	h->System_SetState(HGE_USESOUND, false);
	h->System_SetState(HGE_HIDEMOUSE, false);
	h->System_SetState(HGE_TITLE, "HGE BWChess - Dates Call Back");
	h->System_SetState(HGE_SHOWSPLASH, false);
	return h;
}

void HGEFinit(HGE *h)
{
	h->System_Shutdown();
	h->Release();
}

bool FrameFunc()
{
	WinLose s;
	PlayResult res;
	//判断是否退出
	if(ExitBtn->Clicked()) //回主界面
	{
		gmstop(false);
		return false;
	}
	//读档存档
	if(LoadBtn->Clicked()) board.Load();
	if(SaveBtn->Clicked()) board.Save();

	//悔棋
	if(UndoBtn->Clicked())
	{
		int step;
		if(bplayer.getrol() == wplayer.getrol()) step = 1;
		else step = 2;
		if(!board.undo(step)) MessageBoxA(0, "悔棋失败！", 0, 0);
	}

	//提示
	if(HintBtn->Clicked()) HGECB->set_hint(!HGECB->is_hinton());

	//刷新光标
	Cur->Move();

	//下棋逻辑 判断输赢
	s = board.JudgeWin();
	if(s)
	{
		MessageBoxA(0, ChessBoard::GetWinMsg(s), "", 0);
		gmstop(true);
		return false;
	}
	//黑白方各自下棋
	if(board.get_cclr() == Black)
	{
		res = bplayer.play();
		if(!res)
		{
			if(!board.JudgeContinue(ChessClr::White))
			{
				s = board.JudgeWinByNum();
				MessageBoxA(0, ChessBoard::GetWinMsg(s), "", 0);
				gmstop(true);
				return false;
			}
			else
			{
				board.set_cclr(White);
				return false;
			}
		}
		else if(res == Nop) return false;

		board.set_cclr(White);
	}
	else //White
	{
		res = wplayer.play();
		if(!res)
		{
			if(!board.JudgeContinue(ChessClr::Black))
			{
				s = board.JudgeWinByNum();
				MessageBoxA(0, ChessBoard::GetWinMsg(s), "", 0);
				gmstop(true);
				return false;
			}
			else
			{
				board.set_cclr(Black);
				return false;
			}
		}
		else if(res == Nop) return false;

		board.set_cclr(Black);
	}

	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(ARGB(255, 0x8c, 0x78, 0x53));

	//Chessboard
	HGECB->Render();
	//cursor
	Cur->Render();
	//score board
	HFont->printf(BTN2_X, BLBL_Y, 0, "Black: %d", board.GetBNum());
	HFont->printf(BTN2_X, WLBL_Y, 0, "White: %d", board.GetWNum());
	char *p = (board.get_cclr() == Black) ? "Black" : "White";
	HFont->printf(BTN2_X, NOWLBL_Y, 0, "Now: %s", p);
	Timer->Render();
	//sidebar
	SaveBtn->Render();
	LoadBtn->Render();
	UndoBtn->Render();
	ExitBtn->Render();
	HintBtn->Render();
	
	hge->Gfx_EndScene();
	return false;
}


bool RenderFunc0()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(ARGB(255, 0x8c, 0x78, 0x53));

	//buttons
	TiSpr->Render(TITLE_X, TITLE_Y);
	PVCFirBtn->Render();
	PVCLasBtn->Render();
	PVPBtn->Render();
	RplyBtn->Render();
	EscBtn->Render();

	hge->Gfx_EndScene();
	return false;
}

bool FrameFunc0()
{
	PVCFirBtn->JdgMsOn();
	PVCLasBtn->JdgMsOn();
	PVPBtn->JdgMsOn();
	RplyBtn->JdgMsOn();
	EscBtn->JdgMsOn();

	if(PVCFirBtn->Clicked())
	{
		bplayer.setrol(Human);
		wplayer.setrol(Computer);
		gmstart();
		return false;
	}
	else if(PVCLasBtn->Clicked())
	{
		bplayer.setrol(Computer);
		wplayer.setrol(Human);
		gmstart();
		return false;
	}
	else if(PVPBtn->Clicked())
	{
		bplayer.setrol(Human);
		wplayer.setrol(Human);
		gmstart();
		return false;
	}
	else if(RplyBtn->Clicked())
	{
		rplystart();
		return false;
	}
	else if(EscBtn->Clicked()) return true;

	return false;
}

void gmstart()
{
	board.Reset();
	Timer->Reset();
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
}

void gmstop(bool done)
{
	if(done && MessageBoxA(0, "是否要保存录像？", "",MB_YESNO) == IDYES)
		board.SaveReplay();

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc0);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc0);
}

bool RenderFunc2()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(ARGB(255, 0x8c, 0x78, 0x53));

	//Chessboard
	HGECB->Render();
	//score board
	HFont->printf(BTN2_X, BLBL_Y, 0, "Black: %d", board.GetBNum());
	HFont->printf(BTN2_X, WLBL_Y, 0, "White: %d", board.GetWNum());
	char *p = (board.get_cclr() == Black) ? "Black" : "White";
	HFont->printf(BTN2_X, NOWLBL_Y, 0, "Now: %s", p);
	Timer->Render();
	//sidebar
	ExitBtn->Render();

	hge->Gfx_EndScene();
	return false;
}

bool FrameFunc2()
{
	if(ExitBtn->Clicked())
	{
		rplystop(false);
		return false;
	}
	
	if(rplypos > replay.size() - 3)
	{
		rplystop(true);
		return false;
	}

	ChessClr clr = ChessClr(replay.at(rplypos));
	rplypos++;
	int x = ChessClr(replay.at(rplypos));
	rplypos++;
	int y = ChessClr(replay.at(rplypos));
	rplypos++;

	board.set_cclr(ChessClr(-clr));
	char dir[9];
	board.Power(x, y, clr, dir);
	if(dir[8]) board.SetChess(x, y, clr, dir);

	Sleep(1000);
	return false;
}

void rplystart()
{
	try
	{
		FileDlg ofn;
		ofn.SetFilter("存档文件(*.rply)\0*.rply\0\0");
		if(ofn.show())
		{
			replay.clear();
			rplypos = 0;
			fstream fs(ofn.GetFile(), ios::in | ios::binary);
			if(!fs) throw exception("录像文件打开失败！");
			while(!fs.eof())
			{
				char chr;
				fs>>chr;
				replay.push_back(chr);
			}
			fs.close();

			board.Reset();
			Timer->Reset();
			hge->System_SetState(HGE_FRAMEFUNC, FrameFunc2);
			hge->System_SetState(HGE_RENDERFUNC, RenderFunc2);
		}
	}
	catch(exception &ex)
	{
		MessageBoxA(0, ex.what(), 0, 0);
	}
}
void rplystop(bool done)
{
	if(done) MessageBoxA(0, "回放完毕！", "", 0);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc0);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc0);
}