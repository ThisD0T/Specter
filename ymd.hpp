#include <iostream>
#include <vector>
#include <string>
#include <map>

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

struct Month {
    public:
        std::vector<Day> days;
        int digit;
        std::string name;

        Month(int month_digit): digit(month_digit), name(month_name_from_digit(digit)) {
            for (int i = 0; i < days_in_month(name); i++) {
                Day new_day = {i};
                days.push_back(new_day);
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
            std::cout << year_num << ":";
            for (Month month : months) {
                std::cout << "\n" << month.digit << ", " << month.name << "\nlast day: " << month.days.size() << "\n";
            }
        }

        int year_num;
        std::vector<Month> months;
};

std::map<std::string, int> get_days_in_months();



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
