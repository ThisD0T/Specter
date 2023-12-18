#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "ymd.hpp"
#include "ui.hpp"
#include "ui_manager.hpp"

int main() {
    Year year = Year(1977);
    Interface interface = Interface("specter.txt");
    interface.init();

    return 0;
}
