#pragma once

#include <wx/string.h>
#include <wx/url.h>
#include <wx/icon.h>
#include <wx/bitmap.h>


class AppGlobals
{
private :
     wxString AppName;
	 wxString VendorName;
	 wxString Description;
	//static wxString LongDescription;
	 wxURL AppWebsiteLink;
	 wxArrayString DevelopersName;
	 wxString CopyRight;
	 wxString Version;
	 wxIcon AppIcon;
	 wxBitmap IconBitmap;
	 wxString AppPath;
	 wxArrayString AppDocWriter;
	 wxArrayString AppCoreCompilerDesign;

	

public :
	 AppGlobals();
	 wxString GetVendorName();
     void SetVendorName(wxString name);
	 wxString GetAppName();
	 wxString GetDescription();
	 wxString GetAppWebsiteLink();
	 wxArrayString GetDevelopersName();
	 wxString GetCopyright();
	 wxString GetVersion();
	 wxIcon GetAppicon();
	 wxBitmap GetAppIconBitmap();
	 wxArrayString GetAppDocWriter();
	 wxArrayString GetAppCoreCompilerDesign();

};

