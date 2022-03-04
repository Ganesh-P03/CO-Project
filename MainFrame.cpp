#include "MainFrame.h"

#ifdef wxUSE_ARTPROVIDER_STD
#include <wx/artprov.h>
#endif // wxUSE_ART_PROVIDER 

#if wxUSE_STARTUP_TIPS
#include "wx/tipdlg.h"
#endif // wxUSE_STARTUP_TIPS

#if wxUSE_COLOURDLG
#include "wx/colordlg.h"
#endif // wxUSE_COLOURDLG

#if wxUSE_FILEDLG
#include "wx/filedlg.h"
#endif // wxUSE_FILEDLG

#if wxUSE_DIRDLG
#include "wx/dirdlg.h"
#endif // wxUSE_DIRDLG

#if wxUSE_FONTDLG
#include "wx/fontdlg.h"
#endif // wxUSE_FONTDLG

#if wxUSE_FINDREPLDLG
#include "wx/fdrepdlg.h"
#endif // wxUSE_FINDREPLDLG

#if USE_COLOURDLG_GENERIC
#include "wx/generic/colrdlgg.h"
#endif // USE_COLOURDLG_GENERIC

#if USE_DIRDLG_GENERIC
#include "wx/generic/dirdlgg.h"
#endif // USE_DIRDLG_GENERIC

#if USE_FILEDLG_GENERIC
#include "wx/generic/filedlgg.h"
#endif // USE_FILEDLG_GENERIC

#if USE_FONTDLG_GENERIC
#include "wx/generic/fontdlgg.h"
#endif // USE_FONTDLG_GENERIC

#define MENU_FILE 0
#define MENU_EDIT 1
#define MENU_VIEW 2
#define MENU_HELP 3


BEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_MENU(Menu_file_new_file, MainFrame::OnNewFile)
EVT_MENU(Menu_file_new_folder, MainFrame::OnNewFolder)
EVT_MENU(Menu_file_close, MainFrame::OnClose)
EVT_MENU(Menu_file_close_all, MainFrame::OnCloseAll)
EVT_MENU(Menu_file_duplicate, MainFrame::OnDuplicate)
EVT_MENU(Menu_file_export, MainFrame::OnExport)
EVT_MENU(Menu_file_open_folder, MainFrame::OnOpenFolder)
EVT_MENU(Menu_file_print, MainFrame::OnPrint)
EVT_MENU(Menu_file_properties, MainFrame::OnProperties)
EVT_MENU(Menu_file_quit, MainFrame::OnQuit)
EVT_MENU(Menu_file_recent_files, MainFrame::OnRecentFiles)
EVT_MENU(Menu_file_save, MainFrame::OnSave)
EVT_MENU(Menu_file_save_all, MainFrame::OnSaveAll)
EVT_MENU(Menu_file_save_as, MainFrame::OnSaveAs)
EVT_MENU(Menu_file_unload_folder, MainFrame::OnUnloadFolder)

EVT_MENU(Menu_edit_add_codesnp, MainFrame::OnAddCodeSnp)
EVT_MENU(Menu_edit_autocomp_radio1, MainFrame::OnAutoCompRadio1)
EVT_MENU(Menu_edit_autocomp_radio2, MainFrame::OnAutoCompRadio2)
EVT_MENU(Menu_edit_autocomp_radio3, MainFrame::OnAutoCompRadio3)
EVT_MENU(Menu_edit_box_comment, MainFrame::OnBoxComment)
EVT_MENU(Menu_edit_comment, MainFrame::OnComment)
EVT_MENU(Menu_edit_copy, MainFrame::OnCopy)
EVT_MENU(Menu_edit_cut, MainFrame::OnCut)
EVT_MENU(Menu_edit_run_code, MainFrame::OnRunCode)
EVT_MENU(Menu_edit_delete, MainFrame::OnDelete)
EVT_MENU(Menu_edit_find, MainFrame::OnFind)
EVT_MENU(Menu_edit_format_document, MainFrame::OnFormatDocument)
EVT_MENU(Menu_edit_goto_file, MainFrame::OnGotoFile)
EVT_MENU(Menu_edit_goto_line, MainFrame::OnGotoLine)
EVT_MENU(Menu_edit_Ins_file_astxt, MainFrame::OnInsFileAsText)
EVT_MENU(Menu_edit_paste, MainFrame::OnPaste)
EVT_MENU(Menu_edit_props, MainFrame::OnProperties)
EVT_MENU(Menu_edit_redo, MainFrame::OnRedo)
EVT_MENU(Menu_edit_replace, MainFrame::OnReplace)
EVT_MENU(Menu_edit_select_all, MainFrame::OnSelectAll)
EVT_MENU(Menu_edit_show_clpBoardHis, MainFrame::OnShowClipBrdHis)
EVT_MENU(Menu_edit_toggle_comment, MainFrame::OnToggleComment)
EVT_MENU(Menu_edit_uncomment, MainFrame::OnUnComment)
EVT_MENU(Menu_edit_undo, MainFrame::OnUndo)

EVT_MENU(Menu_view_console, MainFrame::OnConsole)
EVT_MENU(Menu_view_fullscreen, MainFrame::OnFullScreen)
EVT_MENU(Menu_view_iconize, MainFrame::OnIconize)
EVT_MENU(Menu_view_logs, MainFrame::OnLogs)
EVT_MENU(Menu_view_minimize, MainFrame::OnMinimize)
EVT_MENU(Menu_view_statbar, MainFrame::OnStatBar)
EVT_MENU(Menu_view_todolist, MainFrame::OnTodoList)
EVT_MENU(Menu_view_toolbar, MainFrame::OnToolBar)

EVT_MENU(Menu_help_getting_started, MainFrame::OnGettingStarted)
EVT_MENU(Menu_help_kbdsrtc, MainFrame::OnKbdSrtc)
EVT_MENU(Menu_help_more_help, MainFrame::OnMoreHelp)
EVT_MENU(Menu_help_tips_tricks, MainFrame::OnTipsTricks)
EVT_MENU(Menu_help_view_help, MainFrame::OnViewHelp)

EVT_UPDATE_UI(Menu_view_toolbar, MainFrame::OnUpdateUIMenuViewTool)
EVT_UPDATE_UI(Menu_view_statbar, MainFrame::OnUpdateUIMenuViewStat)


#if USE_CONTEXT_MENU
EVT_CONTEXT_MENU(MainFrame::OnContextMenu)
#else
EVT_RIGHT_DOWN(MainFrame::OnRightClick)
#endif

END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent) :wxFrame(parent, -1, "wxBits", wxDefaultPosition, wxSize(800, 800), wxDEFAULT_FRAME_STYLE)
{
	InitFull();
	SetBackgroundColour(*wxWHITE);



}



void MainFrame::InitFull() {
	isConsoleVisible = true;
	isAllFilesSaved = true;


	InitMenuBar();
	//InitToolBar();
	InitStatBar();
	//InitMainNote();
	//InitRegGrid();
}

void MainFrame::InitMenuBar()
{
	wxMenu* file = new wxMenu;
	wxMenu* edit = new wxMenu;
	wxMenu* view = new wxMenu;
	wxMenu* help = new wxMenu;
	
	
	//file main menu items inserted 
	wxMenuItem* mi_file_close = new wxMenuItem(file, Menu_file_close, "Close", "Close the Present active file", wxITEM_NORMAL);
	wxMenuItem* mi_file_close_all = new wxMenuItem(file, Menu_file_close_all, "Close All", "Close All  active files in the screen (without saving)", wxITEM_NORMAL);
	wxMenuItem* mi_file_duplicate = new wxMenuItem(file, Menu_file_duplicate, "Duplicate", "Duplicates present active file", wxITEM_NORMAL);
	wxMenuItem* mi_file_export = new wxMenuItem(file, Menu_file_export, "Export", "Export the code", wxITEM_NORMAL);
	wxMenuItem* mi_file_new = new wxMenuItem(file, -1, "New", "New File / Folder ", wxItemKind::wxITEM_DROPDOWN);
	wxMenuItem* mi_file_open = new wxMenuItem(file,-1, "Open", "Open File / Folder ", wxITEM_DROPDOWN);
	wxMenuItem* mi_file_print = new wxMenuItem(file, Menu_file_print, "Print", "Print Present active file", wxITEM_NORMAL);
	wxMenuItem* mi_file_properties = new wxMenuItem(file, Menu_file_properties, "Properties", "Set Properties ", wxITEM_NORMAL);
	wxMenuItem* mi_file_quit = new wxMenuItem(file, Menu_file_quit, "Quit", "Quit the App", wxITEM_NORMAL);
	wxMenuItem* mi_file_recent_files = new wxMenuItem(file, Menu_file_recent_files, "Recent ", "Recently Opened files ", wxITEM_DROPDOWN);
	wxMenuItem* mi_file_save = new wxMenuItem(file, Menu_file_save, "Save", "Save the present active file", wxITEM_NORMAL);
	wxMenuItem* mi_file_save_all = new wxMenuItem(file, Menu_file_save_all, "Save All", "Save all active files", wxITEM_NORMAL);
	wxMenuItem* mi_file_save_as = new wxMenuItem(file, Menu_file_save_as, "Save As", "Change the Name of present active file ", wxITEM_NORMAL);
	wxMenuItem* mi_file_unload_folder = new wxMenuItem(file, Menu_file_unload_folder, "Unload Folder", "Clears the Tree and unloads the folder ", wxITEM_NORMAL);

	//sub menus used by file 
	wxMenu* newsub = new wxMenu;
	wxMenuItem* mi_file_new_file = new wxMenuItem(newsub,Menu_file_new_file, "File", "New File  ", wxITEM_NORMAL);
	wxMenuItem* mi_file_new_folder = new wxMenuItem(newsub, Menu_file_new_folder, "Folder", "New Folder ", wxITEM_NORMAL);

	newsub->Append(mi_file_new_file);
	newsub->Append(mi_file_new_folder);


	wxMenu* opensub = new wxMenu;
	wxMenuItem* mi_file_open_file = new wxMenuItem(opensub, Menu_file_new_file, "File", "Open File  ", wxITEM_NORMAL);
	wxMenuItem* mi_file_open_folder = new wxMenuItem(opensub, Menu_file_new_folder, "Folder", "Open Folder ", wxITEM_NORMAL);

	opensub->Append(mi_file_open_file);
	opensub->Append(mi_file_open_folder);

	//insert submenus 
	mi_file_new->SetSubMenu(newsub);
	mi_file_open->SetSubMenu(opensub);


	// Append all file menu items 
	file->Append(mi_file_new);
	file->Append(mi_file_open);
	file->Append(mi_file_duplicate);
	file->AppendSeparator();
	file->Append(mi_file_close);
	file->Append(mi_file_close_all);
	file->Append(mi_file_unload_folder);
	file->AppendSeparator();
	file->Append(mi_file_save);
	file->Append(mi_file_save_all);
	file->Append(mi_file_save_as);
	file->AppendSeparator();
	file->Append(mi_file_print);
	file->Append(mi_file_properties);
	file->Append(mi_file_export);
	file->AppendSeparator();
	file->Append(mi_file_recent_files);
	file->AppendSeparator();
	file->Append(mi_file_quit);

	//edit Menu main items 

	wxMenuItem* mi_edit_add_codesnp = new wxMenuItem(edit, Menu_edit_add_codesnp, "Add Code Snippet", "Code Snippet Dialog is shown ",wxITEM_NORMAL);
	wxMenuItem* mi_edit_autocomp_radio1 = new wxMenuItem(edit, Menu_edit_autocomp_radio1, "No AutoCompletion", "AutoCompletion is disabled",wxITEM_RADIO);
	wxMenuItem* mi_edit_autocomp_radio2 = new wxMenuItem(edit, Menu_edit_autocomp_radio2, "Only AutoCompletion", "AutoCompletion is enabled", wxITEM_RADIO);
	wxMenuItem* mi_edit_autocomp_radio3 = new wxMenuItem(edit, Menu_edit_autocomp_radio3, "AutoCompletion with help", "AutoCompletion is enabled with helps", wxITEM_RADIO);
	wxMenuItem* mi_edit_box_comment = new wxMenuItem(edit, Menu_edit_box_comment, "Box Comment", "Box Comment is inserted / Do apply changes in properties",wxITEM_NORMAL);
	wxMenuItem* mi_edit_comment = new wxMenuItem(edit, Menu_edit_comment, "Comment", "Comment the line",wxITEM_NORMAL);
	wxMenuItem* mi_edit_copy = new wxMenuItem(edit, Menu_edit_copy, "Copy", "Copy the selected text to clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_cut = new wxMenuItem(edit, Menu_edit_cut, "Cut", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_delete = new wxMenuItem(edit, Menu_edit_delete, "Delete", "Remove selected text ",wxITEM_NORMAL);
	wxMenuItem* mi_edit_find = new wxMenuItem(edit, Menu_edit_find, "Find", "Find Dialog ",wxITEM_NORMAL);
	wxMenuItem* mi_edit_format_document = new wxMenuItem(edit, Menu_edit_format_document, "Format Document", "Clears the document",wxITEM_NORMAL);
	wxMenuItem* mi_edit_goto = new wxMenuItem(edit, -1, "Goto", "Goto File / Folder", wxITEM_DROPDOWN);
	wxMenuItem* mi_edit_ins_file_astxtx = new wxMenuItem(edit, Menu_edit_Ins_file_astxt, "Insert file as text", "Select file in which the text you need exists",wxITEM_NORMAL);
	wxMenuItem* mi_edit_paste = new wxMenuItem(edit, Menu_edit_paste, "Paste", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_props = new wxMenuItem(edit, Menu_edit_props, "Properties", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_redo = new wxMenuItem(edit, Menu_edit_redo, "Redo", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_replace = new wxMenuItem(edit, Menu_edit_replace, "Replace", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_run_code = new wxMenuItem(edit, Menu_edit_run_code, "Run Code", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_select_all = new wxMenuItem(edit, Menu_edit_select_all, "Select All", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_show_clpBoardsHis = new wxMenuItem(edit, Menu_edit_show_clpBoardHis, "ClipBoard History", "Remove selected text and copy in clipboard",wxITEM_NORMAL);
	wxMenuItem* mi_edit_toggle_comment = new wxMenuItem(edit, Menu_edit_toggle_comment, "Toggle Comment", "Remove selected text and copy in clipboard", wxITEM_NORMAL);
	wxMenuItem* mi_edit_uncomment = new wxMenuItem(edit, Menu_edit_uncomment, "UnComment", "Remove selected text and copy in clipboard", wxITEM_NORMAL);
	wxMenuItem* mi_edit_undo = new wxMenuItem(edit, Menu_edit_undo, "Undo", "Remove selected text and copy in clipboard", wxITEM_NORMAL);
	

	wxMenuItem* mi_edit_goto_file = new wxMenuItem(edit, Menu_edit_goto_file, "Goto File", "Remove selected text and copy in clipboard", wxITEM_NORMAL);
	wxMenuItem* mi_edit_goto_line = new wxMenuItem(edit, Menu_edit_goto_line, "Goto Line", "Remove selected text and copy in clipboard", wxITEM_NORMAL);


	wxMenu* subgoto = new wxMenu;
	subgoto->Append(mi_edit_goto_file);
	subgoto->Append(mi_edit_goto_line);

	mi_edit_goto->SetSubMenu(subgoto);

	edit->Append(mi_edit_undo);
	edit->Append(mi_edit_redo);
	edit->AppendSeparator();
	edit->Append(mi_edit_cut);
	edit->Append(mi_edit_copy);
	edit->Append(mi_edit_paste);
	edit->Append(mi_edit_delete);
	edit->Append(mi_edit_format_document);
	edit->AppendSeparator();
	edit->Append(mi_edit_find);
	edit->Append(mi_edit_goto);
	edit->Append(mi_edit_replace);
	edit->Append(mi_edit_select_all);
	edit->AppendSeparator();
	edit->Append(mi_edit_comment);
	edit->Append(mi_edit_uncomment);
	edit->Append(mi_edit_toggle_comment);
	edit->Append(mi_edit_box_comment);
	edit->AppendSeparator();
	//edit->Break();
	edit->Append(mi_edit_autocomp_radio1);
	edit->Append(mi_edit_autocomp_radio2);
	edit->Append(mi_edit_autocomp_radio3);
	edit->AppendSeparator();
	edit->Append(mi_edit_ins_file_astxtx);
	edit->Append(mi_edit_add_codesnp);
	edit->Append(mi_edit_show_clpBoardsHis);
	edit->AppendSeparator();
	edit->Append(mi_edit_props);


	//View Main items
	wxMenuItem* mi_view_console = new wxMenuItem(view, Menu_view_console, "Console", "Interface used to communicate with flow of the program");
	wxMenuItem* mi_view_fullScreen = new wxMenuItem(view, Menu_view_fullscreen, "Full Screen", "Show FullScreen");
	wxMenuItem* mi_view_iconize = new wxMenuItem(view, Menu_view_iconize, "Iconize", "Iconize the App");
	wxMenuItem* mi_view_logs = new wxMenuItem(view, Menu_view_logs, "Logs", "Logs the App");
	wxMenuItem* mi_view_minimize = new wxMenuItem(view, Menu_view_minimize, "Minimize", "Shrink and fit the Program ");
	wxMenuItem* mi_view_statBar = new wxMenuItem(view, Menu_view_statbar, "StatusBar", "Toggle this to decide status of StatusBar",wxITEM_CHECK);
	wxMenuItem* mi_view_todoList = new wxMenuItem(view, Menu_view_todolist, "TodoList", "Shows All Todo Lists included in the program");
	wxMenuItem* mi_view_toolBar = new wxMenuItem(view, Menu_view_toolbar, "ToolBar", "Toggle this to decide status of ToolBar", wxITEM_CHECK);

   
	view->Append(mi_view_console);
	view->Append(mi_view_todoList);
	view->Append(mi_view_logs);
	view->AppendSeparator();
	view->Append(mi_view_fullScreen);
	view->Append(mi_view_minimize);
	view->Append(mi_view_iconize);
	view->AppendSeparator();
	view->Append(mi_view_statBar);
	view->Append(mi_view_toolBar);


	//Help menu Items
	wxMenuItem* mi_help_getting_started = new wxMenuItem(help, Menu_help_getting_started, "Getting Started");
	wxMenuItem* mi_help_tips_tricks = new wxMenuItem(help, Menu_help_tips_tricks, "Tips and Tricks");
	wxMenuItem* mi_help_view_help = new wxMenuItem(help, Menu_help_view_help, "View Help");
	wxMenuItem* mi_help_kbdsrtc = new wxMenuItem(help, Menu_help_kbdsrtc, "KeyBoard Shortcuts");
	wxMenuItem* mi_help_more_help = new wxMenuItem(help, Menu_help_more_help, "More Help...");
	wxMenuItem* mi_help_about = new wxMenuItem(help, Menu_help_about, "More Help...");

	help->Append(mi_help_getting_started);
	help->Append(mi_help_tips_tricks);
	help->AppendSeparator();
	help->Append(mi_help_view_help);
	help->Append(mi_help_more_help);
	help->AppendSeparator();
	help->Append(mi_help_kbdsrtc);
	help->Append(mi_help_about);



	m_menuBar = new wxMenuBar();
	m_menuBar->Append(file, "File");
	m_menuBar->Append(edit, "Edit");
	m_menuBar->Append(view, "View");
	m_menuBar->Append(help, "Help");

	//Add bitmaps
	mi_file_close->SetBitmap(wxArtProvider::GetBitmap(wxART_CLOSE, wxS("wxART_MENU")));
	mi_edit_copy->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxS("wxART_MENU")));
	mi_edit_cut->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxS("wxART_MENU")));
	mi_edit_delete->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxS("wxART_MENU")));
	mi_file_open_file->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxS("wxART_MENU")));
	mi_file_save->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxS("wxART_MENU")));
	mi_file_save_as->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxS("wxART_MENU")));
	mi_edit_find->SetBitmap(wxArtProvider::GetBitmap(wxART_FIND, wxS("wxART_MENU")));
	mi_edit_replace->SetBitmap(wxArtProvider::GetBitmap(wxART_FIND_AND_REPLACE, wxS("wxART_MENU")));
	//mi_file_new_folder->SetBitmap(wxArtProvider::GetBitmap(wxART_FOLDER, wxS("wxART_MENU")));
	mi_file_open_folder->SetBitmap(wxArtProvider::GetBitmap(wxART_FOLDER_OPEN, wxS("wxART_MENU")));
	mi_view_fullScreen->SetBitmap(wxArtProvider::GetBitmap(wxART_FULL_SCREEN, wxS("wxART_MENU")));
	mi_edit_goto_line->SetBitmap(wxArtProvider::GetBitmap(wxART_GOTO_FIRST, wxS("wxART_MENU")));
	mi_help_view_help->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP, wxS("wxART_MENU")));
	mi_help_more_help->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP_PAGE, wxS("wxART_MENU")));
	mi_help_about->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP_SETTINGS, wxS("wxART_MENU")));
	mi_file_new->SetBitmap(wxArtProvider::GetBitmap(wxART_NEW, wxS("wxART_MENU")));
	mi_file_new_folder->SetBitmap(wxArtProvider::GetBitmap(wxART_NEW_DIR, wxS("wxART_MENU")));
	mi_file_new_file->SetBitmap(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxS("wxART_MENU")));
	mi_edit_paste->SetBitmap(wxArtProvider::GetBitmap(wxART_PASTE, wxS("wxART_MENU")));
	mi_file_print->SetBitmap(wxArtProvider::GetBitmap(wxART_PRINT, wxS("wxART_MENU")));
	mi_file_quit->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxS("wxART_MENU")));
	mi_edit_undo->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxS("wxART_MENU")));
	mi_edit_redo->SetBitmap(wxArtProvider::GetBitmap(wxART_REDO, wxS("wxART_MENU")));
	mi_help_tips_tricks->SetBitmap(wxArtProvider::GetBitmap(wxART_TIP, wxS("wxART_MENU")));


	mi_view_statBar->SetBitmaps(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxS("wxART_MENU")), wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxS("wxART_MENU")));
	mi_view_toolBar->SetBitmaps(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxS("wxART_MENU")), wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxS("wxART_MENU")));
	

	SetMenuBar(m_menuBar);

	contextMenu = new wxMenu;
	contextMenu->Append(-1, "Not Yet decided what to add");


}
void MainFrame::InitStatBar(){

	m_statBar = new wxBitsStatusBar(this);
	SetStatusBar(m_statBar);

}
void MainFrame::InitToolBar(){}
void MainFrame::InitMainNote(){}
void MainFrame::InitRegGrid(){}
void MainFrame::InitTreeCtrl(){}

bool MainFrame::IsNativeExistsBgColourChoose(){
	return wxUSE_COLOURDLG;
}
bool MainFrame::IsNativeExistsFgColourChoose(){
	return wxUSE_COLOURDLG;
}
bool MainFrame::IsNativeExistsFileChoose(){

}
bool MainFrame::IsNativeExistsDirChoose() {
}


void MainFrame::AddPage(){}
wxPanel* MainFrame::CreateStartPage() { return nullptr; }
wxPanel* MainFrame::CreateEmptyPage(){ return nullptr; }
void MainFrame::RemovePage(){}


void MainFrame::OnRunCode(wxCommandEvent& eve){}
void MainFrame::OnNewFile(wxCommandEvent& eve){}
void MainFrame::OnNewFolder(wxCommandEvent& eve){}
void MainFrame::OnOpenFile(wxCommandEvent& eve){}
void MainFrame::OnOpenFolder(wxCommandEvent& eve){}
void MainFrame::OnDuplicate(wxCommandEvent& eve){}
void MainFrame::OnClose(wxCommandEvent& eve){}
void MainFrame::OnCloseAll(wxCommandEvent& eve){}
void MainFrame::OnUnloadFolder(wxCommandEvent& eve){}
void MainFrame::OnSave(wxCommandEvent& eve){}
void MainFrame::OnSaveAs(wxCommandEvent& eve){}
void MainFrame::OnSaveAll(wxCommandEvent& eve){}
void MainFrame::OnExport(wxCommandEvent& eve){}
void MainFrame::OnProperties(wxCommandEvent& eve){}
void MainFrame::OnPrint(wxCommandEvent& eve){}
void MainFrame::OnRecentFiles(wxCommandEvent& eve){}
void MainFrame::OnQuit(wxCommandEvent& eve){}

void MainFrame::OnUndo(wxCommandEvent& eve){}
void MainFrame::OnRedo(wxCommandEvent& eve){}
void MainFrame::OnCut(wxCommandEvent& eve){}
void MainFrame::OnCopy(wxCommandEvent& eve){}
void MainFrame::OnPaste(wxCommandEvent& eve){}
void MainFrame::OnDelete(wxCommandEvent& eve){}
void MainFrame::OnFind(wxCommandEvent& eve){}
void MainFrame::OnReplace(wxCommandEvent& eve){}
void MainFrame::OnSelectAll(wxCommandEvent& eve){}
void MainFrame::OnGotoLine(wxCommandEvent& eve){}
void MainFrame::OnGotoFile(wxCommandEvent& eve){}
void MainFrame::OnInsFileAsText(wxCommandEvent& eve){}
void MainFrame::OnAddCodeSnp(wxCommandEvent& eve){}
void MainFrame::OnComment(wxCommandEvent& eve){}
void MainFrame::OnUnComment(wxCommandEvent& eve){}
void MainFrame::OnToggleComment(wxCommandEvent& eve){}
void MainFrame::OnFormatDocument(wxCommandEvent& eve){}
void MainFrame::OnBoxComment(wxCommandEvent& eve){}
void MainFrame::OnAutoCompRadio1(wxCommandEvent& eve){}
void MainFrame::OnAutoCompRadio2(wxCommandEvent& eve){}
void MainFrame::OnAutoCompRadio3(wxCommandEvent& eve){}
void MainFrame::OnShowClipBrdHis(wxCommandEvent& eve){}
void MainFrame::OnEditProps(wxCommandEvent& eve){}

void MainFrame::OnLogs(wxCommandEvent& eve){}
void MainFrame::OnToolBar(wxCommandEvent& eve){

	

}
void MainFrame::OnStatBar(wxCommandEvent& eve){



}
void MainFrame::OnConsole(wxCommandEvent& WXUNUSED(eve)){
	if (!isConsoleVisible)
	{
		consoleFrame->Show();
	}
}
void MainFrame::OnTodoList(wxCommandEvent& WXUNUSED(eve)){
	if (!isTodoListFrmVisible)
	{
		todoListFrame->Show();
	}
}
void MainFrame::OnFullScreen(wxCommandEvent& eve){
	EnableFullScreenView();
}
void MainFrame::OnMinimize(wxCommandEvent& eve){
    
}
void MainFrame::OnIconize(wxCommandEvent& eve){
	Iconize();
}

void MainFrame::OnViewHelp(wxCommandEvent& eve){}
void MainFrame::OnMoreHelp(wxCommandEvent& eve){}
void MainFrame::OnGettingStarted(wxCommandEvent& eve){}
void MainFrame::OnTipsTricks(wxCommandEvent& WXUNUSED(eve)){
	ShowTip();
}
void MainFrame::OnKbdSrtc(wxCommandEvent& eve){}
void MainFrame::OnAbout(wxCommandEvent &eve){}

void MainFrame::OnCloseEvent(wxCloseEvent& eve){



}

#ifdef USE_CONTEXT_MENU
void MainFrame::OnContextMenu(wxContextMenuEvent& eve){

	if (eve.GetPosition() != wxDefaultPosition)
	{
		PopupMenu(contextMenu, eve.GetPosition());
	}
	else
	PopupMenu(contextMenu, wxGetMousePosition());
}
#else
void MainFrame::OnRightClick(wxMouseEvent& eve){

	PopupMenu(contextMenu,eve.GetPosition());

}
#endif

void MainFrame::OnUpdateUIMenuViewStat(wxUpdateUIEvent & WXUNUSED(eve))
{
	show_statBar=m_menuBar->GetMenu(MENU_VIEW)->IsChecked(Menu_view_statbar);
}

void MainFrame::OnUpdateUIMenuViewTool(wxUpdateUIEvent& WXUNUSED(eve))
{
	show_toolBar = m_menuBar->GetMenu(2)->IsChecked(Menu_view_toolbar);
}

#if wxUSE_STARTUP_TIPS
void MainFrame::ShowTip()
{
	static size_t s_index = (size_t)-1;

	if (s_index == (size_t)-1)
	{
		srand(time(NULL));
		s_index = rand() % 5;
	}

	wxTipProvider* tipProvider = wxCreateFileTipProvider("tips.txt", s_index);
  


    showAtStart = wxShowTip(this, tipProvider);

	if (showAtStart)
	{
		wxMessageBox("Will Show tips on Start", "Tips Dialog",wxOK | wxICON_INFORMATION, this);
	}

	s_index = tipProvider->GetCurrentTip();
	delete tipProvider;
}
#endif // wxUSE_STARTUP_TIPS