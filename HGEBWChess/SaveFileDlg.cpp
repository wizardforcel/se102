#include "SaveFileDlg.h"

SaveFileDlg::SaveFileDlg()
{
	ZeroMemory(this, sizeof(SaveFileDlg));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "";
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szfile;
 	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = szfiletitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_EXPLORER;
}

bool SaveFileDlg::show()
{
	return GetSaveFileNameA(&ofn);
}