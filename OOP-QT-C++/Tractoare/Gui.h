//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Service.h"
#include "MyTableModel.h"
#include "qtableview.h"
#include "qwidget.h"
#include "qlineedit.h"
#include "qlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qcombobox.h"

class DrawWidget: public QWidget{
private:
    Service& service;
    MyTableModel& model;
    int id;
public:
    DrawWidget(Service& service, MyTableModel& model): service{service}, model{model} {}

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void setId(int id){
        this->id = id;
        this->repaint();
    }
};

class Gui: public QWidget{
private:
    Service& service;

    MyTableModel* model = new MyTableModel{service.getAll()};
    QTableView* tv = new QTableView;

    QVBoxLayout* main = new QVBoxLayout;
    QHBoxLayout* sus = new QHBoxLayout;
    QHBoxLayout* jos = new QHBoxLayout;
    QVBoxLayout* st = new QVBoxLayout;
    QVBoxLayout* dr = new QVBoxLayout;
    QFormLayout* form = new QFormLayout;

    QLineEdit* idLine = new QLineEdit;
    QLineEdit* denumireLine = new QLineEdit;
    QLineEdit* tipLine = new QLineEdit;
    QLineEdit* nrLine = new QLineEdit;

    QPushButton* btnAdd = new QPushButton{"Add"};
    QComboBox* comboBox = new QComboBox;

    DrawWidget* drawWidget = new DrawWidget{service, *model};

    void addComps();
    void connectSignals();
public:
    Gui(Service& service): service(service){
        addComps();
        connectSignals();
    }
};