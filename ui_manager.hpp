#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include "ymd.hpp"
#include "functions.hpp"

using std::string;
using std::vector;

#ifndef SPECTER_INTERFACE
#define SPECTER_INTERFACE

enum EditingType{
    YEAR,
    MONTH,
    WEEK,
    DAY,
};

// the class that will handle user input, this WILL NOT do any manipulation of 
// the data, that is for Manager this is simple a class for the user to 
// interface with Manager (like some kind of User Interface or something)
class Interface {
    public:

        // "editing_ymwd" meaning the one that is currently being editetd 
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

            editing_month = &editing_year->months[2];
            editing_week = &editing_month->weeks[0];
            editing_day = &editing_week->days[0];
            currently_editing = 1;

            main_loop();
        }

        void main_loop() {
            // TEST
            while (user_input != QUIT) {
                /*switch (EDITING_HEIRARCHY[currently_editing]) {
                    case YEAR:
                        display_year();
                        break;
                    case MONTH:
                        editing_month->screen.display();
                        break;
                    case WEEK:
                        display_week();
                        break;
                    case DAY:
                        display_day();
                        break;
                }*/
                editing_month->draw_screen();
                handle_input();
            }
            endwin();
        }

        void handle_input() {
            int input = 0;
            int increment = 0;
            input = getch();

            switch (input) {
                case 107:// up 
                    user_input = UP;
                    break;
                case 106:// down
                    user_input = DOWN;
                    break;
                case 104:// left
                    user_input = LEFT;
                    break;
                case 108:// right
                    user_input = RIGHT;
                    break;
                case 121:
                    user_input = LEFT_ARROW;
                    increment = -1;
                    break;
                case 117:
                    user_input = RIGHT_ARROW;
                    increment = 1;
                    break;
                case 97:
                    user_input = A;
                    break;
                case 100:
                    user_input = DELETE;
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
                            editing_week = &editing_month->weeks[selected / 8];
                            selected = 0;
                        } else {// if hovering over a day
                            currently_editing = 3;
                            editing_day = get_day_from_menu_selection(selected);
                            selected = 0;
                        }
                        break;
                    case WEEK:
                        currently_editing = 3;
                        editing_day = &editing_week->days[selected];
                        selected = 0;
                    case DAY:
                    default:
                        break;
                }
            }

            if (user_input == A) {
                add_event();
            } else if (user_input == DELETE && currently_editing == 3 && editing_day->events.size() > 0) {
                if (get_user_confirm(1, 2, "are you sure you want to delete the highlighted event?")) {
                    editing_day->events.erase(editing_day->events.begin()+selected);
                }
            }

            // just blindly pop up one level if the user presses esc
            if (user_input == ESC) {
                if (currently_editing > 0) {
                    selected = 0;
                    currently_editing --;
                }
            }

            int new_index;

            // increment the current editing y/m/d
            if (user_input != LEFT_ARROW && user_input != RIGHT_ARROW)
                return;
            switch (EDITING_HEIRARCHY[currently_editing]) {
                case YEAR:
                    break;
                case MONTH:
                    // am I just this bad at programming?
                    editing_month = increment_current_edit(editing_year->months, editing_month, increment);
                    // why does every single line look like this piece of shit ^.
                    break;
                case WEEK:
                    editing_week = increment_current_edit(editing_month->weeks, editing_week, increment);
                    break;
                case DAY:
                    editing_day = increment_current_edit(editing_week->days, editing_day, increment);
                    break;
                default:
                    break;
            }
        }
        
        template<typename T>
        T* increment_current_edit(std::vector<T> &vec, T* current_item, int increment) {
            for (int i = 0; i < vec.size(); i++) {
                if (current_item == &vec[i]) {
                    if (i + increment < 0)
                        return &vec[vec.size() - 1];
                    if (i + increment > vec.size() - 1)
                        return &vec[0];

                    return &vec[i + increment];
                }
            }
            return current_item;
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
            int offset_x = 1, offset_y = 3;

            mvprintw(1, 1, ('[' + editing_month->name + ']').c_str());

            for (int i = 0; i < days_in_month(editing_month->name); i++) {
                if ((i % 7) == 0) {
                    menu_options.push_back("Week View");
                }
                menu_options.push_back(std::to_string(i + 1));
            }


            // display buttons
            for (int i = 0; i < menu_options.size(); i++) {
                int y_pos = (i / columns) * padding_y + offset_y;// conveniently it always rounds down
                int x_pos = 0;

                if (i % 8 == 0)  {
                    x_pos = offset_x;
                }
                else {
                    x_pos = padding_x + (i%columns) * padding_x + offset_x;
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
               
            for (int i = 0; i < editing_week->days.size(); i++) {
                menu_options.push_back(std::to_string(editing_week->days[i].day));
            }

            for (int i = 0; i < menu_options.size(); i++) {
                int y_pos = (i / columns) * padding_y;// conveniently it always rounds down
                int x_pos = padding_x + (i%columns) * padding_x;

                if (i == selected)
                    attron(A_STANDOUT);
                else
                    attroff(A_STANDOUT);
                mvprintw(y_pos, x_pos, std::to_string(editing_week->days[i].day).c_str());
                mvprintw(y_pos + 2, x_pos - 1, ("events: " + std::to_string(editing_week->days[i].events.size())).c_str());
            }
            refresh();
        }

        void display_day() {
            int y_padding = 2, y_offset = 2;
            columns = 1;
            clear();
            menu_options.clear();

            mvprintw(1, 2, ("date: " + std::to_string(editing_day->day)).c_str());

            for (int i = 0; i < editing_day->events.size(); i++) {
                menu_options.push_back(editing_day->events[i].title);
            }

            for (int i = 0; i < menu_options.size(); i++) {
                int y_pos = i * y_padding + y_offset;
                if (i == selected) {
                    attron(A_STANDOUT);
                } else {
                    attroff(A_STANDOUT);
                }
                mvprintw(y_pos, 1, menu_options[i].c_str());
            }

            refresh();
        }

        void add_event() {
            string name = get_string_input(1, 1, "Event Name");
            editing_day->events.push_back(Event(name));
        }

        void add_todo(Day *day) {
        }

        Day* get_day_from_menu_selection(int index) {
            return &editing_month->weeks[(selected / 8)].days[(selected % 8) - 1];
        }

        int get_int_from_user() {
            return 0;
        }

        bool get_user_confirm(int x, int y, string title = "") {
            mvprintw(y, x, title.c_str());
            char input = getch();
            if (input == 10) 
                return true;
            else return false;
        }
};

#endif

