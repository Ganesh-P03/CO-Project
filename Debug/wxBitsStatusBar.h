#ifndef WX_BITS_STATBAR
#define WX_BITS_STATBAR
#include "wx/wxprec.h"


#if !wxUSE_STATUSBAR
#error "StatusBar Not Supported"
#endif // wxUSE_STATUSBAR

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/datetime.h"
#include "wx/numdlg.h"
#include "wx/fontdlg.h"





// A custom status bar which contains controls, icons &c
class wxBitsStatusBar : public wxStatusBar
{
public:
    wxBitsStatusBar(wxWindow* parent, long style=wxSB_FLAT);
    
    virtual ~wxBitsStatusBar();

    void UpdateClock();

    // event handlers
#if wxUSE_TIMER
    void OnTimer(wxTimerEvent& WXUNUSED(event)) { UpdateClock(); }
#endif
    void OnSize(wxSizeEvent& event);
    void OnToggleClock(wxCommandEvent& event);
    void OnIdle(wxIdleEvent& event);

private:
    // toggle the state of the status bar controls
    void DoToggle();

    enum
    {
        Field_Text,
        Field_Checkbox,
        Field_Bitmap,
        Field_NumLockIndicator,
        Field_Clock,
        Field_CapsLockIndicator,
        Field_Max
    };

#if wxUSE_TIMER
    wxTimer m_timer;
#endif

#if wxUSE_CHECKBOX
    wxCheckBox* m_checkbox;
#endif
    wxStaticBitmap* m_statbmp;

    wxDECLARE_EVENT_TABLE();
};

#endif