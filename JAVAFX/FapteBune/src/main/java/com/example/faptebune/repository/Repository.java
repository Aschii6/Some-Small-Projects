package com.example.faptebune.repository;

import com.example.faptebune.domain.Entity;

import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {
    /**
     * @return all entities
     */
    Iterable<E> findAll();
}


