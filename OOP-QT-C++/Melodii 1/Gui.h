//
// Created by Daniel on 13-Jun-23.
//

#pragma once
#include "Service.h"
#include "qlayout.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qpainter.h"
#include "MyTableModel.h"

class DrawWidget: public QWidget{
private:
    Service& service;
public:
    DrawWidget(Service& service): service{service} {}

    void paintEvent(QPaintEvent *event) override;
};

class Gui: public QWidget{
private:
    Service& service;

    QHBoxLayout* lyMain = new QHBoxLayout;
    QVBoxLayout* lySt = new QVBoxLayout;
    QHBoxLayout* lyDr = new QHBoxLayout;

    MyTableModel* model = new MyTableModel{service.getAllServ()};
    QTableView* tv = new QTableView;

    QLineEdit* lineEdit = new QLineEdit;

    QPushButton* btnDelete = new QPushButton{"&Delete"};
    QPushButton* btnUpdate = new QPushButton{"&Update"};

    QSlider* slider = new QSlider{Qt::Horizontal};

    DrawWidget* drawWidget = new DrawWidget{service};

    void addComponents();
    void connectSignals();
public:
    Gui(Service& service): service{service} {
        addComponents();
        connectSignals();
    }
};