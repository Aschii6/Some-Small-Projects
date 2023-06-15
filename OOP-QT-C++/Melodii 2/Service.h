//
// Created by Daniel on 14-Jun-23.
//

#pragma once
#include "Repo.h"
#include "Validator.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo& repo): repo{repo} {}

    vector<Melodie>& getAllServ(){
        return repo.getAll();
    }

    void addMelodieServ(string& titlu, string& autor, string& gen){
        vector<Melodie> melodii = repo.getAll();

        int id = rand();
        Melodie m(id, "", "", "");
        bool cond = false;

        while (!cond){
            cond = true;
            for (auto& mel : melodii)
                if (mel.getId() == id){
                    cond = false;
                    break;
                }
        }

        Melodie mel(id, titlu, autor, gen);
        Validator::validate(mel);
        repo.addMelodie(mel);
    }

    void deleteMelodieServ(int id){
        repo.deleteMelodie(id);
    }
};
