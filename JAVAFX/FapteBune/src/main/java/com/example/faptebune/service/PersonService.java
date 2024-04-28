package com.example.faptebune.service;

import com.example.faptebune.domain.Person;
import com.example.faptebune.repository.PersonRepo;

import java.util.List;
import java.util.Optional;

public class PersonService {
    private final PersonRepo personRepo;

    public PersonService(PersonRepo personRepo) {
        this.personRepo = personRepo;
    }

    public Iterable<Person> getAllPersons() {
        return personRepo.findAll();
    }

    public void register(Person person) {
        Optional<Person> opt = personRepo.save(person);

        if (opt.isPresent()) {
            throw new RuntimeException("Person add problem");
        }
    }

    public Person getPersonByUsername(String username) {
        List<Person> persons = (List<Person>) personRepo.findAll();

        for (Person person : persons) {
            if (person.getUsername().equals(username)) {
                return person;
            }
        }
        return null;
    }

    public Person getOne(Long personInNeedId) {
        Optional<Person> opt = personRepo.findOne(personInNeedId);

        if (opt.isPresent())
            return opt.get();

        throw new RuntimeException("Person not found");
    }
}
