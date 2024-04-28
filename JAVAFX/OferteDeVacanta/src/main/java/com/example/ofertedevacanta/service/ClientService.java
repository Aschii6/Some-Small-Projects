package com.example.ofertedevacanta.service;

import com.example.ofertedevacanta.domain.Client;
import com.example.ofertedevacanta.repository.ClientRepository;

public class ClientService {
    private final ClientRepository clientRepo;

    public ClientService(ClientRepository clientRepo) {
        this.clientRepo = clientRepo;
    }

    public Iterable<Client> getAllClients() {
        return clientRepo.findAll();
    }
}
