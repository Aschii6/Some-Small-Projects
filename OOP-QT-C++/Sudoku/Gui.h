//
// Created by User on 06/07/2023.
//

#pragma once
#include "Sudoku.h"
#include "vector"
#include "qwidget.h"
#include "qpushbutton.h"
#include "qboxlayout.h"
#include "qgridlayout.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "qframe.h"

using namespace std;

class Gui: public QWidget {
private:
    Sudoku& sudoku;

    int selectedNumber = 0;

    vector<vector<QPushButton*>> buttonBoard;
    vector<QPushButton*> numberButtons;

    QGridLayout* gridLayout = new QGridLayout();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* numberLayout = new QHBoxLayout();

    void addComponents();
    void connectSignals();
public:
    Gui(Sudoku& sudoku): sudoku(sudoku) {
        addComponents();
        connectSignals();
    }
};
