#ifndef WXBITS_MAIN_H
#define WXBITS_MAIN_H

#include <wx/wxprec.h>

#include <wx/stc/stc.h>


#ifdef __BORLANDC__
#pragma hdrstop
#endif


#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/sashwin.h>
#include <wx/toplevel.h>
#include "wxBitsStatusBar.h"
#endif

#if defined(__WXMSW__) && wxUSE_TASKBARICON
#include "wx/taskbar.h"
#endif // wxUSE_TASKBARICON


#if !defined(wxUSE_MENUS)|!defined(wxUSE_MENUBAR)
 #error "Menu is not supported !"
#endif // wxUSE_MENUS

// Not all ports have support ContextMenu 
#if defined(__WXMOTIF__) || defined(__WXX11__)
#define USE_CONTEXT_MENU 0
#else
#define USE_CONTEXT_MENU 1
#endif // wxUSE_CONTEXT_MENU

#ifdef __WXUNIVERSAL__
#define USE_WXUNIVERSAL 1
#else
#define USE_WXUNIVERSAL 0
#endif

#ifdef WXUSINGDLL
#define USE_DLL 1
#else
#define USE_DLL 0
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

#define USE_GENERIC_DIALOGS (!USE_WXUNIVERSAL && !USE_DLL)

#define USE_COLOURDLG_GENERIC \
    ((USE_WXMSW || USE_WXMAC) && USE_GENERIC_DIALOGS && wxUSE_COLOURDLG)
#define USE_DIRDLG_GENERIC \
    ((USE_WXMSW || USE_WXMAC) && USE_GENERIC_DIALOGS && wxUSE_DIRDLG)
#define USE_FILEDLG_GENERIC \
    ((USE_WXMSW || USE_WXMAC) && USE_GENERIC_DIALOGS  && wxUSE_FILEDLG)
#define USE_FONTDLG_GENERIC \
    ((USE_WXMSW || USE_WXMACFONTDLG) && USE_GENERIC_DIALOGS && wxUSE_FONTDLG)



//Window id's Used in complete App
enum Menu_id{

	//Menu_file
	Menu_file_new_file=wxID_HIGHEST,
	Menu_file_new_folder,
	Menu_file_open_file,
	Menu_file_open_folder,
	Menu_file_duplicate,
	Menu_file_close,
	Menu_file_close_all,
	Menu_file_unload_folder,
	Menu_file_save,
	Menu_file_save_as,
	Menu_file_save_all,
	Menu_file_export,
	Menu_file_properties,
	Menu_file_print,
	Menu_file_recent_files,
	Menu_file_quit,


	//Menu_edit
	Menu_edit_undo,
	Menu_edit_redo,
	Menu_edit_run_code,
	Menu_edit_cut,
	Menu_edit_copy,
	Menu_edit_paste,
	Menu_edit_delete,
	Menu_edit_find,
	Menu_edit_replace,
	Menu_edit_select_all,
	Menu_edit_goto_line,
	Menu_edit_goto_file,
	Menu_edit_Ins_file_astxt,
	Menu_edit_add_codesnp,
	Menu_edit_comment,
	Menu_edit_uncomment,
	Menu_edit_toggle_comment,
	Menu_edit_format_document,
	Menu_edit_box_comment,
	Menu_edit_autocomp_radio1,
	Menu_edit_autocomp_radio2,
	Menu_edit_autocomp_radio3,
	Menu_edit_show_clpBoardHis,
	Menu_edit_props,

	//Menu view
	Menu_view_logs,
	Menu_view_toolbar,
	Menu_view_statbar,
	Menu_view_console,
	Menu_view_todolist,
	Menu_view_fullscreen,
	Menu_view_minimize,
	Menu_view_iconize,

	//Menu Help
	Menu_help_view_help,//context sensitive help
	Menu_help_more_help,
	Menu_help_getting_started,
	Menu_help_tips_tricks,
	Menu_help_kbdsrtc,
	Menu_help_about,

	Menu_recent_file1,
	Menu_recent_file2,
	Menu_recent_file3,

	Menu_Context,
	dummy

};


class MainFrame :public wxFrame
{
public:

	MainFrame(wxWindow* parent);
	//void LoadFolderInTree();
	//void UnLoadFolder(); // Just remove evry child
	//void LoadFileText(wxString& fileName, int indexInNote);
	void InitFull();

private :

	int activeNotes;
	bool showAtStart;
	bool show_statBar;
	bool show_toolBar;
	bool isTreeVisible;
	bool isAllFilesSaved;
	bool isConsoleVisible;                // oNclose event , we need to get parent and update this 
	bool isTodoListFrmVisible;
	bool allowGeneric;



	wxMenu* contextMenu;
	wxMenu* clipBoardHis;



	wxDialog* codesnpDlg; // user need to select code snippet form here
	
	wxPanel* startPage;
	
	wxNotebook* mainNote;
	wxNotebook* registerNote;
	wxPanel* regGrid;
	wxFrame* treeFrmae;
	wxFrame* consoleFrame;
	wxFrame* todoListFrame;

	wxMenuBar* m_menuBar;
	wxBitsStatusBar* m_statBar;
	wxToolBar* m_toolBar;

	bool IsNativeExistsBgColourChoose();
	bool IsNativeExistsFgColourChoose();
	bool IsNativeExistsFileChoose();
	bool IsNativeExistsDirChoose();

	void InitMenuBar();//Init Menu bar + context Menu
	void InitStatBar();
	void InitToolBar();
	void InitMainNote();
	void InitRegGrid();
	void InitTreeCtrl();
	void ShowTip();


	void AddPage();
	wxPanel* CreateStartPage();
	wxPanel* CreateEmptyPage();
	void RemovePage();



	wxString OpenFileDlg(wxString& wildCards);
	wxString OpenDirDlg();
	



	void OnUpdateUIMenuViewTool(wxUpdateUIEvent& eve);
	void OnUpdateUIMenuViewStat(wxUpdateUIEvent& eve);


	void OnRunCode(wxCommandEvent &eve);
	void OnNewFile(wxCommandEvent& eve);
	void OnNewFolder(wxCommandEvent& eve);
	void OnOpenFile(wxCommandEvent& eve);
	void OnOpenFolder(wxCommandEvent& eve);
	void OnDuplicate(wxCommandEvent& eve);
	void OnClose(wxCommandEvent& eve);
	void OnCloseAll(wxCommandEvent& eve);
	void OnUnloadFolder(wxCommandEvent& eve);
	void OnSave(wxCommandEvent& eve);
	void OnSaveAs(wxCommandEvent& eve);
	void OnSaveAll(wxCommandEvent &eve);
	void OnExport(wxCommandEvent& eve);
	void OnProperties(wxCommandEvent& eve);
	void OnPrint(wxCommandEvent& eve);
	void OnRecentFiles(wxCommandEvent& eve);
	void OnQuit(wxCommandEvent& eve);


	void OnUndo(wxCommandEvent& eve);
	void OnRedo(wxCommandEvent& eve);
	void OnCut(wxCommandEvent& eve);
	void OnCopy(wxCommandEvent& eve);
	void OnPaste(wxCommandEvent& eve);
	void OnDelete(wxCommandEvent& eve);
	void OnFind(wxCommandEvent& eve);
	void OnReplace(wxCommandEvent& eve);
	void OnSelectAll(wxCommandEvent& eve);
	void OnGotoLine(wxCommandEvent& eve);
	void OnGotoFile(wxCommandEvent& eve);	
	void OnInsFileAsText(wxCommandEvent& eve);
	void OnAddCodeSnp(wxCommandEvent& eve);
	void OnComment(wxCommandEvent& eve);
	void OnUnComment(wxCommandEvent& eve);
	void OnToggleComment(wxCommandEvent& eve);
	void OnFormatDocument(wxCommandEvent& eve);
	void OnBoxComment(wxCommandEvent& eve);
	void OnAutoCompRadio1(wxCommandEvent& eve);
	void OnAutoCompRadio2(wxCommandEvent& eve);
	void OnAutoCompRadio3(wxCommandEvent& eve);
	void OnShowClipBrdHis(wxCommandEvent& eve);
	void OnEditProps(wxCommandEvent& eve);


	void OnLogs(wxCommandEvent& eve);
	void OnToolBar(wxCommandEvent& eve);
	void OnStatBar(wxCommandEvent& eve);
	void OnConsole(wxCommandEvent& eve);
	void OnTodoList(wxCommandEvent& eve);
	void OnFullScreen(wxCommandEvent& eve);
	void OnMinimize(wxCommandEvent& eve);
	void OnIconize(wxCommandEvent& eve);

	void OnViewHelp(wxCommandEvent& eve);
	void OnMoreHelp(wxCommandEvent& eve);
	void OnGettingStarted(wxCommandEvent& eve);
	void OnTipsTricks(wxCommandEvent& eve); //for now  - show tips                                                        ---------------------REMEMBER
	void OnKbdSrtc(wxCommandEvent& eve);
	void OnAbout(wxCommandEvent& eve);
	
	void OnCloseEvent(wxCloseEvent& eve);

#if USE_CONTEXT_MENU
	void OnContextMenu(wxContextMenuEvent& eve);
#else
	void OnRightClick(wxMouseEvent& eve);
#endif

	DECLARE_EVENT_TABLE();

};//Main Top Level Frame




#endif