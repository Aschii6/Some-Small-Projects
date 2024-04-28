package com.example.taximetrie.service;

import com.example.taximetrie.repo.PersonDbRepo;

public class PersonService {
    private final PersonDbRepo personRepo;

    public PersonService(PersonDbRepo personRepo) {
        this.personRepo = personRepo;
    }
}
