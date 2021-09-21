//*****************************************************************************
// FILE:            WinMTRMain.cpp
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTRMain.h"
#include "WinMTRDialog.h"
#include "WinMTRHelp.h"
#include <algorithm>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

WinMTRMain WinMTR;

//*****************************************************************************
// BEGIN_MESSAGE_MAP
//*****************************************************************************
BEGIN_MESSAGE_MAP(WinMTRMain, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

//*****************************************************************************
// WinMTRMain::WinMTRMain
//*****************************************************************************
WinMTRMain::WinMTRMain()
{
}

//*****************************************************************************
// WinMTRMain::InitInstance
//*****************************************************************************
BOOL WinMTRMain::InitInstance()
{
	INITCOMMONCONTROLSEX icex= {sizeof(INITCOMMONCONTROLSEX),ICC_STANDARD_CLASSES};
	InitCommonControlsEx(&icex);
	if(!AfxSocketInit()) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	
	AfxEnableControlContainer();
	
	
	WinMTRDialog mtrDialog;
	m_pMainWnd = &mtrDialog;
	
	if(strlen(m_lpCmdLine)) {
		strcat(m_lpCmdLine," ");
		ParseCommandLineParams(m_lpCmdLine, &mtrDialog);
	}
	
	mtrDialog.DoModal();
	
	
	return FALSE;
}


//*****************************************************************************
// WinMTRMain::ParseCommandLineParams
//*****************************************************************************
void WinMTRMain::ParseCommandLineParams(LPTSTR cmd, WinMTRDialog* wmtrdlg)
{
	char value[1024];
	std::string host_name = "";
	
	if(GetParamValue(cmd, "help",'h', value)) {
		WinMTRHelp mtrHelp;
		m_pMainWnd = &mtrHelp;
		mtrHelp.DoModal();
		exit(0);
	}
	
	if(GetHostNameParamValue(cmd, host_name)) {
		wmtrdlg->SetHostName(host_name.c_str());
	}
	if(GetParamValue(cmd, "interval",'i', value)) {
		wmtrdlg->SetInterval((float)atof(value));
		wmtrdlg->hasIntervalFromCmdLine = true;
	}
	if(GetParamValue(cmd, "size",'s', value)) {
		wmtrdlg->SetPingSize((WORD)atoi(value));
		wmtrdlg->hasPingsizeFromCmdLine = true;
	}
	if(GetParamValue(cmd, "maxLRU",'m', value)) {
		wmtrdlg->SetMaxLRU(atoi(value));
		wmtrdlg->hasMaxLRUFromCmdLine = true;
	}
	if(GetParamValue(cmd, "numeric",'n', NULL)) {
		wmtrdlg->SetUseDNS(FALSE);
		wmtrdlg->hasUseDNSFromCmdLine = true;
	}
	if(GetParamValue(cmd, "ipv6",'6', NULL)) {
		wmtrdlg->hasUseIPv6FromCmdLine=true;
		wmtrdlg->useIPv6=1;
	}
	if(GetParamValue(cmd, "ipv4",'4', NULL)) {
		wmtrdlg->hasUseIPv6FromCmdLine=true;
		wmtrdlg->useIPv6=0;
	}
}

//*****************************************************************************
// WinMTRMain::GetParamValue
//*****************************************************************************
int WinMTRMain::GetParamValue(LPTSTR cmd, char* param, char sparam, char* value)
{
	char* p;
	
	char p_long[1024];
	char p_short[1024];
	
	sprintf(p_long,"--%s ", param);
	sprintf(p_short,"-%c ", sparam);
	
	if((p=strstr(cmd, p_long))) ;
	else
		p=strstr(cmd, p_short);
		
	if(p == NULL)
		return 0;
		
	if(!value)
		return 1;
		
	while(*p && *p!=' ')
		p++;
	while(*p==' ') p++;
	
	int i = 0;
	while(*p && *p!=' ')
		value[i++] = *p++;
	value[i]='\0';
	
	return 1;
}

//*****************************************************************************
// WinMTRMain::GetHostNameParamValue
//*****************************************************************************
int WinMTRMain::GetHostNameParamValue(LPTSTR cmd, std::string& host_name)
{
// WinMTR -h -i 1 -n google.com
	size_t size = strlen(cmd);
	std::string name = "";
	while(cmd[--size] == ' ');
	
	size++;
	while(size-- && cmd[size] != ' ' && (cmd[size] != '-' || cmd[size - 1] != ' ')) {
		name = cmd[size ] + name;
	}
	
	if(size == -1) {
		if(name.length() == 0) {
			return 0;
		} else {
			host_name = name;
			return 1;
		}
	}
	if(cmd[size] == '-' && cmd[size - 1] == ' ') {
		// no target specified
		return 0;
	}
	
	std::string possible_argument = "";
	
	while(size-- && cmd[size] != ' ') {
		possible_argument = cmd[size] + possible_argument;
	}
	
	if(possible_argument.length() && (possible_argument[0] != '-' || possible_argument == "-n" || possible_argument == "--numeric" || possible_argument == "-6" || possible_argument == "--ipv6" || possible_argument == "-4" || possible_argument == "--ipv4")) {
		host_name = name;
		return 1;
	}
	
	return 0;
}
