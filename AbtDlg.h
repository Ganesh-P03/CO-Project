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


wxAboutDialogInfo* wxBitsabtinfo;



class wBAboutDialog :public  wxGenericAboutDialog {

public :
	wBAboutDialog() :wxGenericAboutDialog()
	{
		wxBitsabtinfo = new wxAboutDialogInfo();
		
	
		

	}


};


#endif