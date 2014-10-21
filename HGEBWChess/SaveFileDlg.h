#include <Windows.h>

#ifndef SaveFileDlg_H
#define SaveFileDlg_H

struct SaveFileDlg
 { 
	OPENFILENAMEA ofn;
	//新添加 用于返回信息
	char szfile[MAX_PATH];
	char szfiletitle[MAX_PATH];
	
	SaveFileDlg();
	bool show();
};
#endif