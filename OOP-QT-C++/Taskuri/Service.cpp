//
// Created by Daniel on 15-Jun-23.
//

#include "Service.h"
#include <sstream>
using std::stringstream;

vector<Task> &Service::getAll() {
    return repo.getAll();
}

void Service::addTask(int id, string& descriere, string& stare, string& programatori) {
    stringstream ss(programatori);
    vector<string> listaProgramatori;
    string token;
    while (std::getline(ss,token,',')){
        listaProgramatori.push_back(token);
    }

    Task task(id, descriere, stare, listaProgramatori);
    Validator::validate(task);

    repo.addTask(task);
}

vector<Task> Service::filter(string& filtru) {
    vector<Task> taskuri = repo.getAll();
    vector<Task> rez;

    for (auto& task : taskuri){
        vector<string> programatori = task.getProgramatori();
        for (auto& prog : programatori){
            if (prog.find(filtru) != string::npos){
                rez.push_back(task);
                break;
            }
        }
    }
    return rez;
}