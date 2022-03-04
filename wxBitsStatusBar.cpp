#include "wxBitsStatusBar.h"

#include "icons/green.xpm"
#include "icons/red.xpm"

#ifdef wxUSE_ARTPROVIDER_STD
#include<wx/artprov.h>
#endif //wxUSE_ART_PROVIDER 


#ifdef __VISUALC__
#pragma warning(default: 4355)
#endif

wxBitsStatusBar::wxBitsStatusBar(wxWindow* parent):wxStatusBar(parent)
{
	isPowerManagerOn = false;
	isClockShown = true;

	const int widths[] = { -1,50,50,80 };
	SetFieldsCount(4,widths);

	showOrhide = new wxBitmapButton(this, -1, wxArtProvider::GetBitmap(wxART_TICK_MARK, wxS("wxART_BUTTON")),wxPoint());



}


