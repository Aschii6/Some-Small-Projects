//
// Created by Daniel on 15-Jun-23.
//

#include "Repo.h"
#include <fstream>
#include <sstream>

void Repo::read() {
    ifstream f(path);
    produse.clear();

    string line;
    while (getline(f, line)){
        stringstream ss(line);
        string token;
        vector<string> tmp;
        while (std::getline(ss, token, ','))
            tmp.push_back(token);

        Produs produs(stoi(tmp[0]), tmp[1], tmp[2], stod(tmp[3]));
        produse.push_back(produs);
    }
    f.close();
}

void Repo::write() {
    ofstream g(path);

    for (auto& produs : produse){
        g << produs.getId() << ',';
        g << produs.getNume() << ',';
        g << produs.getTip() << ',';
        g << produs.getPret() << '\n';
    }
    g.close();
}

vector<Produs>& Repo::getAll() {
    read();
    return produse;
}

void Repo::addProdus(Produs &produs) {
    read();
    for (auto& p : produse)
        if (p.getId() == produs.getId())
            throw DuplicateIdError();
    produse.push_back(produs);
    write();
}