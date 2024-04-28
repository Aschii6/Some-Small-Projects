package com.example.zboruri.utils;

public interface Observable {
    void notifyObservers();
    void addObserver(Observer observer);
}
