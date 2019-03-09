#include "game.h"

game::game()
{
    height = 200;
    width = 400;
    gate = 40;
    travel = 3;
    kick = 6;
    lw = width / 10;
    lh = height / 10;
    lg = gate / 10;
    current_player = 1;
    move_number = 1;
    p = new int [(lw + 1) * (lh + 1)];
    e = new int [(lw + 1) * (lh + 1)];
    for (int i = 0; i < lw * lh; i++) 
        p[i] = e[i] = 0;
    current_place_x = lw / 2;
    current_place_y = lh / 2;
    p[current_place_y * lw + current_place_x] = 1;
    
    gameover = 0;
}

game::game(int h, int w, int g, int t = 3, int k = 6)
{
    height = h;
    width = w;
    gate = g;
    travel = t;
    kick = k;
    lw = width / 10;
    lh = height /10;
    lg = gate / 10;
    current_player = 1;
    p = new int [(lw + 1) * (lh + 1)];
    e = new int [(lw + 1) * (lh + 1)];
    for (int i = 0; i < lw * lh; i++) 
        p[i] = e[i] = 0;
    current_place_x = lw / 2;
    current_place_y = lh / 2;
    p[current_place_y * lw + current_place_x] = 1;
    
    gameover = 0;
    
}

game::~game()
{
    
    delete [] p;
    delete [] e;
}

int game::GetWidth()
{
    return width;
}

int game::GetHeight()
{
    return height;
}

int game::GetGate()
{
    return gate;
}


int game::MoveEnable(int i, int x, int y) 
{
    int res = 0x0;
    if(i == 1) {
        // left move
        if(x > 0) {
            if(this->p[y * this->lw + x - 1] == 0) 
                res |= 0x01;
        }
        else {
            if((y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
                res |= 0x01;
        }
        
        // left up move
        
        if((x > 0) && (y > 0) && !(this->e[(y - 1) * this->lw + x ] & 0x80)) {
            if(this->p[(y - 1) * this->lw + x - 1] == 0)
                res |= 0x02;
                
        }
        if((x == 0) && (y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
            res |= 0x02;
        
        // up move
        if(y > 0) {
            if(this->p[(y - 1) * this->lw + x] == 0)
                res |= 0x04;
        }
        
        // right up move
        if((x < this->lw) && (y > 0) && !(this->e[(y - 1) * this->lw + x ] & 0x20)) {
            if(this->p[(y - 1) * this->lw + x + 1] == 0)
                res |= 0x08;
        }
        if((x == this->lw) && (y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
            res |= 0x08;
        // right move
        if(x < this->lw) {
            if(this->p[y * this->lw + x + 1] == 0) 
                res |= 0x10;
        }
        else {
            if((y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
                res |= 0x10;
        }
        
        // right down move
        if((x < this->lw) && (y < this->lh) && !(this->e[(y + 1) * this->lw + x ] & 0x80)) {
            if(this->p[(y + 1) * this->lw +x + 1] == 0)
                res |= 0x20;
        }
        if((x == this->lw) && (y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
            res |= 0x20;
        // down move
        if(y < this->lh) {
            if(this->p[(y + 1) * this->lw + x] == 0)
                res |= 0x40;
        }
        // left down move
        if((x > 0) && (y < this->lh) && !(this->e[(y + 1) * this->lw + x ] & 0x02)) {
            if(this->p[(y + 1) * this->lw + x - 1] == 0)
                res |= 0x80;
        }
        if((x == 0) && (y > (this->lh / 2 - this->lg / 2)) && (y < (this->lh / 2 + this->lg )))
            res |= 0x80;
    }
    else {
        // left move
        if((x == 0) && (y > (this->lh - this->lg) / 2) && (y < (this->lh + this->lg) / 2))
            res |= 0x1;
        else
            if(((x - 1) >= 0) && (this->p[y * this->lw + x - 1] == 0)) {
                this->p[y * this->lw + x - 1] = 1;
                res |= game::MoveEnable(i - 1, x - 1, y) == 0 ? 0x0 : 0x1;
                this->p[y * this->lw +x - 1] = 0;
            }
        // left up move
        if((x == 0) && (y > (this->lh - this->lg) / 2) && (y < (this->lh + this->lg) / 2))
            res |= 0x2;
        else
            if((x > 0) && (y > 0) && (this->p[(y - 1) * this->lw + x - 1] == 0) && !(this->e[(y - 1) * this->lw + x ] & 0x80)) {
                this->p[(y - 1) * this->lw + x - 1] = 1;
                res |= game::MoveEnable(i - 1, x - 1, y - 1) == 0 ? 0x0 : 0x2;
                this->p[(y - 1) * this->lw + x - 1] = 0;
            }
        // up move
        if(((y - 1) >= 0) && (this->p[(y - 1) * this->lw + x] == 0)) {
            this->p[(y - 1) * this->lw + x] = 1;
            res |= game::MoveEnable(i - 1, x, y - 1) == 0 ? 0x0 : 0x4;
            this->p[(y - 1) * this->lw + x] = 0;
        }
        // right up move
        if((x == this->lw) && (y > (this->lh - this->lg) / 2) && (y < (this->lh + this->lg) / 2))
            res |= 0x8;
        else
        
            if((x < this->lw) && (y > 0) && (this->p[(y - 1) * this->lw + x + 1] == 0) && !(this->e[(y - 1) * this->lw + x ] & 0x20)) {
                this->p[(y - 1) * this->lw + x + 1] = 1;
                res |= game::MoveEnable(i - 1, x + 1, y - 1) == 0 ? 0x0 : 0x8;
                this->p[(y - 1) * this->lw + x + 1] = 0;
            }
        // right move
        if((x == this->lw) && (y > (this->lh - this->gate) / 2) && (y < (this->lh + this->gate) / 2))
            res |= 0x10;
        else
            if(((x + 1) <= this->lw) && (this->p[y * this->lw + x + 1] == 0)) {
                this->p[y * this->lw + x + 1] = 1;    
                res |= game::MoveEnable(i - 1, x + 1, y) == 0 ? 0x0 : 0x10;
                this->p[y * this->lw + x + 1] = 0;
            }
        
        // right down move
        if((x == this->lw) && (y > (this->lh - this->gate) / 2) && (y < (this->lh + this->gate) / 2))
            res |= 0x20;
        else
        
            if((x < this->lw) && (y < this->lh) && (this->p[(y + 1) * this->lw + x + 1] == 0) && !(this->e[(y + 1) * this->lw + x ] & 0x08)) {
                this->p[(y + 1) * this->lw + x + 1] = 1;
                res |= game::MoveEnable(i - 1, x + 1, y + 1) == 0 ? 0x0 : 0x20;
                this->p[(y + 1) * this->lw + x + 1] = 0;
            }
        // down move
        if(((y + 1) <= this->lh) && (this->p[(y + 1) * this->lw + x] == 0)) {
            this->p[(y + 1) * this->lw + x] = 1;
            res |= game::MoveEnable(i - 1, x, y + 1) == 0 ? 0x0 : 0x40;
            this->p[(y + 1) * this->lw + x] = 0;
        }
        // left sown move
        if((x == 0) && (y > (this->lh - this->gate) / 2) && (y < (this->lh + this->gate) / 2))
            res |= 0x80;
        else
            if((x > 0) && (y < this->lh) && (this->p[(y + 1) * this->lw + x - 1] == 0) && !(this->e[(y + 1) * this->lw + x ] & 0x02)) {
                this->p[(y + 1) * this->lw + x - 1] = 1;
                res |= game::MoveEnable(i - 1, x - 1, y + 1) == 0 ? 0x0 : 0x80;
                this->p[(y + 1) * this->lw + x - 1] = 0;
            }
    }
    return res; // This is mask of direction
}
// return mask of penalties directions
int game::PenaltyEnable()
{
    int res = 0;
    int x = this->current_place_x;
    int y = this->current_place_y;
    // left penalty
    if(((x - this->kick) >= 0) && (this->p[y * this->lw + x - this->kick] == 0))
        res |= 0x01;
    if (((x - this->kick) < 0) && (y > (this->lh - this->gate) / 2) && (y < (this->lh + this->gate) / 2))
        res |= 0x01;
        
    // right penalty
    if(((x + this->kick) <= this->lw) && (this->p[y * this->lw + x + this->kick] == 0))
        res |= 0x10;
    if (((x + this->kick) > this->lw) && (y > (this->lh - this->gate) / 2) && (y < (this->lh + this->gate) / 2))
        res |= 0x10;
        
    // up penalty
    if(((y - this->kick) >= 0) && (this->p[(y - this->kick) * this->lw + x] == 0))
        res |= 0x04;
        
    // down penalty
    
    if(((y + this->kick) <= this->lh) && (this->p[(y + this->kick) * this->lw + x] == 0))
        res |= 0x40;
        
    // left up penalty
    
    if(((y - this->kick) >= 0) && ((x - this->kick) >= 0) && (this->p[(y - this->kick) * this->lw + x - this->kick] == 0))
        res |= 0x02;
    if((x < this->kick) && ((y - x) > (this->lh - this->gate) / 2) && ((y - x) < (this->lh + this->gate) / 2))   
        res |= 0x02; 
    // right up penalty
    
    if(((y - this->kick) >= 0) && ((x + this->kick) <= this->lw) && (this->p[(y - this->kick) * this->lw + x + this->kick] == 0))
        res |= 0x08;
    if(((this->lw - x) < this->kick) && ((y - this->lw + x) > (this->lh - this->gate) / 2) && ((y - this->lw + x) < (this->lh + this->gate) / 2))   
        res |= 0x08; 
        
    // right down penalty
    
    if(((y + this->kick) <= this->lh) && ((x + this->kick) <= this->lw) && (this->p[(y + this->kick) * this->lw + x + this->kick] == 0))
        res |= 0x20;
    if(((this->lw - x) < this->kick) && ((y + this->lw - x) > (this->lh - this->gate) / 2) && ((y + this->lw - x) < (this->lh + this->gate) / 2))   
        res |= 0x20; 
        
    // left down penalty
    
    if(((y + this->kick) <= this->lh) && ((x - this->kick) >= 0) && (this->p[(y + this->kick) * this->lw + x - this->kick] == 0))
        res |= 0x80;
    if(( x < this->kick) && ((y + x) > (this->lh - this->gate) / 2) && ((y + x) < (this->lh + this->gate) / 2))   
        res |= 0x80;
    
    
    return res; // This is mask of direction
}
