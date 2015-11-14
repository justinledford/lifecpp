#include "Grid.h"

Grid::Grid() {}

void Grid::initializeCoordinates(int row, int col) {
    coordinates.resize(row);

    for(int i = 0; i < row; ++i) {
        coordinates[i].resize(col);
        fill(coordinates[i].begin(), coordinates[i].end(), 0);
    }

    max_row = row - 1;
    max_col = col - 1;
}

void Grid::setState(int row, int col, int n) {
   coordinates[row][col] = n; 
}

int Grid::getState(int row, int col) const {

    if(row < 0) {
        if(col < 0)
            return coordinates[max_row][max_col];
        else if(col > max_col)
            return coordinates[max_row][0];
        else
            return coordinates[max_row][col];
    } else if(row > max_row) {
        if(col < 0)
            return coordinates[0][max_col];
        else if(col > max_col)
            return coordinates[0][0];
        else
            return coordinates[0][col];
    } else {
        if(col < 0)
            return coordinates[row][max_col];
        else if(col > max_col)
            return coordinates[row][0];
        else
            return coordinates[row][col];
    }
}

