package com.example.faptebune.utils;

public interface Observable {
    void notifyObservers();
    void addObserver(Observer observer);
}
