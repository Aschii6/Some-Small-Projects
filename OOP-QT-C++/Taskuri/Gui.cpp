//
// Created by Daniel on 15-Jun-23.
//

#include "Gui.h"
#include "qmessagebox.h"

void Gui::addComponents() {
    setLayout(lyMain);
    lyMain->addLayout(lySt);
    lyMain->addLayout(lyDr);

    lySt->addLayout(lyForm);
    lySt->addWidget(btnAdd);

    lyForm->addRow("Id",lineId);
    lyForm->addRow("Descriere",lineDescriere);
    lyForm->addRow("Programatori",lineProgramatori);
    lyForm->addRow("Stare",lineStare);
    lyForm->addRow("Search",searchProgramator);

    lyDr->addWidget(tv);
    tv->setModel(model);

    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);

    auto* stareOpen = new GuiStare{service, "open"};
    auto* stareInProgress = new GuiStare{service, "inprogress"};
    auto* stareClosed = new GuiStare{service, "closed"};

    stareOpen->show();
    stareInProgress->show();
    stareClosed->show();
}

void Gui::connectSignals() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this](){
        auto id = lineId->text().toInt();
        lineId->clear();
        auto descriere = lineDescriere->text().toStdString();
        lineDescriere->clear();
        auto stare = lineStare->text().toStdString();
        lineStare->clear();
        auto program = lineProgramatori->text().toStdString();
        lineProgramatori->clear();

        try {
            service.addTask(id, descriere, stare, program);
            model->setTaskuri(service.getAll());
        } catch (DuplicateIdError&){
            QMessageBox::warning(this, "Warning", "Duplicate id");
        } catch (ValidError& ve){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
        }
    });

    QObject::connect(searchProgramator, &QLineEdit::textEdited, [this](){
       auto filtru = searchProgramator->text().toStdString();

       if (filtru.empty()) {
           model->setTaskuri(service.getAll());
           return;
       }
       model->setTaskuri(service.filter(filtru));
    });
}