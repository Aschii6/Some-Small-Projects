package com.example.faptebune.service;

import com.example.faptebune.domain.Need;
import com.example.faptebune.domain.Person;
import com.example.faptebune.utils.Observable;
import com.example.faptebune.utils.Observer;

import java.util.ArrayList;
import java.util.List;

public class Service implements Observable {
    private final PersonService personService;
    private final NeedService needService;

    List<Observer> observers = new ArrayList<>();

    public Service(PersonService personService, NeedService needService) {
        this.personService = personService;
        this.needService = needService;
    }

    public Iterable<Person> getAllPersons() {
        return personService.getAllPersons();
    }

    public void register(String lastName, String firstName, String username, String password, String city,
                         String street, String streetNo, String phoneNo) {
        Person person = new Person(lastName, firstName, username, password, city, street, streetNo, phoneNo);
        personService.register(person);
    }

    public Person getPersonByUsername(String username) {
        return personService.getPersonByUsername(username);
    }

    public Iterable<Need> getAllNeedsFromYourCity(String cityName, Long yourId) {
        List<Need> needs = (List<Need>) needService.getAllNeeds();

        needs.removeIf(need -> need.getPersonInNeedId().equals(yourId));

        needs.removeIf(need -> !personService.getOne(need.getPersonInNeedId()).getCity().equals(cityName));

        return needs;
    }

    public void updateNeed(Long needId, Long personHelpingId) {
        needService.updateNeed(needId, personHelpingId);
        notifyObservers();
    }

    @Override
    public void notifyObservers() {
        observers.forEach(Observer::update);
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }
}
