//
// Created by Daniel on 14-Jun-23.
//

#pragma once
#include <string>
#include <utility>

using std::string;

class Melodie {
private:
    int id;
    string titlu, artist, gen;
public:
    Melodie(int id, string titlu, string artist, string gen): id{id}, titlu{std::move(titlu)}, artist{std::move(artist)}, gen{std::move(gen)} {}

    int getId() const{
        return id;
    }
    string getTitlu() const{
        return titlu;
    }
    string getArtist() const{
        return artist;
    }
    string getGen() const{
        return gen;
    }

    int operator==(const Melodie& mel) const{
        return this->id == mel.id;
    }
};
