package com.example.zboruri.service;

import com.example.zboruri.domain.Client;
import com.example.zboruri.domain.Flight;
import com.example.zboruri.domain.SuperFlight;
import com.example.zboruri.domain.Ticket;
import com.example.zboruri.utils.Observable;
import com.example.zboruri.utils.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements Observable {
    private final ClientService clientService;
    private final FlightService flightService;
    private final TicketService ticketService;

    private List<Observer> observers = new ArrayList<>();

    public Service(ClientService clientService, FlightService flightService, TicketService ticketService) {
        this.clientService = clientService;
        this.flightService = flightService;
        this.ticketService = ticketService;
    }

    public Client login(String username) {
        Optional<Client> opt = clientService.findOne(username);
        if (opt.isPresent()) {
            return opt.get();
        }

        throw new ServiceException("Username not registered");
    }

    public Iterable<Ticket> getAllTicketsFromDate() {
        return ticketService.getAllTicketsFromDate();
    }

    public Iterable<Ticket> getAllTicketsOfAClient(String username) {
        return ticketService.getAllTicketsOfAClient(username);
    }

    public Iterable<SuperFlight> getAllFlights() {
        Iterable<SuperFlight> iterable = flightService.getAllFlights();

        iterable.forEach(flight -> flight.setFreeSeats(flight.getSeats() - ticketService.getNoOfTicketsForFlight(flight.getId())));

        return iterable;
    }

    public Iterable<String> getAllFroms() {
        return flightService.getAllFroms();
    }

    public Iterable<String> getAllTos() {
        return flightService.getAllTos();
    }

    public Iterable<SuperFlight> getAllFlightsFiltered(String filterFrom, String filterTo, LocalDateTime filterDate) {
        Iterable<SuperFlight> iterable = flightService.getAllFlightsFiltered(filterFrom, filterTo, filterDate);

        iterable.forEach(flight -> flight.setFreeSeats(flight.getSeats() - ticketService.getNoOfTicketsForFlight(flight.getId())));

        return iterable;
    }

    public void buyTicket(String username, Long flightId) {
        ticketService.buyTicket(username, flightId);

        notifyObservers();
        notifyObservers();
    }

    @Override
    public void notifyObservers() {
        observers.forEach(Observer::update);
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }
}
