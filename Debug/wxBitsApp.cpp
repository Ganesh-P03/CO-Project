#include "wxBitsApp.h"


wxIMPLEMENT_APP(wxBitsApp);

//OnInit - Called when initialized at first in wxEventBaseLoop
bool wxBitsApp::OnInit()
{

	if (!wxApp::OnInit())
	{
		return false;
	}//OnInit failure of wxApp

	SetVendorName("StartUp Configs");
	SetAppName("wxBits");

	SetVendorDisplayName("Configs");

	

    wxImage::AddHandler(new wxPNGHandler);

    // create the main application window
 

    wxBitmap bitmap;

    bool m_isPda= m_isPda = (wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA);

    if (m_isPda)
        bitmap = wxBitmap(mobile_xpm);

    bool ok = m_isPda
        ? bitmap.IsOk()
        : bitmap.LoadFile("wxBitsSplash (1).png", wxBITMAP_TYPE_PNG);

    if (ok)
    {
        // we can even draw dynamic artwork onto our splashscreen
        DecorateSplashScreen(bitmap);

        // show the splashscreen
        new wxSplashScreen(bitmap,
            wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
            4000, m_frame, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxSIMPLE_BORDER | wxSTAY_ON_TOP);
    }

    wxSleep(4);

#if !defined(__WXGTK20__)
    // we don't need it at least on wxGTK with GTK+ 2.12.9
    wxYield();
#endif
    m_frame = new MainFrame(nullptr);  // m_frame top level win
	m_frame->Show(true);
	return true;

}//OnInit()

void wxBitsApp::DecorateSplashScreen(wxBitmap& bmp)
{
    // use a memory DC to draw directly onto the bitmap
    wxMemoryDC memDc(bmp);

    // draw an orange box (with black outline) at the bottom of the splashscreen.
    // this box will be 10% of the height of the bitmap, and be at the bottom.
    const wxRect bannerRect(wxPoint(0, (bmp.GetHeight() / 10) * 9),
        wxPoint(bmp.GetWidth(), bmp.GetHeight()));
    wxDCBrushChanger bc(memDc, wxBrush(wxColour(255, 102, 0)));
    memDc.DrawRectangle(bannerRect);
    memDc.DrawLine(bannerRect.GetTopLeft(), bannerRect.GetTopRight());

    // dynamically get the wxWidgets version to display
    wxString description ="wxBits 0.1 Initial Release";
    // create a copyright notice that uses the year that this file was compiled
    wxString year("2022");
    wxString copyrightLabel = "No Copyright";

    // draw the (white) labels inside of our orange box (at the bottom of the splashscreen)
    memDc.SetTextForeground(*wxWHITE);
    // draw the "wxWidget" label on the left side, vertically centered.
    // note that we deflate the banner rect a little bit horizontally
    // so that the text has some padding to its left.
    memDc.DrawLabel(description, bannerRect.Deflate(5, 0), wxALIGN_CENTRE_VERTICAL | wxALIGN_LEFT);

    // draw the copyright label on the right side
    memDc.SetFont(wxFontInfo(8));
    memDc.DrawLabel(copyrightLabel, bannerRect.Deflate(5, 0), wxALIGN_CENTRE_VERTICAL | wxALIGN_RIGHT);
}