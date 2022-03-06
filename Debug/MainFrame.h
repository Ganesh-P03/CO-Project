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
//#include "Simulator.h"
#endif

#include "wx/timer.h"

#include "wx/power.h"

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

#include <wx/treectrl.h>

#ifdef  wxUSE_LISTCTRL
#include <wx/listctrl.h>
#endif

#include <wx/commandlinkbutton.h>



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

	power_manager_id,
	
	Menu_Context,
	dummy

};


class wxBitsTreeCtrl :public wxTreeCtrl {
public :
	wxBitsTreeCtrl(wxWindow *parent):wxTreeCtrl(parent,-1,wxDefaultPosition,wxDefaultSize,wxTR_TWIST_BUTTONS|wxTR_HAS_BUTTONS) {
		wxTreeItemId parent1=AddRoot("This is a tree Frame");
		AppendItem(parent1,"and this need ");
		AppendItem(parent1, "to be reimplemented for 2nd phase");
		wxTreeItemId child3=AppendItem(parent1, "but for now - it is useless like me in my home");
		AppendItem(child3, "don't explore everything ");

	}
	void LoadDirInTree(wxString dir) {

	}
	void UnloadDirInTree() {
		DeleteAllItems();
	}

};



class MainNotePage :public wxPanel {

public:
	MainNotePage(wxWindow* parent, bool isStart,bool isAutoOn) :wxPanel(parent, wxID_ANY, wxDefaultPosition),isStart(isStart)
	{
		int h = GetParent()->GetClientRect().GetHeight();
		int w = GetParent()->GetClientRect().GetWidth();
		SetSize(w,h);
		this->isStart = isStart;
		this->isAutoOn = isAutoOn;

		if (!isStart)
		{
			notepad = new wxStyledTextCtrl(this, -1,wxDefaultPosition,wxSize(w,h));
			notepad->SetCaretLineBackground(*wxBLUE);
		
			Update();
			Refresh();
		}
		else{
			CreateStartPage();
		}

		if (isAutoOn)
		{
			autoComItemList = new wxString("add and addi andi beq bne blt bltu bge bgeu ble data exit globlmain jalr jal li lw or ori sll srl sub sra slti sliu slt sltu sw text word xor  xori");
			BindAuto();
		}

	}
	void CreateStartPage() {
		wxStaticText* startText = new wxStaticText(this, -1, "Start Page -Sorry for not making this start page attractive :)", wxPoint(300,300), wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
		wxCommandLinkButton* link = new wxCommandLinkButton(this, -1, "Github Link", "Link to Github Source code", wxPoint(300, 400));
		link->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &eve) {
			
			wxLaunchDefaultBrowser("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
			
			});

	
	}
	void BindAuto()
	{
		notepad->Bind(wxEVT_STC_CHANGE, [this](wxStyledTextEvent& eve) {
			wxStyledTextCtrl* stc = (wxStyledTextCtrl*)eve.GetEventObject();

			// Find the word start
			int currentPos = stc->GetCurrentPos();
			int wordStartPos = stc->WordStartPosition(currentPos, true);

			// Display the autocompletion list
			int lenEntered = currentPos - wordStartPos;
			if (lenEntered > 0)
			{
				stc->AutoCompShow(lenEntered,*autoComItemList);
			}
			});
	}
	//Need to use vector - sorted Insert

	wxStyledTextCtrl* notepad;
	bool isStart;
	bool isAutoOn;
	wxString* autoComItemList;
	
};



class wxBitsFolderTree :public wxFrame {
public:
	wxBitsFolderTree(wxWindow* parent);
	    void LoadDir(wxString dir);
		void UnLoadDir();
	wxBitsTreeCtrl* tree;
	bool isTreeLoaded;

};
enum {
	RegGrid_set_all,RegGrid_hide_dis,RegGrid_hide_abi
};

class RegisterGridPanel :public wxPanel
{
public :
	RegisterGridPanel(wxWindow *parent):wxPanel(parent,-1)
	{
		int h = GetParent()->GetClientRect().GetHeight();
		int w = GetParent()->GetClientRect().GetWidth();
		SetSize(w, h);
		regList = new wxListCtrl(this, -1,wxDefaultPosition,wxSize(w,h-150),wxLC_REPORT);
		regList->AppendColumn("Register");
		regList->AppendColumn("ABI Name");
		regList->AppendColumn("Description");
		regList->AppendColumn("Value ");
		regList->SetColumnWidth(0, 100);
		regList->SetColumnWidth(1, 100);
		regList->SetColumnWidth(2, 150);
		registerName = new wxListItem * [32];
		regVal = new wxListItem * [32];
		regABIName = new wxListItem * [32];
		regDesciption = new wxListItem * [32];
		
		//regList->EnableAlternateRowColours();

		for (int i = 0; i < 32; i++)
		{
			registerName[i] = new wxListItem();
			regVal[i] = new wxListItem();
			regABIName[i] = new wxListItem();
			regDesciption[i] = new wxListItem();

			if (i == 0)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

				regVal[i]->SetId(i);
				regVal[i]->SetText("");
				regVal[i]->SetColumn(3);

				regABIName[i]->SetId(i);
				regABIName[i]->SetText("zero");
				regABIName[i]->SetColumn(1);

				regDesciption[i]->SetId(i);
				regDesciption[i]->SetText("hardwired zero");
				regDesciption[i]->SetColumn(2);
			}
			else if (i==1)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

				regVal[i]->SetId(i);
				regVal[i]->SetText("");
				regVal[i]->SetColumn(3);

				regABIName[i]->SetId(i);
				regABIName[i]->SetText("ra");
				regABIName[i]->SetColumn(1);

				regDesciption[i]->SetId(i);
				regDesciption[i]->SetText("return address");
				regDesciption[i]->SetColumn(2);
			}
			else if (i == 2)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

				regVal[i]->SetId(i);
				regVal[i]->SetText("");
				regVal[i]->SetColumn(3);

				regABIName[i]->SetId(i);
				regABIName[i]->SetText("sp");
				regABIName[i]->SetColumn(1);

				regDesciption[i]->SetId(i);
				regDesciption[i]->SetText("stack pointer");
				regDesciption[i]->SetColumn(2);
			}
			else if (i == 3)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

				regVal[i]->SetId(i);
				regVal[i]->SetText("");
				regVal[i]->SetColumn(3);

				regABIName[i]->SetId(i);
				regABIName[i]->SetText("gp");
				regABIName[i]->SetColumn(1);

				regDesciption[i]->SetId(i);
				regDesciption[i]->SetText("global pointer");
				regDesciption[i]->SetColumn(2);
			}
			else if (i == 4)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

				regVal[i]->SetId(i);
				regVal[i]->SetText("");
				regVal[i]->SetColumn(3);

				regABIName[i]->SetId(i);
				regABIName[i]->SetText("tp");
				regABIName[i]->SetColumn(1);

				regDesciption[i]->SetId(i);
				regDesciption[i]->SetText("thread pointer");
				regDesciption[i]->SetColumn(2);
			}
			else if (i>=5&&i<=7)
			{
				registerName[i]->SetId(i);
				registerName[i]->SetText(wxString::Format("x%d", i));
				registerName[i]->SetColumn(0);

			regVal[i]->SetId(i);
			regVal[i]->SetText("");
			regVal[i]->SetColumn(3);

			regABIName[i]->SetId(i);
			regABIName[i]->SetText(wxString::Format("t%d",i-5));
			regABIName[i]->SetColumn(1);

			regDesciption[i]->SetId(i);
			regDesciption[i]->SetText(wxString::Format("temporary register %d", i - 5));
			regDesciption[i]->SetColumn(2);
			}
			else if (i == 8||i==9)
			{
			registerName[i]->SetId(i);
			registerName[i]->SetText(wxString::Format("x%d", i));
			registerName[i]->SetColumn(0);

			regVal[i]->SetId(i);
			regVal[i]->SetText("");
			regVal[i]->SetColumn(3);

			regABIName[i]->SetId(i);
			regABIName[i]->SetText(wxString::Format("s%d", i - 8));
			regABIName[i]->SetColumn(1);

			regDesciption[i]->SetId(i);
			regDesciption[i]->SetText(wxString::Format("saved register %d", i - 8));
			regDesciption[i]->SetColumn(2);
			}
			else if (i >=10&&i <=17)
			{
			registerName[i]->SetId(i);
			registerName[i]->SetText(wxString::Format("x%d", i));
			registerName[i]->SetColumn(0);

			regVal[i]->SetId(i);
			regVal[i]->SetText("");
			regVal[i]->SetColumn(3);

			regABIName[i]->SetId(i);
			regABIName[i]->SetText(wxString::Format("a%d", i - 10));
			regABIName[i]->SetColumn(1);

			regDesciption[i]->SetId(i);
			regDesciption[i]->SetText(wxString::Format("function argument %d", i - 10));
			regDesciption[i]->SetColumn(2);
			}
			else if (i>=18&& i<=27)
			{
			registerName[i]->SetId(i);
			registerName[i]->SetText(wxString::Format("x%d", i));
			registerName[i]->SetColumn(0);

			regVal[i]->SetId(i);
			regVal[i]->SetText("");
			regVal[i]->SetColumn(3);

			regABIName[i]->SetId(i);
			regABIName[i]->SetText(wxString::Format("s%d", i - 16));
			regABIName[i]->SetColumn(1);

			regDesciption[i]->SetId(i);
			regDesciption[i]->SetText(wxString::Format("saved register %d", i - 16));
			regDesciption[i]->SetColumn(2);
			}
			else
			{
			registerName[i]->SetId(i);
			registerName[i]->SetText(wxString::Format("x%d", i));
			registerName[i]->SetColumn(0);

			regVal[i]->SetId(i);
			regVal[i]->SetText("");
			regVal[i]->SetColumn(3);

			regABIName[i]->SetId(i);
			regABIName[i]->SetText(wxString::Format("t%d", i - 25));
			regABIName[i]->SetColumn(1);

			regDesciption[i]->SetId(i);
			regDesciption[i]->SetText(wxString::Format("temporary register %d", i - 25));
			regDesciption[i]->SetColumn(2);
			}

			regList->InsertItem(*registerName[i]);
			regList->SetItem(*regVal[i]);
			regList->SetItem(*regABIName[i]);
			regList->SetItem(*regDesciption[i]);

			setAll = new wxButton(this, RegGrid_set_all,"Set",wxPoint(250,h-120));
			hideDesciption = new wxButton(this, RegGrid_hide_dis, "Hide Description", wxPoint(120, h - 60));
			hideABIName = new wxButton(this,RegGrid_hide_abi, "Hide ABI", wxPoint(350, h - 60));

		}

	}
	void SetAllZero() {
		for (int i = 0; i < 32; i++)
		{
			regVal[i]->SetText("0");
			regList->SetItem(*regVal[i]);
		}
	}
	void LoadRegisterGrid();

	wxListCtrl* regList;
	wxListItem** registerName;
	wxListItem** regVal;
	wxListItem** regABIName;
	wxListItem** regDesciption;

	void OnSetAllZero(wxCommandEvent& eve);
	void OnHideDiscription(wxCommandEvent& eve);
	void OnHideABIName(wxCommandEvent& eve);

	wxButton* setAll;
	wxButton* hideDesciption;
	wxButton* hideABIName;

	wxDECLARE_EVENT_TABLE();
};

class MemoryGridPanel :public wxPanel {

};

class MainFrame :public wxFrame
{
public:

	MainFrame(wxWindow* parent);
	//void LoadFolderInTree();
	//void UnLoadFolder(); // Just remove evry child
	//void LoadFileText(wxString& fileName, int indexInNote);
	void InitFull();


	int duplicatesNum;
	int activeNotes;
	bool showAtStart;
	bool show_statBar;
	bool show_toolBar;
	bool isTreeVisible;
	bool isAllFilesSaved;
	bool isConsoleVisible;                // oNclose event , we need to get parent and update this 
	bool isTodoListFrmVisible;
	bool allowGeneric;
	bool allowAutoCompletion;
	bool doesContainDir;
	bool isStartPageVisible;
private:

	wxArrayString* autoCompArray;

	wxMenu* contextMenu;       //com
	wxMenu* clipBoardHis;
	wxMenu* toolContextMenu;   // com
	wxString* presentDir;      //com


	wxDialog* codesnpDlg; // user need to select code snippet form here
	
	wxNotebook* mainNote;
	wxNotebook* registerMainNote;
	RegisterGridPanel* registerGrid;
	
	wxBitsFolderTree* treeFrame;
	wxFrame* consoleFrame;
	wxFrame* todoListFrame;

	wxMenuBar* m_menuBar;
	wxBitsStatusBar* m_statBar;
	wxToolBar* m_toolBar;


	void InitMenuBar();//Init Menu bar + context Menu
	void InitStatBar();
	void InitToolBar();
	void InitMainNote();
	void InitRegGrid();
	void InitTreeCtrl();
	void ManagePropertiesOfNotePad();
	void ShowTip();
	void UpdateTreeFrame();

	MainNotePage* GetPageOnMainNoteIndex(int index);
	void MainNoteAddPage(MainNotePage *pg);
	MainNotePage* CreateStartPage();
	MainNotePage* CreateEmptyPage();
	void RemovePage();



	wxString OpenFileDlg(wxString& wildCards);
	void OpenDirDlg();
	int GetNumberFromUser(int present, int min, int max);



	void OnUpdateUIMenuViewTool(wxUpdateUIEvent& eve);
	void OnUpdateUIMenuViewStat(wxUpdateUIEvent& eve);


	void OnRunCode(wxCommandEvent &eve);//com
	void OnNewFile(wxCommandEvent& eve);//com
	void OnNewFolder(wxCommandEvent& eve);
	void OnOpenFile(wxCommandEvent& eve);//com
	void OnOpenFolder(wxCommandEvent& eve);
	void OnDuplicate(wxCommandEvent& eve);//com
	void OnClose(wxCommandEvent& eve);//com
	void OnCloseAll(wxCommandEvent& eve);//com
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
	void OnStartTaskClicked(wxCommandEvent& WXUNUSED(eve));
	void OnStopTaskClicked(wxCommandEvent& WXUNUSED(eve));

	void StartLongTask()
	{
		m_taskProgress = 0;
		m_taskTimer.Start(12000);
		GetMenuBar()->Enable(wxID_NEW, false);
		GetMenuBar()->Enable(wxID_ABORT, true);

		m_powerResourceBlocker
			= new wxPowerResourceBlocker(wxPOWER_RESOURCE_SYSTEM);

	}

	void StopLongTask()
	{
		GetMenuBar()->Enable(wxID_NEW, true);
		GetMenuBar()->Enable(wxID_ABORT, false);
		m_taskTimer.Stop();

		wxDELETE(m_powerResourceBlocker);
	}
	void UpdatePowerSettings(wxPowerType powerType, wxBatteryState batteryState)
	{
		wxString powerStr;
		switch (m_powerType = powerType)
		{
		case wxPOWER_SOCKET:
			powerStr = "wall";
			break;

		case wxPOWER_BATTERY:
			powerStr = "battery";
			break;

		default:
			wxFAIL_MSG("unknown wxPowerType value");
			wxFALLTHROUGH;

		case wxPOWER_UNKNOWN:
			powerStr = "psychic";
			break;
		}

		wxString batteryStr;
		switch (m_batteryState = batteryState)
		{
		case wxBATTERY_NORMAL_STATE:
			batteryStr = "charged";
			break;

		case wxBATTERY_LOW_STATE:
			batteryStr = "low";
			break;

		case wxBATTERY_CRITICAL_STATE:
			batteryStr = "critical";
			break;

		case wxBATTERY_SHUTDOWN_STATE:
			batteryStr = "empty";
			break;

		default:
			wxFAIL_MSG("unknown wxBatteryState value");
			wxFALLTHROUGH;

		case wxBATTERY_UNKNOWN_STATE:
			batteryStr = "unknown";
			break;
		}
	}

	wxLog* m_logOld;
	wxPowerType m_powerType;
	wxBatteryState m_batteryState;

	wxTimer m_taskTimer;
	wxPowerResourceBlocker* m_powerResourceBlocker;
	int m_taskProgress;

#if USE_CONTEXT_MENU
	void OnContextMenu(wxContextMenuEvent& eve);
#else
	void OnRightClick(wxMouseEvent& eve);
#endif
	void OnToolContextMenu(wxCommandEvent& eve);

#ifdef wxHAS_POWER_EVENTS
	void OnSuspending(wxPowerEvent& event)
	{
		wxLogMessage("System suspend starting...");
		if (wxMessageBox("Veto suspend?", "Please answer",
			wxYES_NO, this) == wxYES)
		{
			event.Veto();
			wxLogMessage("Vetoed suspend.");
		}
	}
	void OnTaskTimer(wxTimerEvent& WXUNUSED(event))
	{
		++m_taskProgress;

		if (m_taskProgress == 100)
		{
			StopLongTask();
			wxLogMessage("Long running task finished");
		}
		else
		{
			wxLogMessage("Long running task at %d%%...", m_taskProgress);
		}
	}

	void OnSuspended(wxPowerEvent& WXUNUSED(event))
	{
		wxLogMessage("System is going to suspend.");
	}

	void OnSuspendCancel(wxPowerEvent& WXUNUSED(event))
	{
		wxLogMessage("System suspend was cancelled.");
	}

	void OnResume(wxPowerEvent& WXUNUSED(event))
	{
		wxLogMessage("System resumed from suspend.");
	}
#endif // wxHAS_POWER_EVENTS

	DECLARE_EVENT_TABLE();

};//Main Top Level Frame




#endif