//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;

class Task {
private:
    int id;
    string descriere, stare;
    vector<string> programatori;
public:
    Task(int id, string descriere, string stare, vector<string>& programatori): id{id}, descriere{std::move(descriere)}, programatori{programatori},
        stare{std::move(stare)} {}

    int getId() const{
        return id;
    }
    string getDescriere() const{
        return descriere;
    }
    string getStare() const{
        return stare;
    }
    vector<string>& getProgramatori(){
        return programatori;
    }

    void setStare(string stareNoua){
        stare = std::move(stareNoua);
    }
};
