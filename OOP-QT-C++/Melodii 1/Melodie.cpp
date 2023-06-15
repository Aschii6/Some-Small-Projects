//
// Created by Daniel on 13-Jun-23.
//

#include "Melodie.h"

int Melodie::getId() const {
    return id;
}

string Melodie::getTitlu() {
    return titlu;
}

string Melodie::getArtist() {
    return artist;
}

int Melodie::getRank() const {
    return rank;
}

void Melodie::setRank(int rankNou) {
    rank = rankNou;
}

void Melodie::setTitlu(string titluNou) {
    titlu = titluNou;
}