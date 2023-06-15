//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Produs.h"
#include "QAbstractTableModel"
#include "qcolor.h"

class MyTableModel: public QAbstractTableModel {
private:
    vector<Produs> produse;
    int nr = 0;
public:
    MyTableModel(vector<Produs>& produse): produse{produse} {
        sort(3);
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return produse.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 5;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Produs produs = produse[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(produs.getId());
                case 1:
                    return QString::fromStdString(produs.getNume());
                case 2:
                    return QString::fromStdString(produs.getTip());
                case 3:
                    return QString::number(produs.getPret());
                case 4:{
                    int nr = 0;
                    for (auto ch : produs.getNume())
                        if (strchr("aeiouAEIOU", ch) != nullptr)
                            nr++;
                    return QString::number(nr);
                }
                default:
                    break;
            }
        }
        if (role == Qt::BackgroundRole){
            Produs produs = produse[index.row()];
            if (produs.getPret() <= nr){
                QColor color(255, 0, 0, 190);
                return color;
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
                        return QString("Nume");
                    case 2:
                        return QString("Tip");
                    case 3:
                        return QString("Pret");
                    case 4:
                        return QString("Nr vocale nume");
                    default:
                        break;
                }
            } else if (orientation == Qt::Vertical)
                return QString::number(section);
        }
        return QVariant();
    }

    void sort(int column, Qt::SortOrder = Qt::AscendingOrder) override {
        std::sort(produse.begin(), produse.end(), [](const Produs& p1, const Produs& p2){
            return p1.getPret() > p2.getPret();
        });
    }

    void setProduse(const vector<Produs>& produse){
        this->produse = produse;
        sort(3);

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }

    void setNr(int nrNou){
        nr = nrNou;
        emit layoutChanged();
    }
};
