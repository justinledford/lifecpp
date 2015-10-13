#include <unistd.h>

#include <iostream>
#include <string>

#include "GameOfLife.h"

using namespace std;

int main(int argc, char **argv) {
    //Process options
    int gflag = 0;
    char *svalue;
    int opt;
    opterr = 0;
    int speed = 250;

    while((opt = getopt(argc, argv, "gs:")) != -1) {
        switch(opt) {
            case 'g':
                gflag = 1;
                break;
            case 's':
                {
                    svalue = optarg;
                    string str(svalue);
                    speed = stoi(str, nullptr, 10);
                    break;
                }
            case '?':
                cout << "Random Game of life\nUsage:\n\t" 
                    "-g\tGlider mode\n\t-s\tSpeed in ms\n";
                return 0;
            default:
                break;
        }
    }

    if(gflag) {
        GameOfLife game(speed, "glider");
        game.start();
    }
    else {
        GameOfLife game(speed, "random");
        game.start();
    }
}

