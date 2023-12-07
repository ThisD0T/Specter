#include <ncurses.h>
#include <vector>
#include <string>

using std::string, std::vector;

#ifndef __UI_MANAGER__
#define __UI_MANAGER__

class MenuOption {
public:
    string name, desc, tag;
    int pos_x, pos_y;

    bool highlighted;

    MenuOption(string name, string tag, int pos_x, int pos_y, string desc = ""): name(name), tag(tag), desc(desc), pos_x(pos_x), pos_y(pos_y) {
        
    }
};

// this class will handle input from it's own menu options and print to the screen.
// this is so you can have all different kinds of menu screens to go through, what fun!
class Screen {
public:
    Screen(){}

    vector<vector<MenuOption>> menu_options;
    MenuOption *active_menu_option;

    int selected_x, selected_y;

    void display() {
        for (int i = 0; i < menu_options.size(); i++) {
            for (int j = 0; j < menu_options[i].size(); j++) {
                if (j == selected_x && i == selected_y) {
                    attron(A_STANDOUT);
                }
                else {
                    attroff(A_STANDOUT);
                }

                MenuOption option = menu_options[i][j];
                mvprintw(option.pos_y, option.pos_x, option.name.c_str());
            }
        }
    }
};

#endif
