package com.example.ofertedevacanta.utils;

import com.example.ofertedevacanta.domain.Hobby;

public interface Observable {
    void notifyObservers(Hobby hobby, Long idClient);
    void addObserver(Observer observer);
}
