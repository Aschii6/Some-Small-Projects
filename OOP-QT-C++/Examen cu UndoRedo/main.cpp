#include <QApplication>
#include "Teste.h"
#include "Repo.h"
#include "Service.h"
#include "Gui.h"

int main(int argc, char *argv[]) {
    allTeste();
    QApplication a(argc, argv);
    Repo repo("studenti.txt");
    Service service(repo);
    Gui gui(service);
    gui.show();
    return QApplication::exec();
}
