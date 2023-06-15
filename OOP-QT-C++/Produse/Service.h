//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Repo.h"
#include "Validator.h"
#include "Observer.h"

class Service: public Observable{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo(repo) {}

    vector<Produs>& getAll(){
        return repo.getAll();
    }

    void addProdus(int id, string& nume, string& tip, double pret);

    int getNrTip(string& tip){
        int nr = 0;
        for (auto& produs : repo.getAll()){
            if (produs.getTip() == tip)
                nr++;
        }
        return nr;
    }

    vector<string> getTipuri(){
        vector<string> rez;
        for (auto& produs : repo.getAll()){
            bool ok = true;
            for (auto& tip : rez){
                if (tip == produs.getTip())
                    ok = false;
            }
            if (ok)
                rez.push_back(produs.getTip());
        }
        return rez;
    }
};
