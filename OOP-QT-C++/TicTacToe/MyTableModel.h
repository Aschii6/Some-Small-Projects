//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Joc.h"
#include "vector"
#include "algorithm"
#include "QAbstractTableModel"
#include "qcolor.h"

using namespace std;

class MyTableModel : public QAbstractTableModel{
private:
    vector<Joc> jocuri;
public:
    MyTableModel(vector<Joc>& joc): jocuri(joc) {
        sort();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return jocuri.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Joc j = jocuri[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(j.getId());
                case 1:
                    return QString::number(j.getDim());
                case 2:
                    return QString::fromStdString(j.getTabla());
                case 3:
                    return QString::fromStdString(j.getToPlay());
                case 4:
                    return QString::fromStdString(j.getStare());
                default:
                    break;
            }
        }
        return QVariant();
    }

    void sort() {
        std::sort(jocuri.begin(),jocuri.end(),[](const Joc& j1, const Joc& j2){
            return j1.getStare() > j2.getStare();
        });
    }

    void setJocuri(vector<Joc>& jocuri){
        this->jocuri = jocuri;
        sort();

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            if (orientation == Qt::Horizontal){
                switch (section) {
                    case 0:
                        return QString("Id");
                    case 1:
                        return QString("Dim");
                    case 2:
                        return QString("Tabla");
                    case 3:
                        return QString("To play");
                    case 4:
                        return QString("Stare");
                    default:
                        break;
                }
            } else if (orientation == Qt::Vertical)
                return QString::number(section);
        }
        return QVariant();
    }
};