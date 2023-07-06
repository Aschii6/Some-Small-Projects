//
// Created by User on 06/07/2023.
//

#include "Gui.h"

void Gui::addComponents() {
    setWindowTitle("Sudoku");
    setFixedSize(700, 800);

    setLayout(mainLayout);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(numberLayout);

//    int board[9][9];
//    sudoku.getVisibleBoard(board);
//
//    buttonBoard.resize(9);
//    for (int i = 0; i < 9; ++i) {
//        buttonBoard[i].resize(9);
//        for (int j = 0; j < 9; ++j) {
//            auto* btn = new QPushButton("ඞ");
//            btn->setFixedSize(60, 60);
//            btn->setStyleSheet("background-color: white");
//            btn->setFont(QFont("Times", 20, QFont::Bold));
//
//            int number = board[i][j];
//            if (number){
//                btn->setText(QString::number(number));
//            }
//
//            gridLayout->addWidget(btn, i, j);
//            buttonBoard[i][j] = btn;
//        }
//    }

    int board[9][9];
    sudoku.getVisibleBoard(board);

    buttonBoard.resize(9);
    for (int i = 0; i < 9; ++i) {
        buttonBoard[i].resize(9);
        for (int j = 0; j < 9; ++j) {
            auto* btn = new QPushButton("ඞ");
            btn->setFixedSize(60, 60);
            btn->setStyleSheet("background-color: white");
            btn->setFont(QFont("Times", 20, QFont::Bold));

            int number = board[i][j];
            if (number){
                btn->setText(QString::number(number));
            }

            gridLayout->addWidget(btn, i * 2, j * 2);
            buttonBoard[i][j] = btn;

            // Add vertical lines between buttons
            if (j < 8) {
                QFrame* verticalLine = new QFrame();
                verticalLine->setFrameShape(QFrame::VLine);
                if ((j + 1) % 3 == 0) {
                    verticalLine->setLineWidth(3); // Make every third vertical line thicker
                }
                gridLayout->addWidget(verticalLine, i * 2, j * 2 + 1);
            }
        }

        // Add horizontal lines between rows
        if (i < 8) {
            QFrame* horizontalLine = new QFrame();
            horizontalLine->setFrameShape(QFrame::HLine);
            if ((i + 1) % 3 == 0) {
                horizontalLine->setLineWidth(3); // Make every third horizontal line thicker
            }
            gridLayout->addWidget(horizontalLine, i * 2 + 1, 0, 1, 19); // Spanning 19 columns
        }
    }

    numberButtons.resize(9);
    for (int i = 0; i < 9; ++i) {
        auto* btn = new QPushButton(QString::number(i + 1));
        btn->setFixedSize(60, 60);
        btn->setStyleSheet("background-color: white");
        btn->setFont(QFont("Times", 20, QFont::Bold));
        numberLayout->addWidget(btn);
        numberButtons[i] = btn;
    }

    QFrame* horizontalLine = new QFrame();
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setLineWidth(3);
    gridLayout->addWidget(horizontalLine, 17, 0, 1, 19);
}


void Gui::connectSignals() {
    for (int i = 0; i < 9; ++i) {
        auto btn = numberButtons[i];
        QObject::connect(btn, &QPushButton::clicked, [this, btn](){
            for (auto button : numberButtons){
                button->setStyleSheet("background-color: white");
            }
            selectedNumber = btn->text().toInt();
            btn->setStyleSheet("background-color: green");
        });
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            auto btn = buttonBoard[i][j];
            QObject::connect(btn, &QPushButton::clicked, [this, btn, i, j](){
                if (btn->text() != "ඞ")
                    return;
                if (selectedNumber == 0)
                    return;

                try {
                    sudoku.addNumber(i, j, selectedNumber);
                    btn->setText(QString::number(selectedNumber));
                    if (sudoku.solved()){
                        QMessageBox::information(this, "Info", "Congrats!");
                    }
                } catch (WrongNumberException&){
                    QMessageBox::information(this, "Info", "Wrong Number");
                }
            });
        }
    }
}
