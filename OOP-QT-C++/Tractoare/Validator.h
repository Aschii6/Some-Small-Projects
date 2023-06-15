//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Tractor.h"

class ValidError: public exception{
private:
    string msg;
public:
    explicit ValidError(string msg): msg(std::move(msg)) {}
    string getMsg(){
        return msg;
    }
};

class Validator{
public:
    static void validate(Tractor& tr){
        string msg;
        if (tr.getId() < 0)
            msg += "Id-ul nu poate fi negativ\n";
        if (tr.getDenumire().empty())
            msg += "Denumirea nu poate fi vida\n";
        if (tr.getTip().empty())
            msg += "Tipul nu poate fi vid\n";
        if (tr.getNr() < 2 || tr.getNr() > 16 || tr.getNr() % 2 != 0)
            msg += "Numarul de roti trebuie sa fie par, intre 2 si 16\n";
        if (!msg.empty())
            throw ValidError(msg);
    }
};
