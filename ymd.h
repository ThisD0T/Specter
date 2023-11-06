#include <iostream>
#include <vector>
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

