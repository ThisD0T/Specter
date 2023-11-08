#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "ymd.hpp"

#ifndef SPECTER_INTERFACE
#define SPECTER_INTERFACE

enum EditingType{
    YEAR,
    MONTH,
    WEEK,
    DAY,
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
        bool user_enter;

        int currently_editing;
        const EditingType EDITING_HEIRARCHY[4] = {YEAR, MONTH, WEEK, DAY};

        Interface(Year *year) {
            editing_year = year;
        }

        void init_ncurses() {
            // ----- ncurses initialization -----
            initscr();
            noecho();
            cbreak();

            getmaxyx(stdscr, x_width, y_width);

            editing_month = &editing_year->months[1];
            editing_week = &editing_month->weeks[0];
            editing_day = &editing_week->days[0];
            currently_editing = 1;
        }

        void main_loop() {
            user_enter = false;
            int input;

            // TEST
            while (input != 'q') {
                clear();
                input = 0;

                refresh();

                input = getch();
                std::cout << input << "  ";
                switch (input) {
                    case 107:// Up
                        if (selected - columns < 0) {
                            break;
                        }
                        selected -= columns;
                        break;

                    case 106:// Down
                        if (selected + columns >= menu_options.size()) {
                            break;
                        }
                        selected += columns;
                        break;

                    case 104:// Left
                        if (selected - 1 < 0) {
                            selected = menu_options.size() - 1;
                            break;
                        }
                        selected --;
                        break;

                    case 108:// Right
                        if (selected + 1 >= menu_options.size()) {
                            selected = 0;
                            break;
                        }
                        selected ++;
                        break;

                    case 97:// Esc
                        if (currently_editing > 0) {
                            currently_editing --;
                            break;
                        }
                        break;

                    case 102:// Enter
                        user_enter = true;
                        break;

                    default:
                        break;
                }

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
    

            }
            endwin();
        }

        void clear_screen() {
            system("clear");
        }

        void display_years() {

        }
        void display_year() {

        }
        void display_month() {
            menu_options.clear();
            columns = 8;

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

            // display menu options
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

            if (user_enter) {
                if (selected % 8 == 0) {
                    currently_editing = 2;
                    editing_week = &editing_month->weeks[selected];
                } else {
                    currently_editing = 3;
                    editing_day = get_day_from_menu_selection(selected);
                }
                user_enter = false;
            }
        }
        void display_week() {

        }
        void display_day() {
            clear();
            
            mvprintw(2, 2, std::to_string(editing_day->day).c_str());
        }

        Day* get_day_from_menu_selection(int index) {
            return &editing_month->weeks[(selected / 8)].days[(selected % 8) - 1];
        }
};

#endif

