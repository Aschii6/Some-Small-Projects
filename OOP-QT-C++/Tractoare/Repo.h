//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Tractor.h"
#include <vector>
#include <exception>

class DuplicateIdError: public exception{};

class Repo{
private:
    vector<Tractor> tractoare;
    string path;
public:
    explicit Repo(string path): path(std::move(path)) {}

    vector<Tractor>& getAll();

    void addTractor(Tractor& tractor);

    void read();
    void write();

    Tractor& searchTractor(int id);
};