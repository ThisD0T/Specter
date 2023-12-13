#ifndef __YMD__
#define __YMD__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <ncurses.h>
#include "ui.hpp"
#include "lib.hpp"
#include <sstream>
#include <boost/archive/basic_binary_iarchive.hpp>
#include <boost/archive/basic_binary_oarchive.hpp>

using std::string;

// file for defining year, month and day structs for other files

// because you can't make a static map apparently?
inline int days_in_month(std::string month) {
    std::map<std::string, int> map;
    map["Jan"] = 31;
    map["Feb"] = 28;
    map["Mar"] = 31;
    map["Apr"] = 30;
    map["May"] = 31;
    map["Jun"] = 30;
    map["Jul"] = 31;
    map["Aug"] = 31;
    map["Sep"] = 30;
    map["Oct"] = 31;
    map["Nov"] = 30;
    map["Dec"] = 31;

    return map[month];
}

inline std::string month_name_from_digit(int digit) {
    if (digit > 12) {
        return "Err";
    }

    std::map<int, std::string> map;
    map[1] = "Jan";
    map[2] = "Feb";
    map[3] = "Mar";
    map[4] = "Apr";
    map[5] = "May";
    map[6] = "Jun";
    map[7] = "Jul";
    map[8] = "Aug";
    map[9] = "Sep";
    map[10] = "Oct";
    map[11] = "Nov";
    map[12] = "Dec";

    return map[digit];
}


struct Event {
    public:
        std::string title;
};

struct Todo {
    public:
        std::string title;
        bool complete;
};

class Day: public Screen {
    public:
        int day, month_num;

        std::vector<Event> events;
        std::vector<Todo> todos;

        Day(int day, int month_num): day(day), month_num(month_num) {}

        void add_event() {
            string name = get_string_input(2, 2, "Event Name");
            events.push_back(Event{name});
        }

        Screen *handle_input(UserInput input) {
            switch (input) {
                case UP:
                    selected_y --;
                    break;
                case DOWN:
                    selected_y ++;
                    break;
                case LEFT:
                    selected_x --;
                    break;
                case RIGHT:
                    selected_x ++;
                    break;
                case ENTER:
                    break;
                case DELETE:
                    if (get_user_confirm(2, 2, "Are you sure you want to delete event?")) {
                        events.erase(events.begin()+selected_y);
                    }
                    break;
                case A:
                    add_event();
                    break;
                default:
                    break;
            }
            return nullptr;
        }

        void display() {
            clear();

            mvprintw(1, 2, "%i of %s", day, month_name_from_digit(month_num).c_str());

            for (int i = 1; i < events.size()+1; i++) {
                set_highlighted(i, selected_x);
                mvprintw(i * 3, 2, events[i-1].title.c_str());
            }
        }
};

class Week: public Screen {
    public:
        std::vector<Day> days;

        void display(int y_pos, int grid_y_pos, int y_select, int x_select) {
            selected_y = y_select;
            selected_x = x_select;

            for (int i = 0; i < days.size(); i++) {
                set_highlighted(grid_y_pos, i);
                mvprintw(y_pos, i * 10, "%i", days[i].day);
            }
        }
};

class Month: public Screen {
    public:
        std::vector<Week> weeks;
        int digit;
        std::string name;
        int num_weeks;

        Month(int month_digit): digit(month_digit), name(month_name_from_digit(month_digit)) {
            int days_counter = 0;

            if (days_in_month(name) > 28) {
                num_weeks = 5;
            }
            else {
                num_weeks = 4;
            }

            // create weeks
            for (int i = 0; i <  num_weeks; i++) {
                Week new_week;

                // fill week with days
                while (new_week.days.size() < 7) {
                    days_counter ++;
                    if (days_counter > days_in_month(name)) {
                        break;
                    }

                    Day new_day = Day(days_counter, digit);
                    new_week.days.push_back(new_day);
                }

                weeks.push_back(new_week);
            }
        }

        Screen *handle_input(UserInput input) {
            switch (input) {
                case UP:
                    selected_y --;
                    break;
                case DOWN:
                    selected_y ++;
                    break;
                case LEFT:
                    selected_x --;
                    break;
                case RIGHT:
                    selected_x ++;
                    break;
                case ENTER:
                    return &weeks[selected_y].days[selected_x];
                    break;
                case A:
                    weeks[selected_y].days[selected_x].add_event();
                    break;
                default:
                    break;
            }
            return nullptr;
        }

        void display() {
            clear();
            for (int i = 0; i < weeks.size(); i++) {
                weeks[i].display(i * 4, i, selected_y, selected_x);
            }
        }
};

class Year: public Screen {
    public:
        int year_num;
        std::vector<Month> months;

        Year(): year_num(0) {};
        Year(int year_num): year_num(year_num) {
            for (int i = 1; i < 13; i++) {
                Month new_month(i);
                months.push_back(new_month);
            }
        }

        void display() {
            clear();
            mvprintw(1, 2, "[year]");
            for (int i = 1; i < 13; i++) {
                set_highlighted(selected_y, i);
                mvprintw(3, i * 5, month_name_from_digit(i).c_str());
            }
        }

        Screen *handle_input(UserInput input) {
            switch (input) {
                case ENTER:
                    return &months[selected_x - 1];
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

            return nullptr;
        }
};

std::map<std::string, int> get_days_in_months();

#endif
