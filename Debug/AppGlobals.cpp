#include "AppGlobals.h"

#ifdef wxUSE_STDPATHS 
#include <wx/stdpaths.h>
#endif

static const char* const wxwin_xpm[] = {
"16 16 142 2",
"  	c None",
". 	c #7171C0",
"+ 	c #7D7DC7",
"@ 	c #8181CE",
"# 	c #7979CE",
"$ 	c #7171CE",
"% 	c #6868CD",
"& 	c #5050C0",
"* 	c #7C7CCB",
"= 	c #D3D3FC",
"- 	c #C0C0FF",
"; 	c #B1B1FF",
"> 	c #A4A4FF",
", 	c #9696FF",
"' 	c #6B6BE3",
") 	c #3E3EC0",
"! 	c #7B7BD3",
"~ 	c #CFCFFF",
"{ 	c #A7A7FF",
"] 	c #8989FF",
"^ 	c #7B7BFF",
"/ 	c #5E5EEB",
"( 	c #3333BF",
"_ 	c #6969D3",
": 	c #BEBEFF",
"< 	c #8E8EFF",
"[ 	c #5E5EFF",
"} 	c #4C4CFD",
"| 	c #6464C6",
"1 	c #A4A478",
"2 	c #BFBF63",
"3 	c #BFBF5C",
"4 	c #BFBF56",
"5 	c #BFBF51",
"6 	c #C17474",
"7 	c #BF7070",
"8 	c #BF6969",
"9 	c #BF6363",
"0 	c #544AC7",
"a 	c #A8A8FF",
"b 	c #7070FF",
"c 	c #5050FF",
"d 	c #3F3FFF",
"e 	c #8C8CBA",
"f 	c #F6F6C8",
"g 	c #FBFBBB",
"h 	c #FBFBAE",
"i 	c #FBFBA1",
"j 	c #F9F993",
"k 	c #D7D760",
"l 	c #D28D8D",
"m 	c #EEB8B8",
"n 	c #EFAAAA",
"o 	c #EF9E9E",
"p 	c #7C5ABC",
"q 	c #8D8DFF",
"r 	c #4747FF",
"s 	c #3535FF",
"t 	c #2B2BFF",
"u 	c #AAAAA7",
"v 	c #FFFFD2",
"w 	c #FFFFA9",
"x 	c #FFFF9A",
"y 	c #FFFF8D",
"z 	c #FFFF80",
"A 	c #E4E45B",
"B 	c #E39F9F",
"C 	c #FFCCCC",
"D 	c #FFA9A9",
"E 	c #FF9C9C",
"F 	c #B469A0",
"G 	c #3E3DE7",
"H 	c #2828EF",
"I 	c #1E1EEF",
"J 	c #1515EF",
"K 	c #A5A595",
"L 	c #FFFFC2",
"M 	c #FFFF8F",
"N 	c #F7F765",
"O 	c #F2F251",
"P 	c #DBDB3A",
"Q 	c #E48E8E",
"R 	c #FFBABA",
"S 	c #FF8E8E",
"T 	c #FF8181",
"U 	c #FF6868",
"V 	c #E54D60",
"W 	c #AC2E56",
"X 	c #0B0BBF",
"Y 	c #0606BF",
"Z 	c #C8C85D",
"` 	c #FEFEB1",
" .	c #FEFE74",
"..	c #F4F456",
"+.	c #EFEF42",
"@.	c #EFEF38",
"#.	c #D7D725",
"$.	c #E47676",
"%.	c #FFA8A8",
"&.	c #FF7373",
"*.	c #FF5555",
"=.	c #FF4343",
"-.	c #FF3939",
";.	c #DA2323",
">.	c #CFCF3C",
",.	c #F6F694",
"'.	c #F0F047",
").	c #EFEF2E",
"!.	c #EFEF24",
"~.	c #D7D715",
"{.	c #E45757",
"].	c #FF8888",
"^.	c #FF4646",
"/.	c #FF2F2F",
"(.	c #FF2525",
"_.	c #DA1414",
":.	c #C3C328",
"<.	c #EBEB55",
"[.	c #ECEC2F",
"}.	c #ECEC24",
"|.	c #ECEC1A",
"1.	c #EBEB10",
"2.	c #CDCD06",
"3.	c #DD3A3A",
"4.	c #FF6060",
"5.	c #FF1B1B",
"6.	c #FE1111",
"7.	c #D10707",
"8.	c #B8B819",
"9.	c #B7B715",
"0.	c #B7B710",
"a.	c #B7B70B",
"b.	c #B7B706",
"c.	c #B7B701",
"d.	c #B7B700",
"e.	c #BF1A1A",
"f.	c #CC1919",
"g.	c #CE1414",
"h.	c #CE0E0E",
"i.	c #CE0808",
"j.	c #C90202",
"k.	c #C00000",
"                                ",
"                                ",
"        . + @ # $ % &           ",
"        * = - ; > , ' )         ",
"        ! ~ { , ] ^ / (         ",
"        _ : < ^ [ } | 1 2 3 4 5 ",
"6 7 8 9 0 a b c d e f g h i j k ",
"l m n o p q r s t u v w x y z A ",
"B C D E F G H I J K L M z N O P ",
"Q R S T U V W X Y Z `  ...+.@.#.",
"$.%.&.*.=.-.;.    >.,.'.@.).!.~.",
"{.].^.-./.(._.    :.<.[.}.|.1.2.",
"3.4./.(.5.6.7.    8.9.0.a.b.c.d.",
"e.f.g.h.i.j.k.                  ",
"                                ",
"                                " };


AppGlobals::AppGlobals()
{
	AppName = "wxBits";
	VendorName = ::wxGetUserName();
	Description = "wxBits is just time pass app written for fun -No use of it - Just unistall it ";
	AppWebsiteLink = wxURL("https://www.google.co.in/");
	DevelopersName.Add("Sleepy Baby");
	CopyRight = "Copyright free";
	Version = "0.1- Initial Release";
	AppIcon = wxIcon(wxwin_xpm);
	IconBitmap = wxBitmap(wxwin_xpm);
	AppPath = wxStandardPaths::Get().GetExecutablePath();
	AppDocWriter.Add("Ganesh");
	AppCoreCompilerDesign.Add("Ganesh");
}

wxString AppGlobals::GetVendorName()
{
	return VendorName;
}

void AppGlobals::SetVendorName(wxString name)
{
	VendorName = name;
}

wxString  AppGlobals::GetAppName(){
	return AppName;
}
wxString  AppGlobals::GetDescription(){
	return Description;
}
wxString  AppGlobals::GetAppWebsiteLink(){
	return AppWebsiteLink.GetPath();
}
wxArrayString  AppGlobals::GetDevelopersName(){
	return DevelopersName;
}
wxString  AppGlobals::GetCopyright(){
	return CopyRight;
}
wxString  AppGlobals::GetVersion(){
	return Version;
}
wxIcon  AppGlobals::GetAppicon(){
	return AppIcon;
}
wxBitmap  AppGlobals::GetAppIconBitmap(){
	return IconBitmap;
}
wxArrayString  AppGlobals::GetAppDocWriter(){
	return AppDocWriter;
}
wxArrayString  AppGlobals::GetAppCoreCompilerDesign(){
	return AppCoreCompilerDesign;
}
