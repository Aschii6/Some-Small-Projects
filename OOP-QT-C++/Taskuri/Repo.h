//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include "Task.h"
#include <utility>
#include <exception>

using std::exception;

class DuplicateIdError: public exception {};


class Repo {
private:
    vector<Task> taskuri;
    string path;

public:
    void read();
    void write();

    Repo(string path): path{std::move(path)} {}

    void addTask(Task& task);

    vector<Task>& getAll();

    Task& getTask(int id){
        for (auto& task : taskuri){
            if (task.getId() == id)
                return task;
        }
    }
};