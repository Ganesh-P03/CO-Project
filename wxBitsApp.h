/////////////////////////////////////////////////////////////////////////////
// Name:        wxBits.h
// Purpose:     wxBitsApp header
// Author:      Nishanth
// Created:     01/03/2022
// Copyright:   (c)None Copyright
// Licence:     None License
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// For compilers that support precompilation, includes "wx/wx.h".

#ifndef WXBITS_APP_H
#define WXBITS_APP_H

#include <wx/wxprec.h>


#ifdef __BORLANDC__
#pragma hdrstop
#endif


#ifndef WX_PRECOMP
#include "MainFrame.h"
#endif  //wxPRECOMP 

#ifdef wxUSE_SPLASH
#include <wx/splash.h>
#endif  // wxUSE_SPLASH

#ifdef wxUSE_PROPGRID
#include <wx/propgrid/props.h>
#include <wx/propgrid/advprops.h>
#endif  //wxUSE_PROPGRID


#ifndef wxUSE_GUI
#error Oops! Your System doesn't support wxBits
#endif


#if defined(__WXMSW__)
#define USE_WXMSW 1
#else
#define USE_WXMSW 0
#endif

#ifdef __WXMAC__
#define USE_WXMAC 1
#else
#define USE_WXMAC 0
#endif

#if USE_NATIVE_FONT_DIALOG_FOR_MACOSX
#define USE_WXMACFONTDLG 1
#else
#define USE_WXMACFONTDLG 0
#endif

#ifdef __WXGTK__
#define USE_WXGTK 1
#else
#define USE_WXGTK 0
#endif


/* \mainpage  wxBits GUI
*
* Just Time Pass Project Given By Raghava Sir ( CO tutor )
*
*/

class wxBitsApp :public wxApp {

public:
	virtual bool OnInit();
	//virtual int OnExit();
	wxString GetAppPath();
	void LoadConfig();
	void SaveConfig();
	void LoadImages();  
	void showSplash();

protected:
	void FindBrainFk();


private:
	MainFrame* m_frame;
	wxBitmap* splashScrren;
	wxBitmap* m_logo;

};

wxDECLARE_APP(wxBitsApp);  //DECLARE App


#endif   //wxBitsApp
