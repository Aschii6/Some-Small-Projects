#include <QApplication>
#include "Repo.h"
#include "Validator.h"
#include "Service.h"
#include "Gui.h"

// Melodii 2

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(nullptr));
    Repo repo("melodii.txt");
    Service service(repo);
    Gui gui(service);
    gui.show();
    return a.exec();
}
