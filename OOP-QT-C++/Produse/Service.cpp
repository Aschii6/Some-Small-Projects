//
// Created by Daniel on 15-Jun-23.
//

#include "Service.h"

void Service::addProdus(int id, string &nume, string &tip, double pret) {
    Produs produs{id, nume, tip, pret};
    Validator::validate(produs);
    repo.addProdus(produs);
    notify();
}