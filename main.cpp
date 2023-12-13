#include <iostream>
#include <vector>
#include <map>

#include "ymd.hpp"
#include "ui.hpp"
#include "ui_manager.hpp"

int main() {
    Year year = Year(2023);
    Interface interface = Interface(&year);
    interface.init();

    return 0;
}
