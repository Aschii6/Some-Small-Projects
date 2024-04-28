package com.example.zboruri.service;

import com.example.zboruri.domain.Flight;
import com.example.zboruri.domain.SuperFlight;
import com.example.zboruri.repository.FlightRepo;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FlightService {
    private final FlightRepo flightRepo;

    public FlightService(FlightRepo flightRepo) {
        this.flightRepo = flightRepo;
    }

    public Iterable<SuperFlight> getAllFlights() {
        List<Flight> flights = (List<Flight>) flightRepo.findAll();

        List<SuperFlight> superFlights = new ArrayList<>();

        for(Flight f : flights) {
            SuperFlight superFlight = new SuperFlight(f.getFrom(), f.getTo(), f.getDepartureTime(), f.getLandingTime(),
                    f.getSeats(), 0);
            superFlight.setId(f.getId());

            superFlights.add(superFlight);
        }
        return superFlights;
    }

    public Iterable<String> getAllFroms() {
        List<Flight> flights = (List<Flight>) flightRepo.findAll();

        return flights.stream()
                .map(Flight::getFrom)
                .distinct()
                .toList();
    }

    public Iterable<String> getAllTos() {
        List<Flight> flights = (List<Flight>) flightRepo.findAll();

        return flights.stream()
                .map(Flight::getTo)
                .distinct()
                .toList();
    }

    public Iterable<SuperFlight> getAllFlightsFiltered(String filterFrom, String filterTo, LocalDateTime filterDate) {
        List<SuperFlight> flights = (List<SuperFlight>) getAllFlights();

        if (filterFrom != null && !filterFrom.isEmpty()) {
            flights = flights.stream()
                    .filter(flight -> flight.getFrom().equals(filterFrom))
                    .toList();
        }

        if (filterTo != null && !filterTo.isEmpty()) {
            flights = flights.stream()
                    .filter(flight -> flight.getTo().equals(filterTo))
                    .toList();
        }

        if (filterDate != null) {
            flights = flights.stream()
                    .filter(flight -> flight.getDepartureTime().toLocalDate().equals(filterDate.toLocalDate()))
                    .toList();
        }

        return flights;
    }
}
