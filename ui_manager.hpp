#include <curses.h>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "ymd.hpp"
#include "ui.hpp"
#include "lib.hpp"

#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

class Interface {
    public:
        Screen *editing_screen;
        vector<Screen *> editing_stack;
        Year editing_year;

        int x_width, y_width;
        WINDOW* main_win;
        int selected = 10;// holds which option is selected

        UserInput user_input;

        const EditingType EDITING_HEIRARCHY[4] = {YEAR, MONTH, WEEK, DAY};

        Interface(string file_name) {
            {
                std::ifstream ifs(file_name);
                boost::archive::text_iarchive iarchive(ifs);

                iarchive >> editing_year;
            }
            
            editing_stack.push_back(&editing_year);

        }

        Interface(Year &year) {
            editing_year = year;
            editing_stack.push_back(&year);
        }

        void init() {
            // ----- ncurses initialization -----
            initscr();
            noecho();
            cbreak();

            getmaxyx(stdscr, x_width, y_width);

            main_loop();
        }

        void main_loop() {
            // TEST
            while (user_input != QUIT) {
                editing_stack[editing_stack.size()-1]->display();
                refresh();
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
                    save_current_year();
                default:
                    break;
            }

            // pop one level up if esc is pressed
            if (user_input == ESC && editing_stack.size() > 1) {
                editing_stack.pop_back();
            }

            Screen *new_screen = editing_stack[editing_stack.size()-1]->handle_input(user_input);
            if (new_screen != nullptr) {
                editing_stack.push_back(new_screen);
            }

            int new_index;
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

        void save_current_year() {
            std::ofstream ofs("specter.txt");
            {
                boost::archive::text_oarchive oarchive(ofs);

                oarchive << editing_year;
            }
        }

        void load_year(string file_name) {
            std::ifstream ifs(file_name);


            {
                boost::archive::text_iarchive iarchive(ifs);

                iarchive >> editing_year;
            }
        }
};

#endif

