//
// Created by Daniel on 19-Jun-23.
//

#pragma once
#include <utility>
#include "string"

using namespace std;

class Student{
private:
    int id, varsta;
    string nume, facultate;
public:
    /**
     * constructor student
     * @param id int
     * @param nume string
     * @param varsta int
     * @param facultate string
     */
    Student(int id, string nume, int varsta, string facultate): id(id), nume(std::move(nume)), varsta(varsta), facultate(std::move(facultate)) {}

    /**
     * returneaza id
     * @return rez - int
     */
    int getId(){
        return id;
    }

    /**
     * returneaza nume
     * @return rez - string
     */
    string getNume()const{
        return nume;
    }

    /**
     * returneaza varsta
     * @return rez - int
     */
    int getVarsta()const{
        return varsta;
    }

    /**
     * returneaza facultatea
     * @return rez - int
     */
    string getFacultate()const{
        return facultate;
    }

    /**
     * modifica varsta studentului
     * @param varstaNoua int
     */
    void setVarsta(int varstaNoua){
        varsta = varstaNoua;
    }
};
