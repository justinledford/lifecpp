#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#include <vector>
#include <iostream>
#include <string>

#include "GameOfLife.h"

using namespace std;

GameOfLife::GameOfLife(int s, string m)
:speed(s),mode(m)
{
    initializeGui();

    //Initialize vectors
    currentGen.resize(row);
    for(int i = 0; i < row; ++i) {
        currentGen[i].resize(col);
        fill(currentGen[i].begin(), currentGen[i].end(), 0);
    }

    nextGen.resize(row);
    for(int i = 0; i < row; ++i) {
        nextGen[i].resize(col);
        fill(nextGen[i].begin(), nextGen[i].end(), 0);
    }

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
}


void GameOfLife::initialRandom() {
    srand(time(NULL));

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            currentGen[i][j] = rand() % 2; 
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

    currentGen[centerY - 1][centerX] = 1;
    currentGen[centerY + 1][centerX] = 1;
    currentGen[centerY - 1][centerX - 2] = 1;
    currentGen[centerY - 1][centerX + 2] = 1;
    currentGen[centerY][centerX - 2] = 1;
}


void GameOfLife::displayGen() {
    //mvprintw(0, 0, "%u", (unsigned)time(NULL));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen[i][j] == 1) {
                attron(COLOR_PAIR(1));
                mvprintw(i,j, "  ");
            }
        }
    }
}

void GameOfLife::eraseGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen[i][j] == 1) {
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
            try {
                liveNeighbors += currentGen[i].at(j+2); //right
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen[i].at(j-2); //left
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i+1).at(j+2); //bottom right
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i-1).at(j+2); //top right
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i+1).at(j-2); //bottom left
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i-1).at(j-2); //top left
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i-1).at(j); //top
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i+1).at(j); //bottom
            } catch(out_of_range &e) {}


            if(currentGen[i][j] == 1) {
                if(liveNeighbors < 2) {
                    nextGen[i][j] = 0;
                } else if (liveNeighbors >=2 && liveNeighbors <= 3) {
                    nextGen[i][j] = 1;
                } else {
                    nextGen[i][j] = 0;
                }
            } else if(currentGen[i][j] == 0) {
                if(liveNeighbors == 3) {
                    nextGen[i][j] = 1;
                }
            }
        }
    }

    currentGen = nextGen;
}

