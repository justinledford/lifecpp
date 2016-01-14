#include <unistd.h>

#include <iostream>
#include <string>

#include "GameOfLife.h"

using namespace std;

int main(int argc, char **argv) {
    //Process options
    int gflag = 0;
    int Rflag = 0;
    int cflag = false;
    char *svalue;
    int opt;
    opterr = 0;
    int speed = 250;

    while((opt = getopt(argc, argv, "gcRs:")) != -1) {
        switch(opt) {
            case 'g':
                gflag = 1;
                break;
            case 'R':
                Rflag = 1;
                break;
            case 'c':
                cflag = true;
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
                    "-g\tGlider\n\t"
                    "-R\tR-pentomino\n\t"
                    "-s\tSpeed in ms\n\t"
                    "-c\tChange color for each generation\n";
                return 0;
            default:
                break;
        }
    }

    if(gflag) {
        GameOfLife game(speed, "glider", cflag);
        game.start();
    } else if(Rflag) {
        GameOfLife game(speed, "R", cflag);
        game.start();
    } else {
        GameOfLife game(speed, "random", cflag);
        game.start();
    }
}
