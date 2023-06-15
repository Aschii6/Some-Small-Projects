//
// Created by Daniel on 13-Jun-23.
//

#pragma once
#include "Melodie.h"
#include <vector>

using std::vector;

class Repo {
private:
    string path;
    vector<Melodie> melodii;

public:
    Repo(string path): path{path} {}

    vector<Melodie>& getAllRepo();

    void stergeMelodie(Melodie& melodie);

    Melodie& cautaMelodie(int id);

    void read();

    void write();

    ~Repo() = default;
};