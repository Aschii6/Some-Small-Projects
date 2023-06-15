//
// Created by Daniel on 15-Jun-23.
//

#include "Gui.h"

void Gui::addComps() {
    setLayout(main);
    main->addLayout(st);
    main->addLayout(dr);

    form->addRow("Id", idLine);
    form->addRow("Dim", dimLine);
    form->addRow("Tabla", tablaLine);
    form->addRow("To Play", toPlayLine);
    form->addRow("Stare", stareLine);

    st->addLayout(form);
    st->addWidget(btnAdd);
    st->addWidget(btnModify);
    st->addLayout(grid);

    tv->setModel(model);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);
    dr->addWidget(tv);

    btns.resize(5);
    for (int i = 0; i < 5; ++i) {
        btns[i].resize(5);
        for (int j = 0; j < 5; ++j) {
            btns[i][j] = new QPushButton{"-"};
            btns[i][j]->setFixedSize(50, 50);
            grid->addWidget(btns[i][j], i, j);
        }
    }
}

void Gui::connectSignals() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this](){
auto id = idLine->text().toInt();
        auto dim = dimLine->text().toInt();
        auto tabla = tablaLine->text().toStdString();
        auto toPlay = toPlayLine->text().toStdString();
        auto stare = stareLine->text().toStdString();
        idLine->clear();
        dimLine->clear();
        tablaLine->clear();
        toPlayLine->clear();
        stareLine->clear();

        try {
            service.addJoc(id, dim, tabla, toPlay, stare);
            model->setJocuri(service.getAll());
        } catch (exception&){
            QMessageBox::warning(this, "Warning", QString("Eroare!(Not handled separately yet)"));
        }
    });

    QObject::connect(btnModify, &QPushButton::clicked, [this](){
        auto id = idLine->text().toInt();
        auto dim = dimLine->text().toInt();
        auto tabla = tablaLine->text().toStdString();
        auto toPlay = toPlayLine->text().toStdString();
        auto stare = stareLine->text().toStdString();
        idLine->clear();
        dimLine->clear();
        tablaLine->clear();
        toPlayLine->clear();
        stareLine->clear();

        try {
            service.modifyJoc(id, dim, tabla, toPlay, stare);
            model->setJocuri(service.getAll());
        } catch (exception&){
            QMessageBox::warning(this, "Warning", QString("Eroare!(Not handled separately yet)"));
        }
    });

    QObject::connect(tv->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
        auto sel = tv->selectionModel()->selectedIndexes();
        if (sel.isEmpty())
            return;

        int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
        auto cell = tv->model()->index(selRow, 0);
        auto value = tv->model()->data(cell, Qt::DisplayRole).toInt();

        Joc joc = service.searchJoc(value);

        int dim = joc.getDim();

        auto tabla = joc.getTabla();
        vector<string> chars;

        for (auto& c : tabla)
            chars.push_back(string{c});

        int k = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i < dim && j < dim){
                    btns[i][j]->setText(QString::fromStdString(chars[k]));
                    ++k;
                }
                else
                    btns[i][j]->setText("#");
            }
        }
    });

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            QObject::connect(btns[i][j], &QPushButton::clicked, [this, i, j](){
                auto sel = tv->selectionModel()->selectedIndexes();
                if (sel.isEmpty())
                    return;

                if (btns[i][j]->text() == "X" || btns[i][j]->text() == "O" || btns[i][j]->text() == "#")
                    return;

                int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
                auto cell = tv->model()->index(selRow, 0);
                auto id = tv->model()->data(cell, Qt::DisplayRole).toInt();

                Joc joc = service.searchJoc(id);

                string toPlay = joc.getToPlay();
                string stare = joc.getStare();
                string tabla = joc.getTabla();
                int dim = joc.getDim();

                if (stare == "terminat")
                    return;

                if (stare == "neinceput")
                    stare = "in derulare";

                vector<string> chars;
                for (auto& c : tabla)
                    chars.push_back(string{c});

                btns[i][j]->setText(QString::fromStdString(toPlay));
                chars[i * dim + j] = toPlay;

                if (toPlay == "X")
                    toPlay = "O";
                else
                    toPlay = "X";

                string newTabla;
                for (auto& c : chars)
                    newTabla += c;

                service.modifyJoc(id, dim, newTabla, toPlay, stare);
                model->setJocuri(service.getAll());
            });
        }
    }
}