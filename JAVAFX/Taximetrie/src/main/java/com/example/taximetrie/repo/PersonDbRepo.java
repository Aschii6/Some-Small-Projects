package com.example.taximetrie.repo;

import com.example.taximetrie.domain.Person;

import java.util.Optional;

public class PersonDbRepo implements PersonRepository {
    @Override
    public Optional<Person> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Person> findAll() {
        return null;
    }

    @Override
    public Optional<Person> save(Person entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Person> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Person> update(Person entity) {
        return Optional.empty();
    }
}
