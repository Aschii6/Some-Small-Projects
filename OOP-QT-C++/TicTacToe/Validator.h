//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "exception"
#include "Joc.h"
#include <string>

using namespace std;

class ValidError: public exception{
private:
    string msg;
public:
    explicit ValidError(string msg): msg(std::move(msg)) {}

    string getMsg() const{
        return msg;
    }
};

class Validator{
public:
    static void validate(Joc& joc){

    }
};
