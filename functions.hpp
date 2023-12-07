
#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <ncurses.h>
#include <string>

using std::string;

string get_string_input(int x, int y, string title = "") {
    // should probably make it so it doesn't make a new window every single time
    WINDOW* input_window;
    int string_y = y;
    if (title == "") {// doesn't have title
        input_window = newwin(3, 30, y, x);
    } else {// has title
        input_window = newwin(4, 30, y, x);
    }

    string string = "";
    char input;
    while (true) {
        wclear(input_window);

        box(input_window, 0, 0);
        if (title != "") {
            wprintw(input_window, title.c_str());
        }
        mvwprintw(input_window, string_y, x, string.c_str());// warning because there may be a format specifier

        wrefresh(input_window);

        input = wgetch(input_window);
        if (input == '\n') {
            break;
        }
        string += input;
    }

    return string;
}

#endif

