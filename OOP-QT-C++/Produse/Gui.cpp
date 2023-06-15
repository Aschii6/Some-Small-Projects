//
// Created by Daniel on 15-Jun-23.
//

#include "Gui.h"

void Gui::addComps() {
    setLayout(main);
    main->addLayout(stanga);
    main->addLayout(dreapta);

    form->addRow("Id", lineId);
    form->addRow("Nume", lineNume);
    form->addRow("Tip", lineTip);
    form->addRow("Pret", linePret);

    stanga->addLayout(form);
    stanga->addWidget(slider);
    stanga->addWidget(btnAdd);

    dreapta->addWidget(tv);
    tv->setModel(model);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Gui::connectSignals() {
    QObject::connect(slider, &QSlider::valueChanged, [this](){
        auto val = slider->value();
        model->setNr(val);
    });

    QObject::connect(btnAdd, &QPushButton::clicked, [this](){
        auto id = lineId->text().toInt();
        lineId->clear();
        auto nume = lineNume->text().toStdString();
        lineNume->clear();
        auto tip = lineTip->text().toStdString();
        lineTip->clear();
        auto pret = linePret->text().toDouble();
        linePret->clear();

        try {
            service.addProdus(id, nume, tip, pret);
            model->setProduse(service.getAll());
        } catch (DuplicateIdError&){
            QMessageBox::warning(this, "Warning", "Duplicate id");
        } catch (ValidError& ve){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
        }
    });
}

void Gui::createSmallGuis() {
    vector<string> tipuri = service.getTipuri();
    for (auto& tip : tipuri){
        auto* small = new smallGui{service, tip};
        small->setMinimumSize(400, 100);
        small->setWindowTitle(QString::fromStdString(tip));
        small->show();
    }
}