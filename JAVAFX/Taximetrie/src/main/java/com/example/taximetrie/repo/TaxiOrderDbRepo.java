package com.example.taximetrie.repo;

import com.example.taximetrie.domain.TaxiOrder;

import java.util.Optional;

public class TaxiOrderDbRepo implements TaxiOrderRepository{
    @Override
    public Optional<TaxiOrder> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<TaxiOrder> findAll() {
        return null;
    }

    @Override
    public Optional<TaxiOrder> save(TaxiOrder entity) {
        return Optional.empty();
    }

    @Override
    public Optional<TaxiOrder> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<TaxiOrder> update(TaxiOrder entity) {
        return Optional.empty();
    }
}
