//
// Created by Daniel on 14-Jun-23.
//

#include "Gui.h"
#include "qmessagebox.h"

void Gui::addComponents() {
    setLayout(main);
    main->addLayout(sus);
    main->addLayout(mijloc);
    main->addLayout(jos);

    mijloc->addLayout(stanga);
    mijloc->addLayout(dreapta);

    stanga->addLayout(lineEdits);

    lineEdits->addRow("Titlu", lineTitlu);
    lineEdits->addRow("Artist", lineArtist);
    lineEdits->addRow("Gen", lineGen);

    stanga->addWidget(btnAdauga);
    stanga->addWidget(btnSterge);

    dreapta->addWidget(tv);

    tv->setModel(model);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);

    widgetRock->setMinimumHeight(200);
    widgetPop->setMinimumHeight(200);
    widgetFolk->setMinimumHeight(200);
    widgetDisco->setMinimumHeight(200);

    sus->addWidget(widgetPop);
    sus->addWidget(widgetRock);
    jos->addWidget(widgetFolk);
    jos->addWidget(widgetDisco);
}

void Gui::connectSignals() {
    QObject::connect(btnSterge, &QPushButton::clicked, [this](){
       if (tv->selectionModel()->selectedIndexes().isEmpty())
           return;

       int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
       auto cell = model->index(selRow, 0);
       auto id = model->data(cell, Qt::DisplayRole).toString().toInt();

       service.deleteMelodieServ(id);
       model->setMelodii(service.getAllServ());

       widgetRock->repaint(); widgetPop->repaint(); widgetFolk->repaint(); widgetDisco->repaint();
    });

    QObject::connect(btnAdauga, &QPushButton::clicked, [this](){
        string titlu = lineTitlu->text().toStdString();
        lineTitlu->clear();

        string artist = lineArtist->text().toStdString();
        lineArtist->clear();

        string gen = lineGen->text().toStdString();
        lineGen->clear();

        try{
            service.addMelodieServ(titlu, artist, gen);
            model->setMelodii(service.getAllServ());
            widgetRock->repaint(); widgetPop->repaint(); widgetFolk->repaint(); widgetDisco->repaint();
        } catch (ValidError& ve){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
        }
    });
}