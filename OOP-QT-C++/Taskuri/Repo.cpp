//
// Created by Daniel on 15-Jun-23.
//

#include "Repo.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;

void Repo::addTask(Task &task) {
    read();

    for (auto& t : taskuri)
        if (t.getId() == task.getId())
            throw DuplicateIdError();

    taskuri.push_back(task);

    write();
}

vector<Task> &Repo::getAll() {
    read();
    return taskuri;
}

void Repo::read() {
    ifstream f(path);
    taskuri.clear();

    string line;
    while (std::getline(f, line)){
        stringstream ss(line);
        string token;
        vector<string> tmp;
        while (std::getline(ss, token, ','))
            tmp.push_back(token);

        vector<string> programatori;
        for (int i = 3; i < tmp.size(); ++i) {
            programatori.push_back(tmp[i]);
        }
        Task task(std::stoi(tmp[0]),tmp[1], tmp[2], programatori);
        taskuri.push_back(task);
    }
    f.close();
}

void Repo::write() {
    ofstream g(path);
    for (auto& task : taskuri){
        g << task.getId() << ',';
        g << task.getDescriere() << ',';
        g << task.getStare() << ',';

        vector<string> programatori = task.getProgramatori();
        for (int i = 0; i < programatori.size() - 1; i++){
            g << programatori[i] << ',';
        }
        g << programatori[programatori.size() - 1] << '\n';
    }
    g.close();
}