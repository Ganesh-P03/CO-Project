#pragma once
/////////////////////////////////////////////////////////////////////////////
// Name:                 Oitz.cpp
// Purpose:              Project made to explain MIPS and the basics of One and Zero Operations
// Author:               Nishanth 
// Created:              01 Feb 2022
// Licence:              No license 
// Security License :
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/mstream.h>


// for all others, include the necessary headers explicitly
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif




#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "sample.xpm" 
#endif


// Define a new application type, each program should derive a class from wxApp
class App : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};


wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);


//Enums for Menu Bars , each menuitem must have enum 
enum {
    //File ID's
    wxMENU_FILE_NEW=0,
    wxMENU_FILE_OPEN,
    wxMENU_FILE_CLONE_REPOS,
    wxMENU_FILE_CLOSE,
    wxMENU_FILE_CLOSE_ALL,
    wxMENU_FILE_SAVE,
    wxMENU_FILE_SAVE_AS,

    //Edit ID's

    wxMENU_EDIT_CUT,
    wxMENU_EDIT_COPY,
    wxMENU_EDIT_PASTE,
    wxMENU_EDIT_CUT_WTC, // Cut with Copy default

    //Tool ID's

    wxMENU_TOOL_CAL,

    //Help ID's
    wxMENU_OTHERS_HELP,
    wxMENU_OTHERS_KBSH     //keyboard shortcuts 
};





//CompilerWindow
class CWindow : public wxFrame
{
public:
    CWindow(wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxASCII_STR(wxFrameNameStr)) :wxFrame(parent, id, title, pos, size, style, name)
    {
        SetIcon(wxIcon("IDI_ICON1"));
#if wxUSE_MENUS

        wxMenu* menuFile = new wxMenu;
        wxMenu* menuEdit = new wxMenu;
        wxMenu* menuTool = new wxMenu;
        wxMenu* menuHelp = new wxMenu;
        
        //Menu file Items 
        menuFile->Append(wxMENU_FILE_NEW, "&New\tCtrl+N", "Creates a New File",wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_OPEN,"&Open\tCtrl+O","Open a File (.asm, .bk , .s)", wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_CLOSE, "&Close\tCtrl+Shift+X", "Closes the Present File", wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_SAVE, "&Save\tCtrl+S", "Save Present File", wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_SAVE_AS, "&Save As\tCtrl+Shift+S", "Save as", wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_CLOSE_ALL, "&Close All", "Closes all File", wxITEM_NORMAL);
        menuFile->Append(wxMENU_FILE_CLONE_REPOS, "&Clone Respository\tCtrl+Shift+C", "Clone as Respository", wxITEM_NORMAL);
        menuFile->Append(wxID_EXIT, "&Exit\tCtrl+E", "Exit !", wxITEM_NORMAL);

        //Edit Items
        menuEdit->Append(wxMENU_EDIT_CUT,"&Cut\tCtrl+X","Cut the text -  Check the Cut with Copy Option for Correct Usage ",wxITEM_NORMAL);
        menuEdit->Append(wxMENU_EDIT_COPY, "&Copy\tCtrl+C", "Copy the text", wxITEM_NORMAL);
        menuEdit->Append(wxMENU_EDIT_PASTE, "&Paste\tCtrl+V", "Paste the text", wxITEM_NORMAL);
        menuEdit->Append(wxMENU_EDIT_CUT_WTC, "Cut with Copy Disabled", "To enable Cut with default Copy", wxITEM_RADIO);

        //Tools 
        menuTool->Append(wxMENU_TOOL_CAL, "Calculator", "Calculator used to perform calculations during assembly or bk test ",wxITEM_NORMAL);

        //Help 
        menuHelp->Append(wxID_ABOUT, "About", "About this App", wxITEM_DROPDOWN);
        menuHelp->Append(wxMENU_OTHERS_HELP, "&Help\tCtrl+H", "To provide Tips to get Started with this App",wxITEM_NORMAL);
        menuHelp->Append(wxMENU_OTHERS_KBSH, "&KeyBoard ShortCuts\tCtrl+K","Learn about the keyboard Shortcuts ", wxITEM_NORMAL);



        wxMenuBar* menuBar = new wxMenuBar();
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuEdit, "&Edit");
        menuBar->Append(menuTool, "&Tool");
        menuBar->Append(menuHelp, "&Help");
        menuBar->SetBackgroundColour(wxColour("red"));

        SetMenuBar(menuBar);
#endif



    }
   
//File 
    void OnNew(wxCommandEvent& WXUNUSED(event));
    void OnOpen(wxCommandEvent& WXUNUSED(event));
    void OnCloneRepos(wxCommandEvent& WXUNUSED(event));
    void OnSave(wxCommandEvent& WXUNUSED(event));
    void OnSaveAs(wxCommandEvent& WXUNUSED(event));
    void OnExit(wxCommandEvent& WXUNUSED(event));
    void OnClose(wxCommandEvent& WXUNUSED(event));
    void OnCloseAll(wxCommandEvent& WXUNUSED(event));


//Edit 

    void OnCut(wxCommandEvent& WXUNUSED(event));
    void OnCopy(wxCommandEvent& WXUNUSED(event));
    void OnPaste(wxCommandEvent& WXUNUSED(event));
    //void OnFile(wxCommandEvent& WXUNUSED(event)) ; TODO

//Tools

    void OnCal(wxCommandEvent& WXUNUSED(event));

//Others 

    void OnAbout(wxCommandEvent& WXUNUSED(event));
    void OnHelp(wxCommandEvent& WXUNUSED(event));
    void OnKbsh(wxCommandEvent& WXUNUSED(event));

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(CWindow, wxFrame) //Event static Linking  

//File 
EVT_MENU(wxMENU_FILE_NEW, CWindow::OnNew)
EVT_MENU(wxMENU_FILE_OPEN, CWindow::OnOpen)
EVT_MENU(wxMENU_FILE_CLONE_REPOS, CWindow::OnCloneRepos)
EVT_MENU(wxMENU_FILE_CLOSE, CWindow::OnClose)
EVT_MENU(wxMENU_FILE_CLOSE_ALL, CWindow::OnCloseAll)
EVT_MENU(wxMENU_FILE_SAVE, CWindow::OnSave)
EVT_MENU(wxMENU_FILE_SAVE_AS, CWindow::OnSaveAs)
EVT_MENU(wxID_EXIT, CWindow::OnExit)

//Edit 

EVT_MENU(wxMENU_EDIT_CUT, CWindow::OnCut)
EVT_MENU(wxMENU_EDIT_COPY, CWindow::OnCopy)
EVT_MENU(wxMENU_EDIT_PASTE, CWindow::OnPaste)

//Tools

EVT_MENU(wxMENU_TOOL_CAL, CWindow::OnCal)

//Help 

EVT_MENU(wxID_ABOUT, CWindow::OnAbout)
EVT_MENU(wxMENU_OTHERS_KBSH, CWindow::OnKbsh)
EVT_MENU(wxMENU_OTHERS_HELP, CWindow::OnHelp)

wxEND_EVENT_TABLE()    //end static Linking 




bool App::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }
    CWindow* cfrm = new CWindow(NULL, wxID_ANY, "Console ", wxPoint(300, 100), wxSize(800, 600), wxDEFAULT_FRAME_STYLE);
    cfrm->SetBackgroundColour(wxColour(255, 255, 255));
#if wxUSE_STATUSBAR
    cfrm->CreateStatusBar();
    cfrm->SetStatusText("Welcome to wxWidgets!");
   
#endif // wxUSE_STATUSBAR
    cfrm->ShowFullScreen(true, wxDEFAULT_FRAME_STYLE);
    return true;
}

void CWindow::OnNew(wxCommandEvent& event)
{
    event.Skip(true);
}

void CWindow::OnOpen(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnClose(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnCloneRepos(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnCloseAll(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnSave(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Show(false);
}

void CWindow::OnCut(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnCopy(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnPaste(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnHelp(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnAbout(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnKbsh(wxCommandEvent& WXUNUSED(event))
{

}

void CWindow::OnCal(wxCommandEvent& WXUNUSED(event))
{

}