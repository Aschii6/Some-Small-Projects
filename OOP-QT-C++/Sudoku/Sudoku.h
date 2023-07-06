//
// Created by User on 06/07/2023.
//
#pragma once
#include "exception"

using namespace std;

class Sudoku {
private:
    int correctBoard[9][9] = {
            {5, 6, 3, 8, 7, 9, 2, 1, 4},
            {7, 1, 9, 4, 2, 3, 6, 5, 8},
            {2, 8, 4, 5, 6, 1, 3, 9, 7},
            {4, 2, 6, 1, 5, 7, 9, 8, 3},
            {1, 9, 5, 6, 3, 8, 4, 7, 2},
            {8, 3, 7, 2, 9, 4, 1, 6, 5},
            {9, 4, 8, 3, 1, 5, 7, 2, 6},
            {6, 5, 1, 7, 4, 2, 8, 3, 9},
            {3, 7, 2, 9, 8, 6, 5, 4, 1}
    };

    int visibleBoard[9][9];

public:
    Sudoku(){
        generateBoard();
    }

    void generateBoard();

    void getVisibleBoard(int sentBoard[9][9]);

    bool solvable();
    bool solved();
    void solve();

    void addNumber(int row, int column, int number);
};

class WrongNumberException : public exception {
};

