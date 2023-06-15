//
// Created by Daniel on 15-Jun-23.
//

#pragma once

#include <QObject>
#include "Validator.h"
#include "Repo.h"
#include "algorithm"

class Service{
private:
    Repo& repo;

public:
    explicit Service(Repo& repo): repo(repo) {}

    vector<Tractor>& getAll(){
        return repo.getAll();
    }

    void addTractor(int id, string& denumire, string& tip, int nr){
        Tractor tr(id, denumire, tip, nr);
        Validator::validate(tr);
        repo.addTractor(tr);
    }

    void updateFile(){
        repo.write();
    }

    vector<string> getTipuri(){
        vector<string> tipuri;
        for (auto& tr : repo.getAll())
            if (find(tipuri.begin(), tipuri.end(), tr.getTip()) == tipuri.end())
                tipuri.push_back(tr.getTip());
        return tipuri;
    }

    Tractor& searchTractor(int id){
        return repo.searchTractor(id);
    }
};
