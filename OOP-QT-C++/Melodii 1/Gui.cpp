//
// Created by Daniel on 13-Jun-23.
//

#include "Gui.h"
#include "qlabel.h"
#include "qmessagebox.h"

void Gui::addComponents() {
    setLayout(lyMain);
    lyMain->addLayout(lySt);
    lyMain->addLayout(lyDr);

    tv->setModel(model);
    tv->sortByColumn(3,Qt::DescendingOrder);

    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);

    lySt->addWidget(lineEdit);

    slider->setRange(0,10);
    lySt->addWidget(slider);

    lySt->addWidget(btnUpdate);
    lySt->addWidget(btnDelete);

    lyDr->addWidget(tv);

    lySt->addWidget(drawWidget);
}

void Gui::connectSignals() {
    /*Does the trick for some stuff*/
    QObject::connect(tv->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
       if (tv->selectionModel()->selectedIndexes().isEmpty()){
           lineEdit->setText("");
           return;
       }
       int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
       auto cell = tv->model()->index(selRow, 1);
       auto value = tv->model()->data(cell, Qt::DisplayRole).toString();
       lineEdit->setText(value);
    });

    QObject::connect(btnDelete, &QPushButton::clicked, [this](){
        if (tv->selectionModel()->selectedIndexes().isEmpty()){
            return;
        }
        int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
        auto cell = tv->model()->index(selRow, 0);
        auto value = tv->model()->data(cell, Qt::DisplayRole).toString();

        try {
            service.stergeMelodie(value.toInt());
            model->setMelodii(service.getAllServ());
            drawWidget->repaint();
        } catch (StergeError&){
            QMessageBox::warning(this, "Warning","Nu se poate sterge ultima melodie a artistului");
        }
    });

    QObject::connect(btnUpdate, &QPushButton::clicked, [this](){
        if (tv->selectionModel()->selectedIndexes().isEmpty()){
            return;
        }
        int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
        auto cell = tv->model()->index(selRow, 0);
        auto id = tv->model()->data(cell, Qt::DisplayRole).toString().toInt();

        Melodie& mel = service.cautaMelodie(id);

        int valueSlider = slider->value();
        mel.setRank(valueSlider);

        auto titluNou = lineEdit->text().toStdString();
        if (titluNou.empty())
            return;

        mel.setTitlu(titluNou);

        service.updateFile();

        model->setMelodii(service.getAllServ());
        drawWidget->repaint();
    });
}

void DrawWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    std::vector<int> raport = service.raportRank();

    for (int i = 0; i < 11; ++i) {
        painter.drawRect(40*(i+1),30,30,30*raport[i]);
    }
}