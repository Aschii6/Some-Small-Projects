//
// Created by Daniel on 13-Jun-23.
//

#pragma once
#include "qtableview.h"
#include "Melodie.h"

using std::vector;

class MyTableModel: public QAbstractTableModel {
private:
    vector<Melodie> melodii;
public:
    MyTableModel(const vector<Melodie>& melodii): melodii{melodii} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole){
            Melodie m = melodii[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(m.getId());
                case 1:
                    return QString::fromStdString(m.getTitlu());
                case 2:
                    return QString::fromStdString(m.getArtist());
                case 3:
                    return QString::number(m.getRank());
                case 4:{
                    int nr = 0;
                    for (auto& mel : melodii){
                        if (mel.getRank() == m.getRank())
                            nr++;
                    }
                    return nr;
                }
                default:
                    break;
            }
        }
        /*if (role == Qt::BackgroundRole){
            if (index.row()%2==0)
                return QColor(Qt::yellow);
            else
                return QColor(Qt::lightGray);
        }
        if (role == Qt::ForegroundRole){
            return QColor(Qt::darkGreen);
        }
        if (role == Qt::FontRole){
            QFont f;
            f.setItalic(index.row()%2==1);
            f.setBold(index.row()%2==0);
            f.setStyleHint(QFont::Fantasy);
            return f;
        }*/
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
                        return QString("Rank");
                    case 4:
                        return "Nr";
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

    void setMelodii(const vector<Melodie>& melodii) {
        this->melodii = melodii;

        sort(3);

        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override {
        std::sort(melodii.begin(), melodii.end(), [](const Melodie& m1, const Melodie& m2) {
            return m1.getRank() > m2.getRank();
        });
        // aici nu trebuie, ca fac sortarea in setCarti
        // emit layoutChanged();
    }

    /*Permite editarea casutelor, dar mai trebuie un setData sa se si modifice
    Qt::ItemFlags flags(const QModelIndex& index) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }*/
};