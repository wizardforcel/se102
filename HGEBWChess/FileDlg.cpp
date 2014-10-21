#include "FileDlg.h"

FileDlg::FileDlg()
{
	ZeroMemory(this, sizeof(FileDlg));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "";
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szfile;
 	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = szfiletitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
}

bool FileDlg::show()
{
	if(!mode) return GetOpenFileNameA(&ofn);
	else return GetSaveFileNameA(&ofn);
}