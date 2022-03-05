#include "wxBitsStatusBar.h"

#include "icons/green.xpm"
#include "icons/red.xpm"

#ifdef wxUSE_ARTPROVIDER_STD
#include<wx/artprov.h>
#endif //wxUSE_ART_PROVIDER 

enum {
	STATICBITMAP_BUTTON
};


#ifdef __VISUALC__
#pragma warning(default: 4355)
#endif

wxBitmap* bmp1 = new wxBitmap(red_xpm);
wxBitmap* bmp2 = new wxBitmap(green_xpm);
wxBitmap* bmp3 = new wxBitmap(red_xpm);



BEGIN_EVENT_TABLE(wxBitsStatusBar,wxStatusBar)
EVT_BUTTON(STATICBITMAP_BUTTON,wxBitsStatusBar::OnShowOrHideClick)
EVT_SIZE(wxBitsStatusBar::OnSize)
END_EVENT_TABLE()

wxBitsStatusBar::wxBitsStatusBar(wxWindow* parent):wxStatusBar(parent)
{
	isPowerManagerOn = false;
	isClockShown = true;

	int x = GetParent()->GetRect().GetWidth();


	widths[Field_text] = -1;
	widths[Field_powBitmap] = bmp1->GetWidth() ;
	widths[Field_clockbutton] = bmp2->GetWidth();
	widths[Field_clock] = 100;
	widths[Field_flag] = bmp3->GetWidth();

	SetFieldsCount(Field_max);
	SetStatusWidths(Field_max, widths);

	powerOnOffBitmap = new wxStaticBitmap(this, -1, *bmp1);
	showOrhide = new wxBitmapButton(this,STATICBITMAP_BUTTON, wxArtProvider::GetBitmap(wxART_TICK_MARK, wxS("wxART_BUTTON_C")));
	IndiaRussiaFlag = new wxStaticBitmap(this, -1, *bmp3);


}

void wxBitsStatusBar::OnShowOrHideClick(wxCommandEvent& eve)
{
	wxMessageBox("Nice working !");
}

void wxBitsStatusBar::OnSize(wxSizeEvent &eve)
{
	ArrangeControlsOnSizeEvemt();
}

void wxBitsStatusBar::ArrangeControlsOnSizeEvemt()
{
	int tot = GetParent()->GetRect().GetWidth();

	int temp = widths[Field_clock] + widths[Field_clockbutton] + widths[Field_flag] + widths[Field_powBitmap];
	int powoffset = tot - temp;
	int butffset = powoffset+ widths[Field_powBitmap];
	int flagoffset = butffset + widths[Field_clock]+widths[Field_clockbutton];


	powerOnOffBitmap->SetPosition(wxPoint(powoffset, -1));
    showOrhide->SetPosition(wxPoint(butffset, -1));
	IndiaRussiaFlag->SetPosition(wxPoint(flagoffset, -1));


}

