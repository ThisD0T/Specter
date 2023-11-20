#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

#ifndef __YMD__
#define __YMD__

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
};

struct Day {
    public:
        int day;

        std::vector<Event> events;
        std::vector<Todo> todos;
};

struct Week {
    public:
        std::vector<Day> days;
};

class Month {
    public:
        std::vector<Week> weeks;
        int digit;
        std::string name;

        Month(int month_digit): digit(month_digit), name(month_name_from_digit(digit)) {
            int days_counter = 0;
            int num_weeks;

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

                    Day new_day = {days_counter};
                    new_week.days.push_back(new_day);
                }

                weeks.push_back(new_week);
            }
        }
};

class Year {
    public:
        Year(): year_num(0) {};
        Year(int year_num): year_num(year_num) {
            for (int i = 1; i < 13; i++) {
                Month new_month(i);
                months.push_back(new_month);
            }
        }

        void test_print() {
            for (Month month : months) {
            }
        }

        int year_num;
        std::vector<Month> months;
};

std::map<std::string, int> get_days_in_months();



//stores data that needs to be serde'd
class Manager {
    public:
        Manager() {}
        
        Year make_new_year(int year_num) {
            Year year = Year(year_num);
            year.test_print();
            return year;
        };

        Year current_year_editing;
};

#endif
