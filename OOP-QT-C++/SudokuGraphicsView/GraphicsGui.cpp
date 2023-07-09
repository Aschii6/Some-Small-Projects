//
// Created by User on 08/07/2023.
//

#include "GraphicsGui.h"
#include "QApplication"

void GraphicsGui::setup() {
    setScene(startScene);

    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    startButton->setText("Start");
    quitButton->setText("Quit");

    startScene->addItem(startButton);
    startScene->addItem(quitButton);

    // For the play scene
    for (int i = 0; i < 9; i++) {
        numberButtons.push_back(new Button(30 + 60 * i, 680, 60, 60));
        numberButtons[i]->setText(QString::number(i + 1));
        playScene->addItem(numberButtons[i]);
    }

    int board[9][9];
    sudoku.getVisibleBoard(board);

    for (int i = 0; i < 81; i++) {
        sudokuSquares.push_back(new Button(30 + 60 * (i % 9), 30 + 60 * (i / 9), 60, 60));
        if (board[i / 9][i % 9] != 0) {
            sudokuSquares[i]->setText(QString::number(board[i / 9][i % 9]));
        }
        playScene->addItem(sudokuSquares[i]);
    }

    mistakesText->setPos(30, 620);
    mistakesText->setPlainText("Mistakes: " + QString::number(mistakes) + "/5");
    mistakesText->setFont(QFont("Times", 16));
    playScene->addItem(mistakesText);

    // For the end scene

    endText->setFont(QFont("Times", 16));
    endText->setPos(200, 400);
    endText->setPlainText("Congrats on the win!");

    endScene->addItem(endText);
}


void GraphicsGui::connectSignals() {
    connect(startButton, &Button::clicked, this, [this] {
        setScene(playScene);
    });

    connect(quitButton, &Button::clicked, this, [this] {
        QApplication::quit();
    });

    for (int i = 0; i < 9; i++) {
        connect(numberButtons[i], &Button::clicked, this, [this, i] {
            for (auto button : numberButtons) {
                button->setColor(Qt::white);
            }
            selectedNumber = i + 1;
            numberButtons[i]->setColor(Qt::green);
        });
    }

    for (int i = 0; i < 81; i++) {
        connect(sudokuSquares[i], &Button::clicked, this, [this, i] {
            if (sudokuSquares[i]->getText() != ""){
                // Some highlighting
                int row = i / 9;
                int column = i % 9;
                for (int j = 0; j < 81; j++){
                    int rowJ = j / 9;
                    int columnJ = j % 9;
                    // condition for same square
                    bool cond = (rowJ / 3 == row / 3 && columnJ / 3 == column / 3);

                    if (sudokuSquares[j]->getText() == sudokuSquares[i]->getText() || rowJ == row || columnJ == column || cond)
                        sudokuSquares[j]->setColor(Qt::lightGray);
                    else
                        sudokuSquares[j]->setColor(Qt::white);
                    sudokuSquares[i]->setColor(Qt::gray);
                }
                return;
            }

            if (selectedNumber == 0)
                return;

            int x = i / 9;
            int y = i % 9;
            try {
                sudoku.addNumber(x, y, selectedNumber);
                sudokuSquares[i]->setText(QString::number(selectedNumber));
            } catch (WrongNumberException&){
                mistakes++;
                if (mistakes >= 5){
                    endText->setPos(240, 400);
                    endText->setPlainText("Game over!");
                    setScene(endScene);
                    return;
                }
                mistakesText->setPlainText("Mistakes: " + QString::number(mistakes) + "/5");
            }
        });
    }
}
