//---------------------------------------------------------------------------
//
// Name:        ffApp.cpp
// Author:      SotnikovA
// Created:     20.05.2018 18:56:54
// Description: 
//
//---------------------------------------------------------------------------

#include "ffApp.h"
#include "ffFrm.h"
#include <wx/pen.h>
#include <wx/dc.h>
#include <wx/event.h>
//#include "game.h"
#include <conio.h>

IMPLEMENT_APP(ffFrmApp)

bool ffFrmApp::OnInit()
{
    
    ffFrm* frame = new ffFrm(NULL);
    SetTopWindow(frame);

    frame->Show();
    
    
    
    wxClientDC dc(frame);
    
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetPen(*wxBLACK_PEN);
    
    dc.DrawLine(20, 10, 20 + frame->g.game::GetWidth(), 10);
    dc.DrawLine(20, 10 + frame->g.game::GetHeight() , 20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight());
    
    dc.DrawLine(20, 10, 20, 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2);
    dc.DrawLine(20, 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2, 20, 10 + frame->g.game::GetHeight());
    
    
    dc.DrawLine(20 + frame->g.game::GetWidth(), 10, 20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2);
    dc.DrawLine(20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2, 20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight());
    
    dc.SetPen(*wxRED_PEN);
    dc.DrawLine(30 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2, 30 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2);
    dc.SetPen(*wxBLUE_PEN);
    dc.DrawLine(10, 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2, 10, 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2);
    
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(10, 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2, 20, 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2);
    dc.DrawLine(10, 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2, 20, 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2);
    
    
    dc.DrawLine(20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2, 30 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 - frame->g.game::GetGate() / 2);
    
    dc.DrawLine(20 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2, 30 + frame->g.game::GetWidth(), 10 + frame->g.game::GetHeight() / 2 + frame->g.game::GetGate() / 2);
    
    for(int i = 0; i <= frame->g.game::GetWidth() / 10; i++)
        for(int j = 0; j <= frame->g.game::GetHeight() / 10; j++)
             dc.DrawCircle(20 + i * 10, 10 + j * 10, 1);
    
    dc.SetPen(*wxBLUE_PEN);
    dc.SetBrush(*wxBLUE_BRUSH);
    
    dc.DrawCircle(20 + frame->g.game::GetWidth() / 2, 10 + frame->g.game::GetHeight() / 2, 2);
    
    wxString s;
    
    s << "Blue Player      Stage:  " << 1;
    
    
    dc.DrawText(s, 100, 250);
    //dc.DrawText("Stage: ",200,250);
    
    char y[10];
    //int ch = GetKeyCode();
    
    //dc.DrawText(itoa(ch, y, 10), 20, 270);
    
    return true;
}
 
int ffFrmApp::OnExit()
{
	return 0;
}
