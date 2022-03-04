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



	m_frame = new MainFrame(nullptr);  // m_frame top level win
	m_frame->Show();
	return true;

}//OnInit()