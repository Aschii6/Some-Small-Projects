//
// Created by User on 08/07/2023.
//

#pragma once
#include "QGraphicsView"
#include "Sudoku.h"
#include "Stuff.h"
#include "vector"

using namespace std;

class GraphicsGui:public QGraphicsView {
private:
    Sudoku& sudoku;

    int selectedNumber = 0;
    int mistakes = 0;

    StartScene* startScene = new StartScene;
    PlayScene* playScene = new PlayScene;
    EndScene* endScene = new EndScene;

    // For the start scene
    Button* startButton = new Button(200, 325, 200, 60);
    Button* quitButton = new Button(200, 450, 200, 60);

    // For the play scene
    vector<Button*> numberButtons;
    vector<Button*> sudokuSquares;

    QGraphicsTextItem* mistakesText = new QGraphicsTextItem;

    // For the end scene

    QGraphicsTextItem* endText = new QGraphicsTextItem;

    void setup();
    void connectSignals();

public:
    GraphicsGui(Sudoku& sudoku): sudoku(sudoku) {
        setup();
        connectSignals();
    }
};
