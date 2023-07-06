//
// Created by User on 06/07/2023.
//

#include "Sudoku.h"
#include "random"

void Sudoku::generateBoard() {
    // Permutations on the rows/columns of the same block

    int noOfPermutations = rand() % 10 + 5;

    for (int i = 0; i < noOfPermutations; i++) {
        int block = rand() % 3;

        int firstRow = rand() % 3;
        int secondRow = rand() % 3;

        if (firstRow == secondRow) {
            continue;
        }
//
        for (int j = 0; j < 9; j++) {
            int aux = correctBoard[firstRow + block * 3][j];
            correctBoard[firstRow + block * 3][j] = correctBoard[secondRow + block * 3][j];
            correctBoard[secondRow + block * 3][j] = aux;
        }

        int firstColumn = rand() % 3;
        int secondColumn = rand() % 3;

        if (firstColumn == secondColumn) {
            continue;
        }

        for (int j = 0; j < 9; j++) {
            int aux = correctBoard[j][firstColumn + block * 3];
            correctBoard[j][firstColumn + block * 3] = correctBoard[j][secondColumn + block * 3];
            correctBoard[j][secondColumn + block * 3] = aux;
        }
    }

    // Now we exchange some numbers

    int noOfExchanges = rand() % 4 + 2;

    for (int i = 0; i < noOfExchanges; i++)
    {
        int firstNumber = rand() % 9 + 1;
        int secondNumber = rand() % 9 + 1;

        if (firstNumber == secondNumber) {
            continue;
        }

        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (correctBoard[j][k] == firstNumber) {
                    correctBoard[j][k] = secondNumber;
                }
                else if (correctBoard[j][k] == secondNumber) {
                    correctBoard[j][k] = firstNumber;
                }
            }
        }
    }

    // Now we generate the visible board
    for (int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            visibleBoard[i][j] = correctBoard[i][j];

    // We remove pairs of transposed cells

    int noOfRemovals = rand() % 23;
    while (noOfRemovals < 18)
        noOfRemovals = rand() % 23;

    int removedCells = 0;

    while (removedCells < noOfRemovals) {
        int row = rand() % 9;
        int column = rand() % 9;

        int val1 = visibleBoard[row][column];
        int val2 = visibleBoard[9-row][9-column];

        if (val1 != 0 && val2 != 0) {
            visibleBoard[row][column] = 0;
            visibleBoard[8 - row][8 - column] = 0;
            removedCells++;

            if (!solvable()) {
                visibleBoard[row][column] = val1;
                visibleBoard[8 - row][8 - column] = val2;
                removedCells--;
            }
        }
    }
}


void Sudoku::getVisibleBoard(int receivedBoard[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            receivedBoard[i][j] = visibleBoard[i][j];
        }
    }
}


/// <summary>
/// Not implemented yet
/// </summary>
/// <returns>
/// bool
/// </returns>
bool Sudoku::solvable() {
    return true;
}


bool Sudoku::solved() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (visibleBoard[i][j] != correctBoard[i][j])
                return false;
    return true;
}


/// <summary>
/// Not implemented yet
/// </summary>
void Sudoku::solve() {

}


void Sudoku::addNumber(int row, int column, int number) {
    if (correctBoard[row][column] != number)
        throw WrongNumberException();

    visibleBoard[row][column] = number;
}