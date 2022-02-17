#include "cApp.h"
#include "cWindow.h"


wxIMPLEMENT_APP(cApp);



bool cApp::OnInit()
{
    cWindow* frame = new cWindow("RISC-V Stimulator", wxPoint(50, 50), wxSize(800, 600));

    frame->Show(true);
    return true;
}