#include "cWindow.h"
#include <wx/splitter.h>


wxBEGIN_EVENT_TABLE(cWindow, wxFrame)




wxEND_EVENT_TABLE()

cWindow::cWindow(const wxString & title, const wxPoint & pos, const wxSize & size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu;

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
   
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
  
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Thanks for choosing our stimulator !");

    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxSP_BORDER | wxSP_LIVE_UPDATE);

    wxSplitterWindow* left_splitter = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxSP_BORDER | wxSP_LIVE_UPDATE);

    wxPanel* right = new wxPanel(splitter);
    wxPanel* left = new wxPanel(left_splitter);
    wxPanel* left_bottom = new wxPanel(left_splitter);


    left->SetBackgroundColour(wxColor(200, 100, 100));
    right->SetBackgroundColour(wxColor(100, 200, 100));
    left_bottom->SetBackgroundColour(wxColor(200, 200, 100));


    left_splitter->SplitHorizontally(left, left_bottom);



    splitter->SetMinimumPaneSize(200);

    splitter->SplitVertically(left_splitter, right);

}


