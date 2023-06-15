//
// Created by Daniel on 14-Jun-23.
//

#pragma once
#include "Service.h"
#include "MyTableModel.h"
#include "qwidget.h"
#include "qlayout.h"
#include "qlineedit.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qpainter.h"
#include "qlistview.h"


class DrawWidget: public QWidget {
private:
    Service& service;
    string gen;
public:
    DrawWidget(Service& service, string gen): service{service}, gen{gen} {}

    void paintEvent(QPaintEvent* event) override {
        QPainter painter{this};

        vector<Melodie> melodii = service.getAllServ();

        int x = 25;

        for (auto& mel : melodii)
            if (mel.getGen() == gen){
                painter.drawEllipse(100-x/2,100-x/2,x,x);
                x += 20;
            }
    }
};


class Gui: public QWidget {
private:
    Service& service;

    QVBoxLayout* main = new QVBoxLayout;

    QHBoxLayout* sus = new QHBoxLayout;
    QHBoxLayout* jos = new QHBoxLayout;
    QHBoxLayout* mijloc = new QHBoxLayout;

    QVBoxLayout* stanga = new QVBoxLayout;
    QVBoxLayout* dreapta = new QVBoxLayout;

    QFormLayout* lineEdits = new QFormLayout;

    MyModel* model = new MyModel{service.getAllServ()};

//    QTableView* tv = new QTableView;
    QListView* tv = new QListView;

    QLineEdit* lineTitlu = new QLineEdit;
    QLineEdit* lineArtist = new QLineEdit;
    QLineEdit* lineGen = new QLineEdit;

    QPushButton* btnAdauga = new QPushButton{"Adauga"};
    QPushButton* btnSterge = new QPushButton{"Sterge"};

    DrawWidget* widgetRock = new DrawWidget{service, "rock"};
    DrawWidget* widgetPop = new DrawWidget{service, "pop"};
    DrawWidget* widgetFolk = new DrawWidget{service, "folk"};
    DrawWidget* widgetDisco = new DrawWidget{service, "disco"};

    void addComponents();
    void connectSignals();
public:
    Gui(Service& service): service{service}{
        addComponents();
        connectSignals();
    }
};
