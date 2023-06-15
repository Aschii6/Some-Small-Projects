//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Task.h"
#include "QAbstractTableModel"
#include <vector>
#include <algorithm>

using std::vector;

class MyTableModel: public QAbstractTableModel {
private:
    vector<Task> taskuri;

public:
    MyTableModel(vector<Task>& taskuri): taskuri{taskuri} {
        sort(3);
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return taskuri.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 4;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Task task = taskuri[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(task.getId());
                case 1:
                    return QString::fromStdString(task.getDescriere());
                case 2:
                    return QString::number(task.getProgramatori().size());
                case 3:
                    return QString::fromStdString(task.getStare());
                default:
                    break;
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            if (orientation == Qt::Horizontal){
                switch (section) {
                    case 0:
                        return QString("Id");
                    case 1:
                        return QString("Descriere");
                    case 2:
                        return QString("Nr programatori");
                    case 3:
                        return QString("Stare");
                    default:
                        break;
                }
            } else if (orientation == Qt::Vertical)
                return QString::number(section);
        }
        return QVariant();
    }

    void sort(int column, Qt::SortOrder = Qt::AscendingOrder) override {
        std::sort(taskuri.begin(), taskuri.end(), [](const Task& t1, const Task& t2){
            return t1.getStare() > t2.getStare();
        });
    }

    void setTaskuri(const vector<Task>& taskuri){
        this->taskuri = taskuri;
        sort(3);

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }
};