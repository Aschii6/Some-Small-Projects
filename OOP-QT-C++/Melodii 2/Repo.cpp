//
// Created by Daniel on 14-Jun-23.
//

#include "Repo.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::getline;
using std::stoi;
using std::find;
using std::stringstream;

void Repo::read() {
    ifstream f(path);
    melodii.clear();

    string line;
    while (getline(f,line)){
        vector<string> tmp;
        string token;
        stringstream ss(line);
        while(getline(ss,token,','))
            tmp.push_back(token);
        Melodie mel(stoi(tmp[0]), tmp[1], tmp[2], tmp[3]);
        melodii.push_back(mel);
    }
    f.close();
}

void Repo::write() {
    ofstream g(path);

    for (auto& mel : melodii){
        g << mel.getId() << ',';
        g << mel.getTitlu() << ',';
        g << mel.getArtist() << ',';
        g << mel.getGen() << '\n';
    }
    g.close();
}

void Repo::deleteMelodie(int id) {
    read();

    Melodie mel(id, "", "", "");
    auto it = find(melodii.begin(), melodii.end(), mel);
    melodii.erase(it);

    write();
}