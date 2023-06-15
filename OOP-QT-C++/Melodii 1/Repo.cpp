//
// Created by Daniel on 13-Jun-23.
//

#include "Repo.h"
#include <algorithm>
#include <fstream>
#include <sstream>

using std::find;

vector<Melodie>& Repo::getAllRepo() {
    read();
    return melodii;
}

void Repo::stergeMelodie(Melodie& melodie) {
    read();
    auto it = find(melodii.begin(), melodii.end(), melodie);
    melodii.erase(it);
    write();
}

Melodie &Repo::cautaMelodie(int id) {
    read();
    for (auto& mel : melodii)
        if (mel.getId() == id)
            return mel;
}

void Repo::read() {
    std::ifstream f(path);
    melodii.clear();

    string line;
    while (std::getline(f,line)){
        vector<string> tmp;
        string token;
        std::stringstream ss(line);
        while (std::getline(ss,token,','))
            tmp.push_back(token);
        Melodie mel(std::stoi(tmp[0]),tmp[1],tmp[2], std::stoi(tmp[3]));
        melodii.push_back(mel);
    }
    f.close();
}

void Repo::write() {
    std::ofstream g(path);

    for (auto& mel : melodii){
        g << mel.getId() << ',';
        g << mel.getTitlu() << ',';
        g << mel.getArtist() << ',';
        g << mel.getRank() << '\n';
    }
    g.close();
}