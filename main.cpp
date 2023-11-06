#include <iostream>
#include <vector>
#include <map>

#include "ymd.h"
#include "Specter.hpp"


// the class that will handle user input
class Interface {
    public:

        Interface() {}


        void clear_screen() {
            system("clear");
        }
};

int main() {
    Interface ui;

    std::map<std::string, int> map = get_days_in_months();

    return 0;
}
