//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Repo.h"
#include "Validator.h"

class Service{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo(repo) {}

    vector<Joc>& getAll(){
        return repo.getAll();
    }

    void addJoc(int id, int dim, string& tabla, string& toPlay, string& stare){
        Joc joc(id, dim, tabla, toPlay, stare);
        //Validator::validate(joc);
        repo.addJoc(joc);
    }

    void modifyJoc(int id, int dim, string& tabla, string& toPlay, string& stare){
        Joc joc(id, dim, tabla, toPlay, stare);
        //Validator::validate(joc);
        for (auto& j : repo.getAll())
            if (j.getId() == id){
                j.setDimensiune(dim);
                j.setTabla(tabla);
                j.setToPlay(toPlay);
                j.setStare(stare);
                repo.write();
                return;
            }
    }

    Joc& searchJoc(int id){
        for (auto& j : repo.getAll())
            if (j.getId() == id)
                return j;
    }
};
