#include <Windows.h>

#ifndef SaveFileDlg_H
#define SaveFileDlg_H

struct SaveFileDlg
 { 
	OPENFILENAMEA ofn;
	//����� ���ڷ�����Ϣ
	char szfile[MAX_PATH];
	char szfiletitle[MAX_PATH];
	
	SaveFileDlg();
	bool show();
};
#endif