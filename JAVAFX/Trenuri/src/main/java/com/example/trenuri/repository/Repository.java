package com.example.trenuri.repository;

import com.example.trenuri.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {
    /**
     *
     * @return all entities
     */
    Iterable<E> findAll();
}
