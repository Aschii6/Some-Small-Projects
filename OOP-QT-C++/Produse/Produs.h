//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include <string>
#include <utility>

using namespace std;

class Produs{
private:
    int id;
    string nume, tip;
    double pret;
public:
    Produs(int id, string nume, string tip, double pret): id{id}, nume{std::move(nume)}, tip{std::move(tip)}, pret{pret} {}

    int getId() const{
        return id;
    }
    string getNume() const{
        return nume;
    }
    string getTip() const{
        return tip;
    }
    double getPret() const{
        return pret;
    }
};