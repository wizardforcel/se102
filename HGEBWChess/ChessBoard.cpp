#include "ChessBoard.h"
#include "FileDlg.h"

#include <stdexcept>
#include <stdlib.h>
#include <fstream>

using namespace std;


void ChessBoard::Reset()
{
	memset(board, None, BOARDSIZE * BOARDSIZE);
	bnum = wnum = 2;
	board[3][3] = White;
	board[3][4] = Black;
	board[4][3] = Black;
	board[4][4] = White;
	cclr = Black;

	replay.clear();
	history.clear();
}

ChessBoard::ChessBoard()
{
	Reset();
}

ChessClr ChessBoard::GetClr(int x, int y)
{
	return ChessClr(board[y][x]);
}

ChessClr ChessBoard::GetClrCK(int x, int y)
{
	if(x < 0 || x >= BOARDSIZE || y < 0 || y >= BOARDSIZE)
		throw exception();
	return GetClr(x, y);
}

bool ChessBoard::SetChessCK(int x, int y, ChessClr s, char dir[9])
{
	if(x >= BOARDSIZE || x < 0 || y >= BOARDSIZE || y < 0)
		throw exception();
	return SetChess(x, y, s, dir);
}

bool ChessBoard::SetChess(int x, int y, ChessClr s, char dir[9])
{
	//??????????????????
	if (board[y][x] != None || (s != Black && s != White)) return false;

	record();
	board[y][x] = s;
	int i;

	//up
	for(i = 1; i <= dir[Up]; i++)
	{
		board[y - i][x] = s;
	}

	//upright
	for(i = 1; i <= dir[UpRight]; i++)
	{
		board[y - i][x + i] = s;
	}

	//right
	for(i = 1; i <= dir[Right]; i++)
	{
		board[y][x + i] = s;
	}

	//downright
	for(i = 1; i <= dir[DownRight]; i++)
	{
		board[y + i][x + i] = s;
	}

	//down
	for(i = 1; i <= dir[Down]; i++)
	{
		board[y + i][x] = s;
	}

	//downleft
	for(i = 1; i <= dir[DownLeft]; i++)
	{
		board[y + i][x - i] = s;
	}

	//left
	for(i = 1; i <= dir[Left]; i++)
	{
		board[y][x - i] = s;
	}

	//upleft
	for(i = 1; i <= dir[UpLeft]; i++)
	{
		board[y - i][x - i] = s;
	}

	if(s == White)
	{
		wnum += dir[8] + 1;
		bnum -= dir[8];
	}
	else if(s == Black)
	{
		bnum += dir[8] + 1;
		wnum -= dir[8];
	}

	replay.push_back(cclr);
	replay.push_back(x);
	replay.push_back(y);

	return true;
}


WinLose ChessBoard::JudgeWin()
{
	if(bnum + wnum == BOARDSIZE * BOARDSIZE)
	{
		if(bnum > wnum) return BlackWin;
		else if(bnum < wnum) return WhiteWin;
		else return Even;
	}
	
	if(bnum == 0) return WhiteWin;
	else if(wnum == 0) return BlackWin;
	else return NoWin;
}

bool ChessBoard::JudgeContinue(ChessClr s)
{
	if(s != Black && s != White) return false;

	char dir[9];

	for(int i = 0; i < BOARDSIZE; i++)
	{
		for(int j = 0; j < BOARDSIZE; j++)
		{
			Power(j, i, s, dir);
			if(dir[8] > 0) return true;
		}
	}

	return false;
}

void ChessBoard::PowerCK(int x, int y, ChessClr s, char dir[9])
{
	//???????
	if(x < 0 || x >= BOARDSIZE || y < 0 || y >= BOARDSIZE)
		throw exception();
	Power(x, y, s, dir);
}


void ChessBoard::Power(int x, int y, ChessClr s, char dir[9])
{
	
	//???????????
	if(board[y][x] != None || (s != Black && s != White))
	{
		dir[8] = 0;
		return;
	}

	//????????????????????
	int sum = 0;
	int i;
	//Status op = Status(1 - s); ????????

	//up
	int valid = false;
	for(i = 1; y - i >= 0; i++)
	{
		if(board[y - i][x] == None) break;
		else if(board[y - i][x] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[Up] = i - 1;
	}
	else dir[Up] = 0;

	//upright
	valid = false;
	for(i = 1; y - i >= 0 && x + i < BOARDSIZE; i++)
	{
		if(board[y - i][x + i] == None) break;
		else if(board[y - i][x + i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[UpRight] = i - 1;
	}
	else dir[UpRight] = 0;

	//right
	valid = false;
	for(i = 1; x + i < BOARDSIZE; i++)
	{
		if(board[y][x + i] == None) break;
		else if(board[y][x + i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[Right] = i - 1;
	}
	else dir[Right] = 0;

	//rightdown
	valid = false;
	for(i = 1; x + i < BOARDSIZE && y + i < BOARDSIZE; i++)
	{
		if(board[y + i][x + i] == None) break;
		else if(board[y + i][x + i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[DownRight] = i - 1;
	}
	else dir[DownRight] = 0;

	//down
	valid = false;
	for(i = 1; y + i < BOARDSIZE; i++)
	{
		if(board[y + i][x] == None) break;
		else if(board[y + i][x] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[Down] = i - 1;
	}
	else dir[Down] = 0;

	//leftdown
	valid = false;
	for(i = 1; y + i < BOARDSIZE && x - i >= 0; i++)
	{
		if(board[y + i][x - i] == None) break;
		else if(board[y + i][x - i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid) 
	{
		sum += i - 1;
		dir[DownLeft] = i - 1;
	}
	else dir[DownLeft] = 0;

	//left
	valid = false;
	for(i = 1; x - i >= 0; i++)
	{
		if(board[y][x - i] == None) break;
		else if(board[y][x - i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[Left] = i - 1;
	}
	else dir[Left] = 0;

	//leftup
	valid = false;
	for(i = 1; x - i >= 0 && y - i >= 0; i++)
	{
		if(board[y - i][x - i] == None) break;
		else if(board[y - i][x - i] == s)
		{
			valid = true;
			break;
		}
	}
	if(valid)
	{
		sum += i - 1;
		dir[UpLeft] = i - 1;
	}
	else dir[UpLeft] = 0;

	dir[8] = sum;
	return;
}

WinLose ChessBoard::JudgeWinByNum()
{
	if(bnum > wnum) return BlackWin;
	else if(wnum > bnum) return WhiteWin;
	else return Even;
}

char *ChessBoard::GetWinMsg(WinLose s)
{
	if(s == BlackWin) return "Black wins!";
	else if(s == WhiteWin) return "White wins!";
	else if(s == Even) return "They are even.";
	else return "";
}

//都用二进制单字节来存 效率高
void ChessBoard::Save() 
{
	try
	{
		FileDlg dlg;
		dlg.SetFilter("存档文件(*.sve)\0*.sve\0\0");
		dlg.SetDefExt("*.sve");
		dlg.SetFileME(false);
		dlg.SetCreateTip(true);
		dlg.SetMode(FileDlg::SaveDlg);

		if(!dlg.show()) return;
		fstream fs(dlg.GetFile(), ios::out | ios::trunc | ios::binary);
		if(!fs) throw exception("文件打开失败！");
		for(int i = 0; i < BOARDSIZE; i++)
		{
			for(int j = 0; j < BOARDSIZE; j++)
			{
				char clr = ChessClr(board[i][j]);
				fs<<clr;
			}
		}
		fs<<(char)bnum;//bnum
		fs<<(char)wnum;//wnum
		fs<<(char)cclr; //current color
		
		for(int i = 0; i < replay.size(); i++)
		{
			fs<<replay.at(i);
		}

		fs.close();
		MessageBoxA(0, "保存成功！", "", 0);
	}
	catch(exception &ex) 
	{
		MessageBoxA(0, ex.what(), 0, 0);
	}
}

void ChessBoard::Load()
{
	try
	{
		FileDlg dlg;
		dlg.SetFilter("存档文件(*.sve)\0*.sve\0\0");
		dlg.SetDefExt("*.sve");

		if(!dlg.show()) return;
		fstream fs(dlg.GetFile(), ios::in | ios::binary);
		if(!fs) throw exception("文件打开失败！");
		char tmp[BOARDSIZE][BOARDSIZE];
		char chr;
		for(int i = 0; i < BOARDSIZE; i++)
		{
			for(int j = 0; j < BOARDSIZE; j++)
			{
				if(fs.eof()) throw exception("文件读取失败！");
				fs>>chr;
				tmp[i][j] = ChessClr(chr);
			}
		}
		//bnum
		if(fs.eof()) throw exception("文件读取失败！");
		fs>>chr;
		int btmp = chr;
		//wnum
		if(fs.eof()) throw exception("文件读取失败！");
		fs>>chr;
		int wtmp = chr;
		//cclr
		if(fs.eof()) throw exception("文件读取失败！");
		fs>>chr;
		ChessClr ctmp = ChessClr(chr);

		vector<char> retmp;
		while(!fs.eof())
		{
			fs>>chr;
			retmp.push_back(chr);
		}

		fs.close();

		//转成int*赋值次数少效率高
		int *src = (int *)tmp[0];
		int *dest = (int *)board[0];
		for(int i = 0; i < BOARDSIZE * BOARDSIZE / sizeof(int); i++)
		{
			dest[i] = src[i];
		}

		bnum = btmp;
		wnum = wtmp;
		cclr = ctmp;
		replay = retmp;
		//valid1 = valid2 = false;
		history.clear();

		MessageBoxA(0, "读取成功！", "", 0);
	}
	catch(exception &ex)
	{
		MessageBoxA(0, ex.what(), 0, 0);
	}
}

void ChessBoard::record()
{

	int *src,
		*dest;
	/*//1 -> 2
	if(valid1)
	{
		src = (int *)board1[0];
		dest = (int *)board2[0];
		for(int i = 0; i < BOARDSIZE * BOARDSIZE / sizeof(int); i++)
		{
			dest[i] = src[i];
		}
		bnum2 = bnum1;
		wnum2 = wnum1;
		cclr2 = cclr1;
		valid2 = true;
	}
	//0 -> 1
	src = (int *)board[0];
	dest = (int *)board1[0];
	for(int i = 0; i < BOARDSIZE * BOARDSIZE / sizeof(int); i++)
	{
		dest[i] = src[i];
	}
	bnum1 = bnum;
	wnum1 = wnum;
	cclr1 = cclr;
	valid1 = true;*/

	BoardItem item;
	item.bnum = bnum;
	item.wnum = wnum;
	item.cclr = cclr;

	dest = (int *)item.board[0];
	src = (int *)board[0];
	for(int i = 0; i < BOARDSIZE * BOARDSIZE / sizeof(int); i++)
	{
		dest[i] = src[i];
	}

	history.push_back(item);

}

bool ChessBoard::undo(int step)
{
	/*if(!valid2) return false;
	char *src = board2[0];
	char *dest = board[0];
	for(int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		dest[i] = src[i];
	}
	bnum = bnum2;
	wnum = wnum2;
	cclr = cclr2;
	valid2 = valid1 = false;

	replay.pop_back();
	replay.pop_back();
	replay.pop_back();
	replay.pop_back();
	replay.pop_back();
	replay.pop_back();

	return true;*/

	if(history.size() < step) return false;

	for(int i = 1; i < step; i++)
	{
		history.pop_back();
	}

	int i = history.size() - 1;
	bnum = history.at(i).bnum;
	wnum = history.at(i).wnum;
	cclr = history.at(i).cclr;

	int *src = (int *)history.at(i).board[0];
	int *dest = (int *)board[0];
	for(int i = 0; i < BOARDSIZE * BOARDSIZE / sizeof(int); i++)
	{
		dest[i] = src[i];
	}

	history.pop_back();

	for(int i = 0; i < step; i++)
	{
		replay.pop_back();
		replay.pop_back();
		replay.pop_back();
	}
}

int ChessBoard::get_lx() const
{
	if(replay.size() < 3) return -1;
	else return replay.at(replay.size() - 2);
}
int ChessBoard::get_ly() const
{
	if(replay.size() < 3) return -1;
	else return replay.at(replay.size() - 1);
}

void ChessBoard::SaveReplay()
{
	FileDlg dlg;
	dlg.SetFilter("录像文件(*.rply)\0*.rply\0\0");
	dlg.SetDefExt("*.sve");
	dlg.SetFileME(false);
	dlg.SetCreateTip(true);
	dlg.SetMode(FileDlg::SaveDlg);

	if(!dlg.show()) return;
	fstream fs(dlg.GetFile(), ios::out | ios::trunc | ios::binary);
	if(!fs) throw exception("文件打开失败！");
	for(int i = 0; i < replay.size(); i++)
	{
		fs<<replay.at(i);
	}
	fs.close();
	MessageBoxA(0, "保存完毕！", "", 0);

}