#include <Windows.h>

#ifndef FileDlg_H
#define FileDlg_H

class FileDlg
 { 

 public:

	 enum Mode {OpenDlg, SaveDlg};
 
private:
 
	OPENFILENAMEA ofn;
	//新添加 用于返回信息
	char szfile[MAX_PATH];
	char szfiletitle[MAX_PATH];
	Mode mode;
	
public:
	
	FileDlg();
	bool show();
	
	void SetMode(Mode m) {mode = m;}
	Mode GetMode() {return mode;}
	
	void SetHwndOwner(HWND p) {ofn.hwndOwner = p;}
	HWND GetHwndOwner() {return ofn.hwndOwner;}
	
	void SetFilter(const char *str) {ofn.lpstrFilter = str;}
	const char *GetFilter() {return ofn.lpstrFilter;}
	
	char *GetFile() {return ofn.lpstrFile;}
	
	int GetFileNum() {return ofn.nMaxFile;}
	
	void SetInitialDir(const char *p) {ofn.lpstrInitialDir = p;}
	const char *GetInitialDir() {return ofn.lpstrInitialDir;}
	
	void SetTitle(const char *p) {ofn.lpstrTitle = p;}
	const char *GetTitle() {return ofn.lpstrTitle;}
	
	void SetDefExt(const char *p) {ofn.lpstrDefExt = p;}
	const char *GetDefExt() {return ofn.lpstrDefExt;}
	
	void SetAllowMulti(bool b)
	{
		if(b) ofn.Flags &= OFN_ALLOWMULTISELECT;
		else ofn.Flags |= ~OFN_ALLOWMULTISELECT;
	}
	bool GetAllowMulti()
	{
		return ofn.Flags & OFN_ALLOWMULTISELECT == ofn.Flags;
	}
	
	void SetCreateTip(bool b)
	{
		if(b) ofn.Flags &= OFN_CREATEPROMPT;
		else ofn.Flags |= ~OFN_CREATEPROMPT;	
	}
	bool GetCreateTip()
	{
		return ofn.Flags & OFN_CREATEPROMPT == ofn.Flags;
	}
	
	void SetFileME(bool b)
	{
		if(b) ofn.Flags &= OFN_FILEMUSTEXIST;
		else ofn.Flags |= ~OFN_FILEMUSTEXIST;
	}
	bool GetFileME()
	{
		return ofn.Flags & OFN_FILEMUSTEXIST == ofn.Flags;
	}
	
	void SetPathME(bool b)
	{
		if(b) ofn.Flags &= OFN_PATHMUSTEXIST;
		else ofn.Flags |= ~OFN_PATHMUSTEXIST;
	}
	bool GetPathME()
	{
		return ofn.Flags & OFN_PATHMUSTEXIST == ofn.Flags;
	}
	
	
};
#endif