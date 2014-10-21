#include "OpenFileDlg.h"

OpenFileDlg::OpenFileDlg()
{
	ZeroMemory(this, sizeof(OpenFileDlg));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "";
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szfile;
 	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = szfiletitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
}

bool OpenFileDlg::show()
{
	return GetOpenFileNameA(&ofn);
}