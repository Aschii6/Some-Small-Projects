//
// Created by Daniel on 15-Jun-23.
//

#include "Gui.h"
#include "qmessagebox.h"
#include "qpainter.h"
#include <QMouseEvent>

void Gui::addComps() {
    setLayout(main);
    main->addLayout(sus);
    main->addLayout(jos);
    sus->addLayout(st);
    sus->addLayout(dr);

    form->addRow("Id", idLine);
    form->addRow("Denumire", denumireLine);
    form->addRow("Tip", tipLine);
    form->addRow("Numar Roti", nrLine);

    st->addLayout(form);
    st->addWidget(comboBox);
    st->addSpacerItem(new QSpacerItem{0, 30});
    st->addWidget(btnAdd);

    tv->setModel(model);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    dr->addWidget(tv);

    drawWidget->setMinimumHeight(100);
    jos->addWidget(drawWidget);

    comboBox->addItem("");
    for (auto& tip : service.getTipuri())
        comboBox->addItem(QString::fromStdString(tip));
}

void Gui::connectSignals() {
    QObject::connect(comboBox, &QComboBox::currentTextChanged, [this](){
        auto tip = comboBox->currentText().toStdString();
        model->setTipCurent(tip);
    });

    QObject::connect(btnAdd, &QPushButton::clicked, [this](){
        auto id = idLine->text().toInt();
        auto denumire = denumireLine->text().toStdString();
        auto tip = tipLine->text().toStdString();
        auto nr = nrLine->text().toInt();
        idLine->clear();
        denumireLine->clear();
        tipLine->clear();
        nrLine->clear();

        try {
            service.addTractor(id, denumire, tip, nr);
            model->setTractoare(service.getAll());
        } catch (DuplicateIdError&) {
            QMessageBox::warning(this, "Warning", QString("Id deja existent!\n"));
        } catch (ValidError& ve){
            QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
        }
    });

    QObject::connect(tv->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
        auto sel = tv->selectionModel()->selectedIndexes();
        if (sel.isEmpty())
            return;
        auto id = sel.at(0).data().toInt();
        drawWidget->setId(id);
    });
}

void DrawWidget::paintEvent(QPaintEvent *event) {
    auto& tractor = service.searchTractor(id);
    int nr = tractor.getNr();

    QPainter painter{this};

    for (int i = 0; i < nr; ++i) {
        painter.drawEllipse(20 + i * 60, 20, 50, 50);
    }
}

void DrawWidget::mousePressEvent(QMouseEvent* event) {
    QPoint click = event->pos();

    auto& tractor = service.searchTractor(id);
    int nr = tractor.getNr();

    for (int i = 0; i < nr; ++i) {
        QRect circleRect(10 + i * 60, 30, 50, 50);

        if (circleRect.contains(click)) {
            if (nr <= 2)
                return;
            tractor.setNr(nr -2);
            service.updateFile();
            model.setTractoare(service.getAll());
            this->repaint();
            break;
        }
    }
}