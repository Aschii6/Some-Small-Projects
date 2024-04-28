package com.example.zboruri.service;

import com.example.zboruri.domain.Ticket;
import com.example.zboruri.repository.TicketRepo;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;

public class TicketService {
    private final TicketRepo ticketRepo;

    public TicketService(TicketRepo ticketRepo) {
        this.ticketRepo = ticketRepo;
    }

    public Iterable<Ticket> getAllTicketsFromDate() {
        List<Ticket> tickets = (List<Ticket>) ticketRepo.findAll();

        Predicate<Ticket> isTicketFromDate = ticket -> ticket.getPurchaseTime().getYear() == 2024 &&
                ticket.getPurchaseTime().getMonthValue() == 1 &&
                ticket.getPurchaseTime().getDayOfMonth() == 24;

        tickets.removeIf(isTicketFromDate.negate());

        return tickets;
    }

    public Iterable<Ticket> getAllTicketsOfAClient(String username) {
        List<Ticket> tickets = (List<Ticket>) ticketRepo.findAll();

        Predicate<Ticket> isTicketOfAClient = ticket -> ticket.getUsername().equals(username);

        tickets.removeIf(isTicketOfAClient.negate());

        return tickets;
    }

    public void buyTicket(String username, Long flightId) {
        ticketRepo.save(new Ticket(username, flightId, LocalDateTime.now().truncatedTo(ChronoUnit.SECONDS)));
    }

    public Integer getNoOfTicketsForFlight(Long id) {
        List<Ticket> tickets = (List<Ticket>) ticketRepo.findAll();

        Predicate<Ticket> isTicketForFlight = ticket -> ticket.getFlightId() == id;

        tickets.removeIf(isTicketForFlight.negate());

        return tickets.size();
    }
}
