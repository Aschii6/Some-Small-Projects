//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Repo.h"
#include "Validator.h"
#include "Observer.h"

class Service: public Observable{
private:
    Repo& repo;
public:
    Service(Repo& repo): repo{repo} {}

    vector<Task>& getAll();

    void addTask(int id, string& descriere, string& stare, string& programatori);

    vector<Task> filter(string& filtru);

    void updateFile(){
        repo.write();
        notify();
    }

    Task& getTask(int id){
        return repo.getTask(id);
    }
};
