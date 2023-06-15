//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Tractor.h"
#include "vector"
#include "algorithm"
#include "QAbstractTableModel"
#include "qcolor.h"

using namespace std;

class MyTableModel : public QAbstractTableModel{
private:
    vector<Tractor> tractoare;
    string tipCurent;
public:
    MyTableModel(vector<Tractor>& tr): tractoare(tr) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return tractoare.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Tractor tr = tractoare[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(tr.getId());
                case 1:
                    return QString::fromStdString(tr.getDenumire());
                case 2:
                    return QString::fromStdString(tr.getTip());
                case 3:
                    return QString::number(tr.getNr());
                case 4:{
                    int nr = 0;
                    for (auto& tr1 : tractoare)
                        if (tr1.getTip() == tr.getTip())
                            nr++;
                    return QString::number(nr);
                }
                default:
                    break;
            }
        }
        if (role == Qt::BackgroundRole){
            Tractor tr = tractoare[index.row()];
            if (!tipCurent.empty() && tr.getTip() == tipCurent){
                QColor color(255, 0, 0, 190);
                return color;
            }
        }
        return QVariant();
    }

    void sort() {
        std::sort(tractoare.begin(),tractoare.end(),[](const Tractor& t1, const Tractor& t2){
           return t1.getDenumire() < t1.getDenumire();
        });
    }

    void setTractoare(vector<Tractor>& tr){
        tractoare = tr;
        sort();

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }

    void setTipCurent(string& tip){
        tipCurent = tip;
        emit layoutChanged();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            if (orientation == Qt::Horizontal){
                switch (section) {
                    case 0:
                        return QString("Id");
                    case 1:
                        return QString("Denumire");
                    case 2:
                        return QString("Tip");
                    case 3:
                        return QString("Nr Roti");
                    case 4:
                        return QString("Acelasi tip");
                    default:
                        break;
                }
            } else if (orientation == Qt::Vertical)
                return QString::number(section);
        }
        return QVariant();
    }
};