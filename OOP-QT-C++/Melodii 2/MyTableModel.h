//
// Created by Daniel on 14-Jun-23.
//

#pragma once

#include "qtableview.h"
#include "Melodie.h"
#include "algorithm"

using std::vector;


class MyModel: public QAbstractTableModel {
private:
    vector<Melodie> melodii;
public:
    MyModel(const vector<Melodie>& melodii): melodii{melodii} {
        sort(2);
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 6;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Melodie m = melodii[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(m.getId());
                case 1:
                    return QString::fromStdString(m.getTitlu());
                case 2:
                    return QString::fromStdString(m.getArtist());
                case 3:
                    return QString::fromStdString(m.getGen());
                case 4:{
                    int nr = 0;
                    for (auto& mel : melodii)
                        if (mel.getArtist() == m.getArtist())
                            nr++;
                    return QString::number(nr);
                }
                case 5:{
                    int nr = 0;
                    for (auto mel : melodii)
                        if (mel.getGen() == m.getGen())
                            nr++;
                    return QString::number(nr);
                }
                default:
                    break;
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0:
                        return QString("Id");
                    case 1:
                        return QString("Tilu");
                    case 2:
                        return QString("Artist");
                    case 3:
                        return QString("Gen");
                    case 4:
                        return "Acelasi artist";
                    case 5:
                        return "Acelasi gen";
                    default:
                        break;
                }
            }
            else if (orientation == Qt::Vertical) {
                return QString::number(section);
            }
        }
        return QVariant();
    }

    void sort(int column, Qt::SortOrder = Qt::AscendingOrder) override{
        std::sort(melodii.begin(), melodii.end(), [](const Melodie m1, const Melodie& m2) {
            return m1.getArtist() < m2.getArtist();
        });
    }

    void setMelodii(const vector<Melodie>& melodii){
        this->melodii = melodii;
        sort(2);

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }
};