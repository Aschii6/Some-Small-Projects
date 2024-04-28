package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.Client;

public interface ClientRepository extends Repository<Long, Client> {
    Iterable<Client> findAll();
}
