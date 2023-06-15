//
// Created by Daniel on 13-Jun-23.
//

#pragma once
#include "Repo.h"

class StergeError: public std::exception{};

class Service {
private:
    Repo& repo;

public:
    Service(Repo& repo): repo{repo} {}

    vector<Melodie> getAllServ();

    void stergeMelodie(int id);

    Melodie& cautaMelodie(int id);

    void updateFile();

    vector<int> raportRank();
};
