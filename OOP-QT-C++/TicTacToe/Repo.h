//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Joc.h"
#include "vector"
#include "fstream"
#include "sstream"

class Repo {
private:
    vector<Joc> jocuri;
    string path;
public:
    Repo(string path): path(std::move(path)) {}

    vector<Joc>& getAll(){
        read();
        return jocuri;
    }

    void addJoc(Joc& joc){
        read();
        jocuri.push_back(joc);
        write();
    }

    void read(){
        ifstream f(path);
        jocuri.clear();

        string line;
        while (getline(f, line)){
            string token;
            vector<string> tmp;
            stringstream ss(line);
            while (getline(ss,token,','))
                tmp.push_back(token);

            Joc joc(stoi(tmp[0]), stoi(tmp[1]), tmp[2], tmp[3], tmp[4]);
            jocuri.push_back(joc);
        }
        f.close();
    }

    void write(){
        ofstream g(path);

        for (auto& joc : jocuri){
            g << joc.getId() << ',';
            g << joc.getDim() << ',';
            g << joc.getTabla() << ',';
            g << joc.getToPlay() << ',';
            g << joc.getStare() << '\n';
        }
        g.close();
    }
};
