//
// Created by Daniel on 13-Jun-23.
//

#include "Service.h"


vector<Melodie> Service::getAllServ() {
    return repo.getAllRepo();
}

void Service::stergeMelodie(int id) {
    vector<Melodie> melodii = repo.getAllRepo();
    string artist;
    for (auto& mel : melodii)
        if (mel.getId() == id){
            artist = mel.getArtist();
            break;
        }
    int nr = 0;
    for (auto& mel : melodii)
        if (mel.getArtist() == artist)
            nr++;
    if (nr == 1)
        throw StergeError();

    string a, b;
    Melodie mel(id,a,b,0);
    repo.stergeMelodie(mel);
}

Melodie &Service::cautaMelodie(int id) {
    return repo.cautaMelodie(id);
}

void Service::updateFile() {
    repo.write();
}

vector<int> Service::raportRank() {
    vector<int> raport(11,0);
    for (auto& mel : repo.getAllRepo())
        raport[mel.getRank()]++;
    return raport;
}