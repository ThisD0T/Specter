#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "ymd.hpp"

#ifndef SPECTER_INTERFACE
#define SPECTER_INTERFACE

// the class that will handle user input, this WILL NOT do any manipulation of the data, that is for Manager
// this is simple a class for the user to interface with Manager 
// (like some kind of User Interface or something)
class Interface {
    public:

        std::vector<Year> years;
        Year current_edit_year;
        bool run;

        int x_width, y_width;
        WINDOW* main_win;

        int columns;// num of columns to have (I know this is weird)
        int padding_x = 5, padding_y = 2;
        std::vector<std::string> menu_options;

        Interface() {
            current_edit_year = (2023);

        }

        void init_ncurses() {
            // ----- ncurses initialization -----
            initscr();
            noecho();
            cbreak();

            getmaxyx(stdscr, x_width, y_width);

            main_win = newwin(6, x_width-15, y_width-15, 16);
        }

        void main_loop() {
            int input;
            int selected;// holds which option is selected

            // TEST
            while (input != 'q') {
                clear();

                box(main_win, 0, 0);

                display_month(current_edit_year.months[1]);

                // display menu options
                for (int i = 0; i < menu_options.size(); i++) {
                    int y_pos = (i / columns) * padding_y;// conveniently the compiler always rounds down
                    int x_pos = 5 + (i%columns) * padding_x;
                    mvprintw(y_pos, x_pos, menu_options[i].c_str());
                }
    
                refresh();
                wrefresh(main_win);
                input = getch();
            }
            endwin();
        }

        void clear_screen() {
            system("clear");
        }

        void display_years() {

        }
        void display_year() {

            std::cout << current_edit_year.year_num;
        }
        void display_month(Month month) {
            menu_options.clear();
            columns = 7;

            for (int i = 0; i < days_in_month(month.name); i++) {
                menu_options.push_back(std::to_string(month.days[i].day));
            }
        }
        void display_week() {

        }
        void display_day() {

        }
};

#endif

