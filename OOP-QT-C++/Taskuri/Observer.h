//
// Created by Daniel on 15-Jun-23.
//

#pragma once
#include <vector>
#include <algorithm>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    vector<Observer*> observers;
protected:
    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
};