#include <QApplication>
#include "Repo.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo("jocuri.txt");
    Service service(repo);
    Gui gui(service);
    gui.show();
    return a.exec();
}
