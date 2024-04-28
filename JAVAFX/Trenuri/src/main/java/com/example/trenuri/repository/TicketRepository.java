package com.example.trenuri.repository;

import com.example.trenuri.domain.Ticket;

import java.util.Optional;

public interface TicketRepository extends Repository<Long, Ticket> {
    Optional<Ticket> save(Ticket ticket);
}
