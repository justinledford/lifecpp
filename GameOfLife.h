#include <vector>
#include <string>

#include "Grid.h"

class GameOfLife {
    public:
        GameOfLife(int=250, std::string="random");
        void start();
    private:
        void initializeGui();
        void initialRandom();
        void initialGlider();
        void initialRPentomino();
        void displayGen();
        void eraseGen();
        void calcNextGen();

        int speed;
        std::string mode;

        int row;
        int col;
        
        Grid currentGen;
        Grid nextGen;
};
