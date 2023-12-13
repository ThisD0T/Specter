#include <ncurses.h>
#include <vector>
#include <string>

using std::string, std::vector;

#ifndef __UI_MANAGER__
#define __UI_MANAGER__

class Day;
struct Week;
class Month;
class Year;

class Screen;

enum UserInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    LEFT_ARROW,
    RIGHT_ARROW,
    ESC,
    ENTER,
    QUIT,
    A,
    DELETE,
    NOTHING,
};

class Screen {
public:
    int selected_x = 1, selected_y = 1;

    Screen() {}

    virtual void display() {};

    virtual Screen *handle_input (UserInput input) {
        switch (input) {
            case UP:
                selected_y ++;
                break;
            case DOWN:
                selected_y --;
                break;
            case LEFT:
                selected_x --;
                break;
            case RIGHT:
                selected_x ++;
                break;
            case ENTER:
                break;
            default:
                break;
        }
        return nullptr;
    }

    // checks to see if you are currently printing the highlighted "button" and
    // sets ncurses to highlight that text
    void set_highlighted(int y, int x) {
        if (selected_x == x && selected_y == y) {
            attron(A_STANDOUT);
        } else {
            attroff(A_STANDOUT);
        }
    }
};

#endif
