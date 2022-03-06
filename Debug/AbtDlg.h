#ifndef WXBITS_ABT_DLG
#define WXBITS_ABT_DLG

#include <wx/wxprec.h>


#ifdef __BORLANDC__
#pragma hdrstop
#endif


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef wxUSE_ABOUTDLG
#include <wx/aboutdlg.h>
#endif //wxUSE_ABOUT_DLG

#include <wx/generic/aboutdlgg.h>

#include "AppGlobals.h"

#include <wx/statline.h>






class wBAboutDialog :public  wxGenericAboutDialog {

public :
	wBAboutDialog(wxWindow *parent,wxAboutDialogInfo info)
	{
		
		Create(info,parent);

	}

	virtual void DoAddCustomControls() wxOVERRIDE
	{
		AddCollapsiblePane("Compiler Developer", "Ganesh");
		AddControl(new wxStaticLine(this), wxSizerFlags().Expand());
		AddText("Thanks for using the App");
		AddControl(new wxStaticLine(this), wxSizerFlags().Expand());
	}
	


};


#endif