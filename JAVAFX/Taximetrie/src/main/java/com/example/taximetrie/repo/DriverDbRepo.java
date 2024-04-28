package com.example.taximetrie.repo;

import com.example.taximetrie.domain.Driver;

import java.util.Optional;

public class DriverDbRepo implements DriverRepository{
    @Override
    public Optional<Driver> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Driver> findAll() {
        return null;
    }

    @Override
    public Optional<Driver> save(Driver entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Driver> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Driver> update(Driver entity) {
        return Optional.empty();
    }
}
