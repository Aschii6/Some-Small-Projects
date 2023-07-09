#include <QApplication>
#include "GraphicsGui.h"
#include "Sudoku.h"
#include "QPushButton"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(NULL));

    Sudoku sudoku;
    GraphicsGui gui(sudoku);
    gui.show();

    return QApplication::exec();
}
