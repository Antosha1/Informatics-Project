///-----------------------------------------------------------------
///
/// @file      ffFrm.cpp
/// @author    SotnikovA
/// Created:   20.05.2018 18:56:54
/// @section   DESCRIPTION
///            ffFrm class implementation
///
///------------------------------------------------------------------

#include "ffFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// ffFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(ffFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	EVT_KEY_DOWN(ffFrm::OnMovement)
	EVT_CLOSE(ffFrm::OnClose)
END_EVENT_TABLE()
////Event Table End

ffFrm::ffFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

ffFrm::~ffFrm()
{
}

void ffFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	SetTitle(_("ff"));
	SetIcon(wxNullIcon);
	SetSize(8,8,520,334);
	Center();
	
	////GUI Items Creation End
}

void ffFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void ffFrm::OnMovement(wxKeyEvent& event)
{
  wxClientDC dc(this);
  bool goal = FALSE;
  bool gate;
  
    
    //dc.SetBackground(*wxWHITE_BRUSH);
    //dc.Clear(); 
    wxChar ch = event.GetKeyCode();
    //dc.GetPen()->SetWidth(3);
    
    
  dc.SetPen(*wxWHITE_PEN);
  dc.SetBrush(*wxWHITE_BRUSH);
  dc.DrawRectangle(90, 240, 420,260);  //Before any move, erase the previous one 
  
  if(((this->g.gameover) == 0)) {
    
    bool flag = FALSE;
    int res = (this->g.game::MoveEnable(this->g.travel - this->g.move_number + 1, this->g.current_place_x, this->g.current_place_y));
    
    
   
    
    
    if(res != 0)
    {
        
        dc.SetPen(this->g.current_player == 1 ? *wxBLUE_PEN : *wxRED_PEN);
        switch (ch) {
            case WXK_DOWN:
            case WXK_NUMPAD2:
            case WXK_NUMPAD_DOWN:
                if(res & 0x40) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+20, this->g.current_place_y*10 + 20);
                    this->g.current_place_y ++;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    flag = TRUE;
                }
                break;
            case WXK_UP:
            case WXK_NUMPAD8:
            case WXK_NUMPAD_UP: 
                if(res & 0x4) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+20, this->g.current_place_y*10);
                    this->g.current_place_y --;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    flag = TRUE;
                }
                break;
            case WXK_LEFT:
            case WXK_NUMPAD4:
            case WXK_NUMPAD_LEFT:
                if(res & 0x1) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10 + 10);
                    if ((this->g.current_place_x == 0) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = FALSE;
                        break;
                    }
                    this->g.current_place_x --;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    flag = TRUE;
                }
                break;
            case WXK_RIGHT:
            case WXK_NUMPAD6:
            case WXK_NUMPAD_RIGHT:
                if(res & 0x10) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10 + 10);
                    if ((this->g.current_place_x == this->g.lw) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = TRUE;
                        break;
                    }
             
                    this->g.current_place_x ++;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    flag = TRUE;
                }
                break;
            case WXK_END:
            case WXK_NUMPAD1:
            case WXK_NUMPAD_END:
                if(res &0x80) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10 + 20);
                    if ((this->g.current_place_x == 0) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = FALSE;
                        break;
                    }
             
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x80;
                    this->g.current_place_y ++;
                    this->g.current_place_x --;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x08;
                    flag = TRUE;
                }
                break;
            case WXK_HOME:
            case WXK_NUMPAD7:
            case WXK_NUMPAD_HOME:
                if(res & 0x2) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10);
             
                    if ((this->g.current_place_x == 0) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = FALSE;
                        break;
                   }
             
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x02;
                    this->g.current_place_y --;
                    this->g.current_place_x --;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x20;
                    flag = TRUE;
                }
                break;
            case WXK_PAGEUP:
            case WXK_NUMPAD9:
            case WXK_NUMPAD_PAGEUP:
                if(res & 0x8) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10);
                    if ((this->g.current_place_x == this->g.lw) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = TRUE;
                        break;
                    }
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x08;
                    this->g.current_place_y --;
                    this->g.current_place_x ++;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x80;
                    flag = TRUE;
                }
                break;
            case WXK_PAGEDOWN:
            case WXK_NUMPAD3:
            case WXK_NUMPAD_PAGEDOWN:
                if(res & 0x20) {
                    dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10 + 20);
                    if ((this->g.current_place_x == this->g.lw) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y > (this->g.lh + this->g.lg) / 2)) {
                        goal = TRUE;
                        gate = TRUE;
                        break;
                    }
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x20;
                    this->g.current_place_y ++;
                    this->g.current_place_x ++;
                    this->g.p[this->g.current_place_y * this->g.lw + this->g.current_place_x] = 1;
                    this->g.e[this->g.current_place_y * this->g.lw + this->g.current_place_x] |= 0x02;
                    flag = TRUE;
                }
                break;
        
        }
        
    }
    else 
        if(int a = this->g.PenaltyEnable()) 
        {
            // do penalty
  
            dc.SetPen(this->g.current_player == 1 ? *wxBLUE_PEN : *wxRED_PEN);
            switch(ch) {
                case WXK_LEFT:
                case WXK_NUMPAD4:
                case WXK_NUMPAD_LEFT:
                    if(((this->g.current_place_x - this->g.kick) >= 0) && (a & 0x01)) {
                        for(int  i = 1; i <= 6; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10 + 10);
                            this->g.current_place_x --;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                        }
                    
                    }
                    if(((this->g.current_place_x - this->g.kick) < 0) && (a & 0x01) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y < (this->g.lh + this->g.lg) / 2)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, 10, this->g.current_place_y*10 + 10);
                        goal = TRUE;
                        gate = FALSE;
                        this->g.gameover = 1;
                    }
                    break;
                    
                case WXK_RIGHT:
                case WXK_NUMPAD6:
                case WXK_NUMPAD_RIGHT:
                    if(((this->g.current_place_x + this->g.kick) <= this->g.lw) && (a & 0x10)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10 + 10);
                            this->g.current_place_x ++;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                        }
                    
                    }
                    if(((this->g.current_place_x + this->g.kick) > this->g.lw) && (a & 0x10) && (this->g.current_place_y > (this->g.lh - this->g.lg) / 2) && (this->g.current_place_y < (this->g.lh + this->g.lg) / 2)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.lw*10+30, this->g.current_place_y*10 + 10);
                        goal = TRUE;
                        gate = TRUE;
                        
                    }
                    break;
                    
                case WXK_UP:
                case WXK_NUMPAD8:
                case WXK_NUMPAD_UP:
                    if(((this->g.current_place_y - this->g.kick) >= 0) && (a & 0x04)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+20, this->g.current_place_y*10);
                            this->g.current_place_y --;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                        }
                    
                    }
                    break;
                    
                case WXK_DOWN:
                case WXK_NUMPAD2:
                case WXK_NUMPAD_DOWN:
                    if(((this->g.current_place_y + this->g.kick) <= this->g.lh) && (a & 0x40)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+20, this->g.current_place_y*10+20);
                            this->g.current_place_y ++;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                        }
                    
                    }
                    break;
                case WXK_HOME:
                case WXK_NUMPAD7:
                case WXK_NUMPAD_HOME:
                    if(((this->g.current_place_x - this->g.kick) >= 0) && ((this->g.current_place_y - this->g.kick) >= 0) && (a & 0x02)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10);
                            this->g.current_place_y --;
                            this->g.current_place_x --;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                            this->g.e[this->g.current_place_y*this->g.lw + this->g.current_place_x] |= 0x20;
                            this->g.e[(this->g.current_place_y + 1)*this->g.lw + this->g.current_place_x + 1] |= 0x02;
                        }
                    }
                    if((this->g.current_place_x < this->g.kick) && ((this->g.current_place_y - this->g.current_place_x) > (this->g.lh - this->g.lg) / 2) && ((this->g.current_place_y - this->g.current_place_x) < (this->g.lh + this->g.lg) / 2) && (a & 0x02)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, 10, (this->g.current_place_y - this->g.current_place_x)*10);
                        goal = TRUE;
                        gate = FALSE;
                    }
                    break;
                case WXK_PAGEUP:
                case WXK_NUMPAD9:
                case WXK_NUMPAD_PAGEUP:
                    if(((this->g.current_place_x + this->g.kick) <= this->g.lw) && ((this->g.current_place_y - this->g.kick) >= 0) && (a & 0x08)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10);
                            this->g.current_place_y --;
                            this->g.current_place_x ++;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                            this->g.e[this->g.current_place_y*this->g.lw + this->g.current_place_x] |= 0x80;
                            this->g.e[(this->g.current_place_y + 1)*this->g.lw + this->g.current_place_x - 1] |= 0x08;
                        }
                    }
                    if(((this->g.lw - this->g.current_place_x) < this->g.kick) && ((this->g.current_place_y - this->g.lw + this->g.current_place_x) > (this->g.lh - this->g.lg) / 2) && ((this->g.current_place_y - this->g.lw + this->g.current_place_x) < (this->g.lh + this->g.lg) / 2) && (a & 0x08)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, (this->g.lw + 1)*10 + 20, (this->g.current_place_y - this->g.lw + this->g.current_place_x)*10);
                        goal = TRUE;
                        gate = TRUE;
                    }
                    break;
                case WXK_PAGEDOWN:
                case WXK_NUMPAD3:
                case WXK_NUMPAD_PAGEDOWN:
                    if(((this->g.current_place_x + this->g.kick) <= this->g.lw) && ((this->g.current_place_y + this->g.kick) <= this->g.lh) && (a & 0x20)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+30, this->g.current_place_y*10 + 20);
                            this->g.current_place_y ++;
                            this->g.current_place_x ++;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                            this->g.e[this->g.current_place_y*this->g.lw + this->g.current_place_x] |= 0x02;
                            this->g.e[(this->g.current_place_y - 1)*this->g.lw + this->g.current_place_x - 1] |= 0x20;
                        }
                    }
                    if(((this->g.lw - this->g.current_place_x) < this->g.kick) && ((this->g.current_place_y + this->g.lw - this->g.current_place_x) > (this->g.lh - this->g.lg) / 2) && ((this->g.current_place_y + this->g.lw - this->g.current_place_x) < (this->g.lh + this->g.lg) / 2) && (a & 0x20)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, (this->g.lw)*10 + 30, (this->g.current_place_y + this->g.lw - this->g.current_place_x)*10 + 20);
                        goal = TRUE;
                        gate = TRUE;
                    }
                    break;
                case WXK_END:
                case WXK_NUMPAD1:
                case WXK_NUMPAD_END:
                    if(((this->g.current_place_x - this->g.kick) >= 0) && ((this->g.current_place_y + this->g.kick) <= this->g.lh) && (a & 0x80)) {
                        for(int  i = 1; i <= this->g.kick; i++) {
                            dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, this->g.current_place_x*10+10, this->g.current_place_y*10 + 20);
                            this->g.current_place_y ++;
                            this->g.current_place_x --;
                            this->g.p[this->g.current_place_y*this->g.lw + this->g.current_place_x] = 1;
                            this->g.e[this->g.current_place_y*this->g.lw + this->g.current_place_x] |= 0x08;
                            this->g.e[(this->g.current_place_y - 1)*this->g.lw + this->g.current_place_x + 1] |= 0x80;
                        }
                    }
                    if((this->g.current_place_x < this->g.kick) && ((this->g.current_place_y + this->g.current_place_x) > (this->g.lh - this->g.lg) / 2) && ((this->g.current_place_y + this->g.current_place_x) < (this->g.lh + this->g.lg) / 2) && (a & 0x80)) {
                        dc.DrawLine(this->g.current_place_x*10+20, this->g.current_place_y*10 + 10, 10, (this->g.current_place_y + this->g.current_place_x)*10 + 20);
                        goal = TRUE;
                        gate = FALSE;
                    }
                    break;
                
            }
            this->g.current_player = this->g.current_player == 1 ? 2 : 1;
        }
        else
        {
            // draw score and we block any commands besides NewGame or Exit
            this->g.gameover = 1;
            
                          
                dc.DrawText("Draw", 100, 250);         
            
        }
    
    
    
    
    if((this->g.move_number == this->g.travel) && flag) {
            this->g.move_number = 1;
            this->g.current_player = this->g.current_player == 1 ? 2 : 1;
        }
    else
        if(flag) 
            this->g.move_number++;
    wxString s;
    
    
    if(this->g.current_player == 1) {
        s << "Blue Player      Stage:  " << this->g.move_number;   
        dc.DrawText(s, 100, 250);
    }
    else {
        s << "Red Player      Stage:  " << this->g.move_number; 
        dc.DrawText(s, 100, 250);
    }
    
    
}   
if(goal == 1) {
        this->g.gameover = 1;
        if(gate && (this->g.current_player == 1))
            dc.DrawText("Blue Player wins", 100, 250);
        if(gate && (this->g.current_player == 2))
            dc.DrawText("Blue Player wins by  autogoal", 100, 250);
        if(!gate && (this->g.current_player == 2))
            dc.DrawText("Red Player wins", 100, 250);
        if(!gate && (this->g.current_player == 1))
            dc.DrawText("Red Player wins by  autogoal", 100, 250);
    }
   
}
