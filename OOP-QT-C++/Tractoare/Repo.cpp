//
// Created by Daniel on 15-Jun-23.
//

#include "Repo.h"
#include "fstream"
#include "sstream"

vector<Tractor> &Repo::getAll() {
    read();
    return tractoare;
}

void Repo::addTractor(Tractor &tractor) {
    read();
    for (auto& t : tractoare)
        if (t.getId() == tractor.getId())
            throw DuplicateIdError();
    tractoare.push_back(tractor);
    write();
}

void Repo::read() {
    ifstream f(path);
    tractoare.clear();

    string line;
    while (getline(f, line)){
        string token;
        vector<string> tmp;
        stringstream ss(line);
        while (getline(ss,token,','))
            tmp.push_back(token);

        Tractor tr(stoi(tmp[0]), tmp[1], tmp[2], stoi(tmp[3]));
        tractoare.push_back(tr);
    }
    f.close();
}

void Repo::write() {
    ofstream g(path);

    for (auto& tr : tractoare){
        g << tr.getId() << ',';
        g << tr.getDenumire() << ',';
        g << tr.getTip() << ',';
        g << tr.getNr() << '\n';
    }
    g.close();
}

Tractor &Repo::searchTractor(int id) {
    read();
    for (auto& tr : tractoare)
        if (tr.getId() == id)
            return tr;
}