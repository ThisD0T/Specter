#include <iostream>
#include <vector>
#include <map>

#include "ymd.hpp"

int main() {
    Manager manager;
    manager.make_new_year(2023);

    std::cout << days_in_month("Feb");

    return 0;
}
