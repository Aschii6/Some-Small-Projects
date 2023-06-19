//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include "vector"
#include "Student.h"
#include "algorithm"
#include "QAbstractTableModel"
#include "qcolor.h"

using namespace std;

class MyTableModel : public QAbstractTableModel{
private:
    vector<Student> studenti;
public:
    /**
     * constructor cu sortare
     * @param st vector<Student>&
     */
    MyTableModel(vector<Student>& st): studenti(st) {
        sort();
    }

    /**
     * returneaza nr de linii
     * @param parent
     * @return rez - int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return studenti.size();
    }

    /**
     * returneaza nr de coloane
     * @param parent
     * @return rez - int (4)
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 4;
    }

    /**
     * functia de data pentru model
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            Student st = studenti[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(st.getId());
                case 1:
                    return QString::fromStdString(st.getNume());
                case 2:
                    return QString::number(st.getVarsta());
                case 3:
                    return QString::fromStdString(st.getFacultate());
                default:
                    break;
            }
        }
        if (role == Qt::BackgroundRole){
            Student st = studenti[index.row()];
            if (st.getFacultate() == "mate")
                return QColor(255, 0, 0, 150);
            if (st.getFacultate() == "info")
                return QColor(0, 255, 0, 150);
            if (st.getFacultate() == "mate-info")
                return QColor(0, 0, 255, 150);
            if (st.getFacultate() == "ai")
                return QColor(127, 0, 127, 150);
        }
        return QVariant();
    }

    /**
     * functie de sortare pentru studenti
     */
    void sort() {
        std::sort(studenti.begin(),studenti.end(),[](const Student& s1, const Student& s2){
            return s1.getVarsta() < s2.getVarsta();
        });
    }

    /**
     * setStudenti
     * @param st vector<Student>
     */
    void setStudenti(vector<Student>& st){
        studenti = st;
        sort();
        emit layoutChanged();
    }

    /**
     * Titlurile coloanelor
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override{
        if (role == Qt::DisplayRole){
            if (orientation == Qt::Horizontal){
                switch (section) {
                    case 0:
                        return QString("Id");
                    case 1:
                        return QString("Nume");
                    case 2:
                        return QString("Varsta");
                    case 3:
                        return QString("Facultate");
                    default:
                        break;
                }
            } else if (orientation == Qt::Vertical)
                return QString::number(section);
        }
        return QVariant();
    }
};
