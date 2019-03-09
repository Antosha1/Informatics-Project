#include <wx/wx.h>


class game {
    public :
        int width;
        int height;
        int gate;
        int travel; // length of curve. default 3
        int kick;  // length of penalty, default 6
        int * p; // array of points
        int * e; // array of edges
        int lw; // logical width
        int lh; // logical height
        int lg; // logical gate
        int current_place_x;
        int current_place_y;
        int current_player;
        int move_number;
        int gameover;
        
    public :
        game(); // default constructor
        game(int, int, int, int, int); // user constructor
        ~game(); // destructor
        int GetWidth(); // width in pixels
        int GetHeight(); // height in pixels
        int GetGate();  // width of gate in pixels
        int MoveEnable(int, int, int); // if move enable return mask of direction elee 0x0
        int PenaltyEnable(); // if penalty enable return mask of directions else 0x0
    };
