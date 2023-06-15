//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include <exception>
#include <string>

using std::exception;
using std::string;

class ValidError: public exception{
private:
    string msg;
public:
    ValidError(string& msg): msg{msg} {}
    string getMsg(){
        return msg;
    }
};

class Validator{
public:
    static void validate(Task& task){
        string msg;
        if (task.getDescriere().empty())
            msg += "Decriere vida\n";
        string stare = task.getStare();
        if (stare != "open" && stare != "inprogress" && stare != "closed")
            msg += "Stare invalida\n";
        if (task.getProgramatori().size() > 4 || task.getProgramatori().empty())
            msg += "Nr programatori invalid\n";

        if (msg.length() > 0)
            throw ValidError(msg);
    }
};