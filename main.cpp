#include <iostream>
#include <vector>
#include <map>

#include "ymd.hpp"
#include "ui.hpp"

int main() {
    Interface interface = Interface();
    interface.init_ncurses();
    interface.main_loop();
    Manager manager;
    manager.make_new_year(2023);

    return 0;
}
