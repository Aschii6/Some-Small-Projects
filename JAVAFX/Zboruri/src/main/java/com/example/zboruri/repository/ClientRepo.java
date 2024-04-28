package com.example.zboruri.repository;

import com.example.zboruri.domain.Client;

import java.util.Optional;

public interface ClientRepo extends Repository<Long, Client> {
    Optional<Client> findOne(String username);
}
