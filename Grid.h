#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {

    public:
        Grid();

        void setState(int, int, int);
        int getState(int, int) const;

        void initializeCoordinates(int, int);

    private:
        std::vector<std::vector<int> > coordinates;
        int max_row;
        int max_col;
};

#endif
