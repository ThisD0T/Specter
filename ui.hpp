#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "ymd.hpp"

using std::string;

#ifndef SPECTER_INTERFACE
#define SPECTER_INTERFACE

enum EditingType{
    YEAR,
    MONTH,
    WEEK,
    DAY,
};

enum UserInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ESC,
    ENTER,
    QUIT,
    NOTHING,
};

// the class that will handle user input, this WILL NOT do any manipulation of the data, that is for Manager
// this is simple a class for the user to interface with Manager 
// (like some kind of User Interface or something)
class Interface {
    public:

        std::vector<Year> years;
        Year *editing_year;
        Month *editing_month;
        Week *editing_week;
        Day *editing_day;

        int x_width, y_width;
        WINDOW* main_win;
        int selected = 10;// holds which option is selected

        int columns;// num of columns to have (I know this is weird)
        int padding_x = 15, padding_y = 4;
        std::vector<std::string> menu_options;
        UserInput user_input;

        int currently_editing;
        const EditingType EDITING_HEIRARCHY[4] = {YEAR, MONTH, WEEK, DAY};

        Interface(Year *year) {
            editing_year = year;
        }

        void init() {
            // ----- ncurses initialization -----
            initscr();
            noecho();
            cbreak();

            getmaxyx(stdscr, x_width, y_width);

            editing_month = &editing_year->months[1];
            editing_week = &editing_month->weeks[0];
            editing_day = &editing_week->days[0];
            currently_editing = 1;

            main_loop();
        }

        void main_loop() {
            // TEST
            while (user_input != QUIT) {
                switch (EDITING_HEIRARCHY[currently_editing]) {
                    case YEAR:
                        display_year();
                        break;
                    case MONTH:
                        display_month();
                        break;
                    case WEEK:
                        display_week();
                        break;
                    case DAY:
                        display_day();
                        break;
                }
                handle_input();
            }
            endwin();
        }

        void handle_input() {
            int input = 0;
            input = getch();

            switch (input) {
                case 107:// up 
                    if (selected - columns >= 0) {
                        selected -= columns;
                    }
                    user_input = UP;
                    break;
                case 106:// down
                    if (selected + columns < menu_options.size()) {
                        selected += columns;
                    }
                    user_input = DOWN;
                    break;
                case 104:// left
                    if (selected - 1 >= 0) {
                        selected --;
                    }
                    user_input = LEFT;
                    break;
                case 108:// right
                    if (selected + 1 < menu_options.size()) {
                        selected ++;
                    }
                    user_input = RIGHT;
                    break;
                case 27:// esc
                    user_input = ESC;
                    break;
                case 10:// enter
                    user_input = ENTER;
                    break;
                case 113:// quit
                    user_input = QUIT;
                default:
                    break;
            }

            if (user_input == ENTER) {

                switch (EDITING_HEIRARCHY[currently_editing]) {
                    case MONTH:
                        if (selected % 8 == 0) {// if hovering over a week
                            currently_editing = 2;
                            selected = 1;
                            editing_week = &editing_month->weeks[selected];
                        } else {// if hovering over a day
                            currently_editing = 3;
                            selected = 1;
                            editing_day = get_day_from_menu_selection(selected);
                        }
                        break;
                    default:
                        break;
                }
            }

            if (user_input == ESC) {
                selected = 1;
                currently_editing --;
            }
        }

        void display_years() {

        }
        void display_year() {

        }
        void display_month() {
            clear();
            menu_options.clear();
            columns = 8;
            int padding_x = 15, padding_y = 4;

            // put all buttons into a list
            for (int i = 0; i < days_in_month(editing_month->name); i++) {
                // if you are at the start of a week, insert an extra button to 
                // go straight to week view
                if ((i % 7) == 0) {
                    // I know the way I am doing weeks in month view is sketchy, sshhhh
                    menu_options.push_back("Week View");
                }
                menu_options.push_back(std::to_string(i + 1));
            }


            // display buttons
            for (int i = 0; i < menu_options.size(); i++) {
                int y_pos = (i / columns) * padding_y;// conveniently it always rounds down
                int x_pos = 0;

                if (i % 8 == 0)  {
                    x_pos = 1;
                }
                else {
                    x_pos = padding_x + (i%columns) * padding_x;
                }

                if (i == selected) {
                    attron(A_STANDOUT);
                    mvprintw(y_pos, x_pos, menu_options[i].c_str());
                    continue;
                }

                attroff(A_STANDOUT);
                mvprintw(y_pos, x_pos, menu_options[i].c_str());
            }
            refresh();
        }

        void display_week() {
            clear();
            menu_options.clear();
            columns = 7;
            int padding_x = 3, padding_y = 2;

            for (int i = 0; i < 7; i++) {
                menu_options.push_back(std::to_string(i));
            }

            for (int i = 0; i < menu_options.size(); i++) {
                int y_pos = (i / columns) * padding_y;// conveniently it always rounds down
                int x_pos = 0;

                x_pos = padding_x + (i%columns) * padding_x;

                if (i == selected) {
                    attron(A_STANDOUT);
                    mvprintw(y_pos, x_pos, menu_options[i].c_str());
                    continue;
                }

                attroff(A_STANDOUT);
                mvprintw(y_pos, x_pos, menu_options[i].c_str());
            }
            refresh();
        }

        void display_day() {
            clear();
            
            mvprintw(2, 2, std::to_string(editing_day->day).c_str());
            refresh();
        }

        Day* get_day_from_menu_selection(int index) {
            return &editing_month->weeks[(selected / 8)].days[(selected % 8) - 1];
        }
};

#endif

