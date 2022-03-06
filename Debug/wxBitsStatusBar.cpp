#include "wxBitsStatusBar.h"

#include "icons/green.xpm"
#include "icons/red.xpm"

#ifdef wxUSE_ARTPROVIDER_STD
#include<wx/artprov.h>
#endif //wxUSE_ART_PROVIDER 

static const int BITMAP_SIZE_X = 32;

#ifdef __VISUALC__
#pragma warning(disable: 4355)
#endif

enum {
    StatusBar_Checkbox
};

wxBEGIN_EVENT_TABLE(wxBitsStatusBar, wxStatusBar)
EVT_SIZE(wxBitsStatusBar::OnSize)
#if wxUSE_CHECKBOX
EVT_CHECKBOX(StatusBar_Checkbox, wxBitsStatusBar::OnToggleClock)
#endif
#if wxUSE_TIMER
EVT_TIMER(wxID_ANY, wxBitsStatusBar::OnTimer)
#endif
EVT_IDLE(wxBitsStatusBar::OnIdle)
wxEND_EVENT_TABLE()

static const char* numlockIndicators[] = { "OFF", "NUM" };
static const char* capslockIndicators[] = { "", "CAPS" };

wxBitsStatusBar::wxBitsStatusBar(wxWindow* parent, long style)
    : wxStatusBar(parent, wxID_ANY, style, "wxBitsStatusBar")
#if wxUSE_TIMER
    , m_timer(this)
#endif
#if wxUSE_CHECKBOX
    , m_checkbox(NULL)
#endif
{
    // compute the size needed for num lock indicator pane
    wxClientDC dc(this);
    wxSize sizeNumLock = dc.GetTextExtent(numlockIndicators[0]);
    sizeNumLock.IncTo(dc.GetTextExtent(numlockIndicators[1]));

    int widths[Field_Max];
    widths[Field_Text] = -1; // growable
    widths[Field_Checkbox] = 150;
    widths[Field_Bitmap] = BITMAP_SIZE_X;
    widths[Field_NumLockIndicator] = sizeNumLock.x;
    widths[Field_Clock] = 100;
    widths[Field_CapsLockIndicator] = dc.GetTextExtent(capslockIndicators[1]).x;

    SetFieldsCount(Field_Max);
    SetStatusWidths(Field_Max, widths);

#if wxUSE_CHECKBOX
    m_checkbox = new wxCheckBox(this, StatusBar_Checkbox, "&Toggle clock");
    m_checkbox->SetValue(true);
#endif

    m_statbmp = new wxStaticBitmap(this, wxID_ANY, wxIcon(green_xpm));

#if wxUSE_TIMER
    m_timer.Start(1000);
#endif

    SetMinHeight(wxMax(m_statbmp->GetBestSize().GetHeight(),
        m_checkbox->GetBestSize().GetHeight()));

    UpdateClock();
}

#ifdef __VISUALC__
#pragma warning(default: 4355)
#endif

wxBitsStatusBar::~wxBitsStatusBar()
{
#if wxUSE_TIMER
    if (m_timer.IsRunning())
    {
        m_timer.Stop();
    }
#endif
}

void wxBitsStatusBar::OnSize(wxSizeEvent& event)
{
#if wxUSE_CHECKBOX
    if (!m_checkbox)
        return;
#endif

    wxRect rect;
    if (!GetFieldRect(Field_Checkbox, rect))
    {
        event.Skip();
        return;
    }

#if wxUSE_CHECKBOX
    wxRect rectCheck = rect;
    rectCheck.Deflate(2);
    m_checkbox->SetSize(rectCheck);
#endif

    GetFieldRect(Field_Bitmap, rect);
    wxSize size = m_statbmp->GetSize();

    m_statbmp->Move(rect.x + (rect.width - size.x) / 2,
        rect.y + (rect.height - size.y) / 2);

    event.Skip();
}

void wxBitsStatusBar::OnToggleClock(wxCommandEvent& WXUNUSED(event))
{
    DoToggle();
}

void wxBitsStatusBar::OnIdle(wxIdleEvent& event)
{
    SetStatusText(numlockIndicators[wxGetKeyState(WXK_NUMLOCK)],
        Field_NumLockIndicator);
    SetStatusText(capslockIndicators[wxGetKeyState(WXK_CAPITAL)],
        Field_CapsLockIndicator);

    event.Skip();
}

void wxBitsStatusBar::DoToggle()
{
#if wxUSE_CHECKBOX
    if (m_checkbox->GetValue())
    {
#if wxUSE_TIMER
        m_timer.Start(1000);
#endif

        m_statbmp->SetIcon(wxIcon(green_xpm));

        UpdateClock();
    }
    else // don't show clock
    {
#if wxUSE_TIMER
        m_timer.Stop();
#endif

        m_statbmp->SetIcon(wxIcon(red_xpm));

        SetStatusText(wxEmptyString, Field_Clock);
    }
#endif // wxUSE_CHECKBOX
}

void wxBitsStatusBar::UpdateClock()
{
    SetStatusText(wxDateTime::Now().FormatTime(), Field_Clock);
}
