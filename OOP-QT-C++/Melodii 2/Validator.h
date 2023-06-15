//
// Created by Daniel on 14-Jun-23.
//

#pragma once
#include "Melodie.h"
#include <exception>
#include <utility>

using std::exception;

class ValidError: public exception{
private:
    string msg;
public:
    ValidError(string msg): msg{std::move(msg)} {}
    string getMsg(){
        return msg;
    }
};

class Validator{
public:
    static void validate(Melodie& mel){
        string msg;
        if (mel.getArtist().empty())
            msg += "Artist nu poate fi vid\n";
        if (mel.getTitlu().empty())
            msg += "Tilu vid\n";

        string gen = mel.getGen();
        if (gen.empty())
            msg += "Gen Vid";
        else if (gen != "rock" && gen != "pop" && gen != "folk" && gen != "disco")
            msg += "Gen invalid";

        if (msg.length() > 0)
            throw ValidError(msg);
    }
};