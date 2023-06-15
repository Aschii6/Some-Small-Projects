//
// Created by Daniel on 13-Jun-23.
//

#pragma once
#include <string>

using std::string;

class Melodie {
private:
    int id, rank;
    string titlu, artist;
public:
    Melodie(int id, string& titlu, string& artist, int rank): id{id}, titlu{titlu}, artist{artist}, rank{rank} {}

    int getId() const;

    string getTitlu();

    string getArtist();

    int getRank() const;

    void setRank(int rankNou);

    void setTitlu(string titluNou);

    int operator==(const Melodie& mel){
        return this->id == mel.id;
    }

    ~Melodie() = default;
};
