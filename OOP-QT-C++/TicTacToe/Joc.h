//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "string"

using namespace std;

class Joc{
private:
    int id, dim;
    string tabla, stare;
    string toPlay;
public:
    Joc(int id, int dim, string tabla, string toPlay, string stare): id(id), dim(dim), tabla(tabla), toPlay(toPlay), stare(stare) {}
    int getId() const{
        return id;
    }
    int getDim() const{
        return dim;
    }
    string getTabla() const{
        return tabla;
    }
    string getToPlay() const{
        return toPlay;
    }
    string getStare() const{
        return stare;
    }

    void setDimensiune(int dim){
        this->dim = dim;
    }
    void setTabla(string tabla){
        this->tabla = tabla;
    }
    void setToPlay(string toPlay){
        this->toPlay = toPlay;
    }
    void setStare(string stare){
        this->stare = stare;
    }
};