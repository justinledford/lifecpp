#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameOfLife.h"

using namespace std;

GameOfLife::GameOfLife(int s, string m, bool c)
:speed(s),mode(m),currentGen(),nextGen()
{
    initializeGui();

    previousGen.initializeCoordinates(row, col);
    currentGen.initializeCoordinates(row, col);
    nextGen.initializeCoordinates(row, col);

    genNumber = 0;
    colorChange = c;
}

void GameOfLife::start() {
    if(mode == "glider")
        initialGlider();
    else if(mode == "R")
        initialRPentomino();
    else
        initialRandom();

    while(true) {
        displayGen();
        refresh();
        usleep(speed * 1000);
        calcNextGen();
        eraseGen();
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
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_CYAN);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);

    getmaxyx(stdscr, row, col);

    col /= 2;
}

void GameOfLife::initialRandom() {
    srand(time(NULL));

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            currentGen.setState(i, j, rand() % 2);
        }
    }
}

void GameOfLife::initialGlider() {
    int centerY = row / 2;
    int centerX = col / 2;

    if((centerX % 2) == 1)
        centerX += 1;

    currentGen.setState(centerY - 1, centerX, 1);
    currentGen.setState(centerY + 1, centerX, 1);
    currentGen.setState(centerY - 1, centerX - 1, 1);
    currentGen.setState(centerY - 1, centerX + 1, 1);
    currentGen.setState(centerY, centerX - 1, 1);
}

void GameOfLife::initialRPentomino() {
    int centerY = row / 2;
    int centerX = col / 2;

    if((centerX % 2) == 1)
        centerX += 1;

    currentGen.setState(centerY, centerX, 1);
    currentGen.setState(centerY + 1, centerX, 1);
    currentGen.setState(centerY - 1, centerX, 1);
    currentGen.setState(centerY, centerX - 1, 1);
    currentGen.setState(centerY - 1, centerX + 1, 1);
}


void GameOfLife::displayGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(currentGen.getState(i, j) == 1 && 
                    previousGen.getState(i, j) == 0) {
                if(colorChange)
                    attron(COLOR_PAIR(genNumber % 6 + 1));
                else
                    attron(COLOR_PAIR(1));
                mvprintw(i,j*2, "  ");
            }
        }
    }
}

void GameOfLife::eraseGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(currentGen.getState(i, j) == 0) {
                attroff(COLOR_PAIR(1));
                mvprintw(i,j*2, "  ");
            }
        }
    }
}

void GameOfLife::calcNextGen() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            int liveNeighbors = 0;

            liveNeighbors += currentGen.getState(i, j+1); //right
            liveNeighbors += currentGen.getState(i, j-1); //left
            liveNeighbors += currentGen.getState(i+1,j+1); //bottom right
            liveNeighbors += currentGen.getState(i-1,j+1); //top right
            liveNeighbors += currentGen.getState(i+1, j-1); //bottom left
            liveNeighbors += currentGen.getState(i-1, j-1); //top left
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

    previousGen = currentGen;
    currentGen = nextGen;
    genNumber++;
}

