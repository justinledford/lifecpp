#include <vector>
#include <string>

class GameOfLife {
    public:
        GameOfLife(int=250, std::string="random");
        void start();
    private:
        void initializeGui();
        void initialRandom();
        void initialGlider();
        void displayGen();
        void eraseGen();
        void calcNextGen();

        int speed;
        std::string mode;

        int row;
        int col;
        
        std::vector<std::vector<int> > currentGen;
        std::vector<std::vector<int> > nextGen;


};
