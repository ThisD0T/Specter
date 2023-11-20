#include <iostream>
#include <vector>
#include <map>

#include "ymd.hpp"
#include "ui.hpp"

int main() {
    Year year = Year(2023);
    Interface interface = Interface(&year);
    interface.init();
    Manager manager;
    manager.make_new_year(2023);

    return 0;
}
