#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#include <vector>
#include <iostream>
#include <string>

#include "GameOfLife.h"

using namespace std;

GameOfLife::GameOfLife(int s, string m)
:speed(s),mode(m),currentGen(),nextGen()
{
    initializeGui();

    currentGen.initializeCoordinates(row, col);
    nextGen.initializeCoordinates(row, col);
}

void GameOfLife::start() {

    if(mode == "glider")
        initialGlider();
    else
        initialRandom();

    while(true) {
        displayGen();
        refresh();
        usleep(speed * 1000);
        eraseGen();
        calcNextGen();
    }
           
    getch();
    endwin();
}

void GameOfLife::initializeGui() {

    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    //timeout(1);

    getmaxyx(stdscr, row, col);


    // col needs to be odd and space at right end 
    col--;

    if(col % 2 == 0)
        col--;
}


void GameOfLife::initialRandom() {
    srand(time(NULL));

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            currentGen.setState(i, j, rand() % 2);
        }
    }
}

void GameOfLife::initialGlider() {
    int centerY = row / 2;
    int centerX = col / 2;

    if((centerX % 2) == 1)
        centerX += 1;

    //mvprintw(0,0, "%u %u", row, col);
    //mvprintw(1,0, "%u %u", centerY, centerX);

    currentGen.setState(centerY - 1, centerX, 1);
    currentGen.setState(centerY + 1, centerX, 1);
    currentGen.setState(centerY - 1, centerX - 2, 1);
    currentGen.setState(centerY - 1, centerX + 2, 1);
    currentGen.setState(centerY, centerX - 2, 1);
}


void GameOfLife::displayGen() {
    //mvprintw(0, 0, "%u", (unsigned)time(NULL));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen.getState(i, j) == 1) {
                attron(COLOR_PAIR(1));
                mvprintw(i,j, "  ");
            }
        }
    }
}

void GameOfLife::eraseGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen.getState(i, j) == 1) {
                attroff(COLOR_PAIR(1));
                mvprintw(i,j, "  ");
            }
        }
    }
}

void GameOfLife::calcNextGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            int liveNeighbors = 0;

            liveNeighbors += currentGen.getState(i, j+2); //right
            liveNeighbors += currentGen.getState(i, j-2); //left
            liveNeighbors += currentGen.getState(i+1,j+2); 
            //bottom right
            liveNeighbors += currentGen.getState(i-1,j+2); //top right
            liveNeighbors += currentGen.getState(i+1, j-2); //bottom left
            liveNeighbors += currentGen.getState(i-1, j-2); //top left
            liveNeighbors += currentGen.getState(i-1, j); //top
            liveNeighbors += currentGen.getState(i+1, j); //bottom





            if(currentGen.getState(i, j) == 1) {
                if(liveNeighbors < 2) {
                    nextGen.setState(i, j, 0);
                } else if (liveNeighbors >=2 && liveNeighbors <= 3) {
                    nextGen.setState(i, j, 1);
                } else {
                    nextGen.setState(i, j, 0);
                }
            } else if(currentGen.getState(i, j) == 0) {
                if(liveNeighbors == 3) {
                    nextGen.setState(i, j, 1);
                }
            }
        }

    }


    currentGen = nextGen;

}

