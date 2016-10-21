#include <vector>
#include <string>

#include "Grid.h"

class GameOfLife {
    public:
        GameOfLife(int=250, std::string="random", bool=false);
        void start();
    private:
        void initializeGui();
        void initialRandom();
        void initialGlider();
        void initialRPentomino();
        void displayGen();
        void eraseGen();
        void calcNextGen();
        int countLiveNeighbors(int, int);

        int speed;
        std::string mode;

        int row;
        int col;

        Grid previousGen;
        Grid currentGen;
        Grid nextGen;

        unsigned int genNumber;
        bool colorChange;
};
