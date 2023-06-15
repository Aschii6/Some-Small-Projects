//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Service.h"
#include "Observer.h"
#include "MyTableModel.h"
#include "qwidget.h"
#include "qtableview.h"
#include "qlayout.h"
#include "qformlayout.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qlistwidget.h"

class Gui: public QWidget, public Observer{
private:
    Service& service;

    MyTableModel* model = new MyTableModel{service.getAll()};
    QTableView* tv = new QTableView;

    QHBoxLayout* lyMain = new QHBoxLayout;
    QVBoxLayout* lySt = new QVBoxLayout;
    QVBoxLayout* lyDr = new QVBoxLayout;

    QFormLayout* lyForm = new QFormLayout;

    QLineEdit* lineId = new QLineEdit;
    QLineEdit* lineDescriere = new QLineEdit;
    QLineEdit* lineProgramatori = new QLineEdit;
    QLineEdit* lineStare = new QLineEdit;

    QLineEdit* searchProgramator = new QLineEdit;

    QPushButton* btnAdd = new QPushButton{"Add"};

    void addComponents();
    void connectSignals();
public:
    Gui(Service& service): service{service}{
        service.addObserver(this);
        addComponents();
        connectSignals();
    }

    void update() override{
        model->setTaskuri(service.getAll());
    }

    ~Gui() override{
        service.removeObserver(this);
    }
};

class GuiStare: public QWidget, public Observer{
private:
    Service& service;
    std::string stare;

    QListWidget* lst = new QListWidget;

    QHBoxLayout* ly = new QHBoxLayout;
    QVBoxLayout* st = new QVBoxLayout;
    QVBoxLayout* dr = new QVBoxLayout;

    QPushButton* btnToOpen = new QPushButton{"To Open"};
    QPushButton* btnToInProgress = new QPushButton{"To In Progress"};
    QPushButton* btnToClosed = new QPushButton{"To Closed"};

    void addComponents(){
        setLayout(ly);
        ly->addLayout(st);
        ly->addLayout(dr);

        dr->addWidget(lst);
        st->addWidget(btnToOpen);
        st->addWidget(btnToInProgress);
        st->addWidget(btnToClosed);

        lst->setSelectionBehavior(QAbstractItemView::SelectRows);
        lst->setSelectionMode(QAbstractItemView::SingleSelection);
    }
    void connectSignals(){
        QObject::connect(btnToOpen, &QPushButton::clicked, [this](){
            if (lst->selectedItems().empty()){
                return;
            }
            auto id = lst->currentItem()->text().split(",")[0].toInt();
            Task& task = service.getTask(id);
            task.setStare("open");
            service.updateFile();
        });

        QObject::connect(btnToInProgress, &QPushButton::clicked, [this](){
            if (lst->selectedItems().empty()){
                return;
            }
            auto id = lst->currentItem()->text().split(",")[0].toInt();
            Task& task = service.getTask(id);
            task.setStare("inprogress");
            service.updateFile();
        });

        QObject::connect(btnToClosed, &QPushButton::clicked, [this](){
            if (lst->selectedItems().empty()){
                return;
            }
            auto id = lst->currentItem()->text().split(",")[0].toInt();
            Task& task = service.getTask(id);
            task.setStare("closed");
            service.updateFile();
        });
    }
    void showLst(){
        lst->clear();
        for (auto task : service.getAll()){
            if (task.getStare() == stare){
                lst->addItem(QString::number(task.getId()) + "," + QString::fromStdString(task.getDescriere())
                + "," + QString::number(task.getProgramatori().size()) + ',' + QString::fromStdString(task.getStare()));
            }
        }
    }
public:
    GuiStare(Service& service, string stare): service{service}, stare{std::move(stare)} {
        service.addObserver(this);
        addComponents();
        connectSignals();
        showLst();
    }

    void update() override{
        showLst();
    }

    ~GuiStare(){
        service.removeObserver(this);
    }
};