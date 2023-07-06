#include <QApplication>
#include "Sudoku.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(NULL));
    Sudoku sudoku;
    Gui gui(sudoku);
    gui.show();
    return a.exec();
}
