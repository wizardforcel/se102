#include <Windows.h>

#ifndef OpenFileDlg_H
#define OpenFileDlg_H

struct OpenFileDlg
 { 
	OPENFILENAMEA ofn;
	//����� ���ڷ�����Ϣ
	char szfile[MAX_PATH];
	char szfiletitle[MAX_PATH];
	
	OpenFileDlg();
	bool show();
};
#endif