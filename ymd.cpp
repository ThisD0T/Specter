#include <vector>
#include <string>
#include <map>

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
        int month;

        std::vector<Event> events;
        std::vector<Todo> todos;
};

struct Month {
    public:
        std::vector<Day> days;
};

struct Year {
    public:
        std::vector<Month> months;
};

std::map<std::string, int> get_days_in_months();

class Manager {
    public:
        Manager();
        Year make_new_year(int year);

        Year current_year_editing;
};


std::map<std::string, int> get_days_in_months() {
    std::map<std::string, int> days;
    days["Jan"] = 31;
    days["Feb"] = 28;
    days["Mar"] = 31;
    days["Apr"] = 30;
    days["May"] = 31;
    days["Jun"] = 30;
    days["Jul"] = 31;
    days["Aug"] = 31;
    days["Sep"] = 30;
    days["Oct"] = 31;
    days["Nov"] = 30;
    days["Dec"] = 31;

    return days;
}
