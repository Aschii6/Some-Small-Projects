//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Service.h"
#include "MyTableModel.h"
#include "Observer.h"
#include "qtableview.h"
#include "qwidget.h"
#include "qlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qmessagebox.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qslider.h"

class Gui: public QWidget {
private:
    Service& service;

    QHBoxLayout* main = new QHBoxLayout;
    QVBoxLayout* stanga = new QVBoxLayout;
    QVBoxLayout* dreapta = new QVBoxLayout;

    QFormLayout* form = new QFormLayout;

    QLineEdit* lineId = new QLineEdit;
    QLineEdit* lineNume = new QLineEdit;
    QLineEdit* lineTip = new QLineEdit;
    QLineEdit* linePret = new QLineEdit;

    QSlider* slider = new QSlider(Qt::Horizontal);

    QPushButton* btnAdd = new QPushButton{"Add"};

    MyTableModel* model = new MyTableModel(service.getAll());

    QTableView* tv = new QTableView;

    void addComps();
    void connectSignals();
    void createSmallGuis();
public:
    Gui(Service& service): service(service) {
        addComps();
        connectSignals();
        createSmallGuis();
    }
};

class smallGui: public QWidget, public Observer {
private:
    Service& service;
    string tip;

    QVBoxLayout* main = new QVBoxLayout;
    QLabel* label = new QLabel;

    void addComps() {
        setLayout(main);
        label->setText(QString::number(service.getNrTip(tip)));
        main->addWidget(label);
    }
public:
    smallGui(Service& service, string tip): service(service), tip(tip) {
        service.addObserver(this);
        addComps();
    }

    void update() override {
        auto nr = service.getNrTip(tip);
        label->setText(QString::number(nr));
    }

    ~smallGui() override {
        service.removeObserver(this);
    }
};