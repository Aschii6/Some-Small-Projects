package com.example.zboruri.service;

import com.example.zboruri.domain.Client;
import com.example.zboruri.repository.ClientRepo;

import java.util.Optional;

public class ClientService {
    private final ClientRepo clientRepo;

    public ClientService(ClientRepo clientRepo) {
        this.clientRepo = clientRepo;
    }

    public Optional<Client> findOne(String username) {
        return clientRepo.findOne(username);
    }
}
