//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include "Service.h"
#include "MyTableModel.h"
#include "qwidget.h"
#include "qlayout.h"
#include "qpushbutton.h"
#include "qtableview.h"

class Gui: public QWidget{
private:
    Service& service;

    MyTableModel* model = new MyTableModel(service.getAll());
    QTableView* tv = new QTableView;

    QHBoxLayout* mainLy = new QHBoxLayout;

    QVBoxLayout* stLy = new QVBoxLayout;
    QVBoxLayout* drLy = new QVBoxLayout;

    QPushButton* stergeBtn = new QPushButton("Sterge");
    QPushButton* intinerireBtn = new QPushButton("Intinerire");
    QPushButton* imbatranireBtn = new QPushButton("Imbatranire");
    QPushButton* undoBtn = new QPushButton("Undo");
    QPushButton* redoBtn = new QPushButton("Redo");

    void addComps();
    void connectSignals();
public:
    Gui(Service& service): service(service){
        addComps();
        connectSignals();
    }
};