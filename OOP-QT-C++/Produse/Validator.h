//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Produs.h"
#include <exception>

class ValidError: public exception{
private:
    string msg;
public:
    explicit ValidError(string msg): msg{std::move(msg)} {}

    string getMsg() const{
        return msg;
    }
};

class Validator {
public:
    static void validate(Produs& produs){
        string msg;
        if (produs.getId() < 1)
            msg += "Id invalid\n";
        if (produs.getNume().empty())
            msg += "Nume invalid\n";
        if (produs.getTip().empty())
            msg += "Tip invalid\n";
        if (produs.getPret() < 1 || produs.getPret() > 100)
            msg += "Pret invalid\n";
        if (!msg.empty())
            throw ValidError(msg);
    }
};