//
// Created by Daniel on 14-Jun-23.
//

#pragma once

#include <utility>
#include <vector>
#include "Melodie.h"

using std::vector;

class Repo {
private:
    vector<Melodie> melodii;
    string path;

    void read();
    void write();
public:
    Repo(string path): path{std::move(path)} {}

    void addMelodie(Melodie& melodie){
        read();
        melodii.push_back(melodie);
        write();
    }

    void deleteMelodie(int id);

    vector<Melodie>& getAll(){
        read();
        return melodii;
    }
};