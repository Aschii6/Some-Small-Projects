package com.example.trenuri.service;

import com.example.trenuri.domain.Ticket;
import com.example.trenuri.repository.TicketRepository;

public class TicketService {
    TicketRepository ticketRepo;

    public TicketService(TicketRepository ticketRepo) {
        this.ticketRepo = ticketRepo;
    }

    public void addTicket(Ticket ticket) {
        ticketRepo.save(ticket);
    }
}
