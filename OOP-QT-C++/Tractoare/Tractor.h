//
// Created by Daniel on 15-Jun-23.
//

#pragma once

#include <string>

using namespace std;

class Tractor {
private:
    int id, nr;
    string denumire, tip;
public:
    Tractor(int id, string denumire, string tip, int nr): id(id), denumire(denumire), tip(tip), nr(nr) {}

    int getId(){
        return id;
    }
    string getDenumire() const{
        return denumire;
    }
    string getTip() const{
        return tip;
    }
    int getNr(){
        return nr;
    }
    void setNr(int nrNou){
        nr = nrNou;
    }
};