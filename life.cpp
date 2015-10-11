#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;

void initialRandom(vector<vector<int> > &, int, int);
void displayGen(vector<vector<int> > &, int, int);
void eraseGen(vector<vector<int> > &, int, int);
void calcNextGen(vector<vector<int> > &currentGen, vector<vector<int> > &nextGen,
        int row, int col);


int main() {
    //int row, col;
    int row = 20;
    int col = 88;

    srand(time(NULL));

    initscr();
    noecho();
    curs_set(0);
    start_color();
    //timeout(1);

    getmaxyx(stdscr, row, col);

    // Initialize vectors
    vector<vector<int> > currentGen;
    vector<vector<int> > nextGen;

    currentGen.resize(row);
    for(int i = 0; i < row; ++i) {
        currentGen[i].resize(col);
    }

    nextGen.resize(row);
    for(int i = 0; i < row; ++i) {
        nextGen[i].resize(col);
    }


    initialRandom(currentGen, row, col);

    while(true) {
        displayGen(currentGen, row, col);

        refresh();
        usleep(500000);

        eraseGen(currentGen, row, col);
        calcNextGen(currentGen, nextGen, row, col);
    }
           
    getch();
    endwin();
}


void initialRandom(vector<vector<int> > &currentGen, int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            currentGen[i][j] = rand() % 2; 
        }
    }
}



void displayGen(vector<vector<int> > &currentGen, int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen[i][j] == 1) {
                attron(A_REVERSE);
                mvprintw(i,j, "  ");
            }
        }
    }
}

void eraseGen(vector<vector<int> > &currentGen, int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            if(currentGen[i][j] == 1) {
                attroff(A_REVERSE);
                mvprintw(i,j, "  ");
            }
        }
    }
}

void calcNextGen(vector<vector<int> > &currentGen, vector<vector<int> > &nextGen,
        int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j += 2) {
            int liveNeighbors = 0;
            try {
                liveNeighbors += currentGen[i].at(j+2);
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen[i].at(j-2);
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i+1).at(j+2);
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i-1).at(j+2);
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i+1).at(j-2);
            } catch(out_of_range &e) {}
            try {
                liveNeighbors += currentGen.at(i-1).at(j-2);
            } catch(out_of_range &e) {}

            if(currentGen[i][j] == 1) {
                if(liveNeighbors < 2) {
                    nextGen[i][j] = 0;
                } else if (liveNeighbors >=2 && liveNeighbors < 3) {
                    nextGen[i][j] = 1;
                } else {
                    nextGen[i][j] = 0;
                }
            } else {
                if(liveNeighbors == 3) {
                    nextGen[i][j] = 1;
                }
            }
        }
    }

    currentGen = nextGen;
}

