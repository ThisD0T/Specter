#include <iostream>

// the class that will handle user input
class Interface {
    public:

        Interface() {}


        void clear_screen() {
            //system("clear");
        }
};

class Specter {
    public:
        Specter();

        //Manager manager;
        Interface interface;
};
