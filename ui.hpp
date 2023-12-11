#include <ncurses.h>
#include <vector>
#include <string>

using std::string, std::vector;

#ifndef __UI_MANAGER__
#define __UI_MANAGER__

struct Week;

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

class MenuOption {
public:
    string name; 
    string desc = "";
    string tag;
    int pos_x;
    int pos_y;

    bool highlighted = false;

    MenuOption(string name, string tag, int pos_y, int pos_x, string desc = ""): name(name), tag(tag), desc(desc), pos_x(pos_x), pos_y(pos_y) {
        
    }
};

// this class will handle input from it's own menu options and print to the screen.
// this is so you can have all different kinds of menu screens to go through, what fun!
class Screen {
public:
    vector<vector<MenuOption>> menu_options {
        {},
        {},
        {},
        {},
        {}
    };
    MenuOption *active_menu_option;

    int selected_x = 1, selected_y = 1;

    Screen(){}

    void display() {
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < menu_options[j].size(); i++) {
                if (j == selected_x && i == selected_y) {
                    attron(A_STANDOUT);
                }
                else {
                    attroff(A_STANDOUT);
                }

                mvprintw(menu_options[j][i].pos_y, menu_options[j][i].pos_x, menu_options[j][i].name.c_str());
            }
        }
    }

    void handle_input (UserInput input) {
        
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
            default:
                break;
        }
    }
};

#endif
