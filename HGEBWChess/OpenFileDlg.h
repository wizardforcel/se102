#include <Windows.h>

#ifndef OpenFileDlg_H
#define OpenFileDlg_H

struct OpenFileDlg
 { 
	OPENFILENAMEA ofn;
	//新添加 用于返回信息
	char szfile[MAX_PATH];
	char szfiletitle[MAX_PATH];
	
	OpenFileDlg();
	bool show();
};
#endif