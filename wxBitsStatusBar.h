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
    


    private:

        enum {
            Field_text,
            Field_powBitmap,
            Field_clockbutton,
            Field_clock,
            Field_flag,
            Field_max
        };


    bool isPowerManagerOn;
    bool isClockShown;
    int widths[Field_max];

    wxStaticBitmap* powerOnOffBitmap;
    wxBitmapButton* showOrhide;
    wxStaticBitmap* IndiaRussiaFlag;

    void OnShowOrHideClick(wxCommandEvent& eve);
    void OnSize(wxSizeEvent &eve);
    void ArrangeControlsOnSizeEvemt();

    wxDECLARE_EVENT_TABLE();
};

#endif