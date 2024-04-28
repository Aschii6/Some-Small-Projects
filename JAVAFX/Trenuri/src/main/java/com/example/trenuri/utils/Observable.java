package com.example.trenuri.utils;

public interface Observable {
    void notifyObservers();
    void addObserver(Observer observer);
}
