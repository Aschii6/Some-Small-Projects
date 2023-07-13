#pragma once#include <vector>

using namespace std;

class GameOfLife {
    private: vector < vector < bool >> grid;

    public: GameOfLife(int x, int y) {
            grid.resize(x);
            for (int i = 0; i < x; i++) {
                grid[i].resize(y);
                for (int j = 0; j < y; j++) {
                    grid[i][j] = false;
                }
            }
        }

        ~GameOfLife() =
        default;

    vector < vector < bool >> getGrid() {
        return grid;
    }

    void evolve() {
        vector < vector < bool >> newGrid = grid;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                int neighbors = 0;

                if (i > 0 && j > 0 && grid[i - 1][j - 1]) neighbors++;
                if (i > 0 && grid[i - 1][j]) neighbors++;
                if (i > 0 && j < grid[i].size() - 1 && grid[i - 1][j + 1]) neighbors++;
                if (j > 0 && grid[i][j - 1]) neighbors++;
                if (j < grid[i].size() - 1 && grid[i][j + 1]) neighbors++;
                if (i < grid.size() - 1 && j > 0 && grid[i + 1][j - 1]) neighbors++;
                if (i < grid.size() - 1 && grid[i + 1][j]) neighbors++;
                if (i < grid.size() - 1 && j < grid[i].size() - 1 && grid[i + 1][j + 1]) neighbors++;

                if (grid[i][j]) {
                    if (neighbors < 2 || neighbors > 3) {
                        newGrid[i][j] = false;
                    }
                } else {
                    if (neighbors == 3) {
                        newGrid[i][j] = true;
                    }
                }
            }
        }
        grid = newGrid;
    }

    void setCell(int x, int y, bool newVal) {
        if (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size()) {
            grid[x][y] = newVal;
        }
    }
};
