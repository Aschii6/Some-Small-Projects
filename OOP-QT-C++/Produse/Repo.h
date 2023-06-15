//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Produs.h"
#include <vector>
#include <exception>

using std::vector;
using std::exception;

class DuplicateIdError: public exception {};

class Repo{
private:
    vector<Produs> produse;
    string path;
public:
    Repo(string path): path(std::move(path)) {}

    vector<Produs>& getAll();

    void addProdus(Produs& produs);

    void read();
    void write();
};