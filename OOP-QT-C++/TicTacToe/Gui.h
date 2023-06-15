//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Service.h"
#include "MyTableModel.h"
#include "qtableview.h"
#include "qlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qmessagebox.h"
#include "qlineedit.h"
#include "qgridlayout.h"

class Gui: public QWidget{
private:
    Service& service;

    MyTableModel* model = new MyTableModel{service.getAll()};
    QTableView* tv = new QTableView;

    QHBoxLayout* main = new QHBoxLayout;
    QVBoxLayout* st = new QVBoxLayout;
    QVBoxLayout* dr = new QVBoxLayout;

    QGridLayout* grid = new QGridLayout;

    vector<vector<QPushButton*>> btns;

    QFormLayout* form = new QFormLayout;

    QLineEdit* idLine = new QLineEdit;
    QLineEdit* dimLine = new QLineEdit;
    QLineEdit* tablaLine = new QLineEdit;
    QLineEdit* toPlayLine = new QLineEdit;
    QLineEdit* stareLine = new QLineEdit;

    QPushButton* btnAdd = new QPushButton{"Add"};
    QPushButton* btnModify = new QPushButton{"Modify"};

    void addComps();
    void connectSignals();
public:
    Gui(Service& service): service{service}{
        addComps();
        connectSignals();
    }
};