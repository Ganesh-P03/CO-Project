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
    wxBitsStatusBar(wxWindow* parent);
    




    bool isPowerManagerOn;
    bool isClockShown;
    wxStaticBitmap* powerOnOffBitmap;
    wxBitmapButton* showOrhide;

    void showClock(bool val);

    wxDECLARE_EVENT_TABLE();
};

#endif