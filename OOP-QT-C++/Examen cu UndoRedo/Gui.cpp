//
// Created by Daniel on 19-Jun-23.
//

#include "Gui.h"
#include "qdebug.h"
#include "qmessagebox.h"

void Gui::addComps() {
    setLayout(mainLy);

    setMinimumSize(660,700);

    mainLy->addLayout(stLy);
    mainLy->addLayout(drLy);

    stLy->addWidget(stergeBtn);
    stLy->addWidget(intinerireBtn);
    stLy->addWidget(imbatranireBtn);
    stLy->addWidget(undoBtn);
    stLy->addWidget(redoBtn);

    tv->setModel(model);
    drLy->addWidget(tv);

    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Gui::connectSignals() {
    QObject::connect(intinerireBtn, &QPushButton::clicked, [this](){
        try{
            service.intinerire();
            model->setStudenti(service.getAll());
        } catch (IntinerireError& ie){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ie.getMsg()));
        }
    });

    QObject::connect(imbatranireBtn, &QPushButton::clicked, [this](){
        service.imbatranire();
        model->setStudenti(service.getAll());
    });

    QObject::connect(stergeBtn, &QPushButton::clicked, [this](){
        if (tv->selectionModel()->selectedIndexes().isEmpty())
            return;

        auto sel = tv->selectionModel()->selectedIndexes();

        for (int i = 0; i < sel.size() ; i += 4){
            int selRow = tv->selectionModel()->selectedIndexes().at(i).row();
            auto cell = tv->model()->index(selRow, 0);
            auto id = tv->model()->data(cell, Qt::DisplayRole).toInt();
            service.stergeStudent(id);
        }
        model->setStudenti(service.getAll());
    });

    QObject::connect(undoBtn, &QPushButton::clicked, [this](){
       try{
           service.undo();
           model->setStudenti(service.getAll());
       } catch (UndoRedoError& ure){
           QMessageBox::warning(this, "Warning", QString::fromStdString(ure.getMsg()));
       }
    });

    QObject::connect(redoBtn, &QPushButton::clicked, [this](){
       try{
           service.redo();
           model->setStudenti(service.getAll());
       } catch (UndoRedoError& ure){
           QMessageBox::warning(this, "Warning", QString::fromStdString(ure.getMsg()));
       }
    });
}