package com.example.trenuri.service;

import com.example.trenuri.domain.City;
import com.example.trenuri.domain.Ticket;
import com.example.trenuri.domain.TrainStation;
import com.example.trenuri.utils.Observable;
import com.example.trenuri.utils.Observer;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements Observable {
    private final CityService cityService;
    private final TrainStationService trainStationService;
    private final TicketService ticketService;

    private List<Observer> observers = new ArrayList<>();

    public Service(CityService cityService, TrainStationService trainStationService, TicketService ticketService) {
        this.cityService = cityService;
        this.trainStationService = trainStationService;
        this.ticketService = ticketService;
    }
    public Iterable<String> findAllCityNames() {
        return cityService.findAllNames();
    }

    public void findRoutes(String departureCity, String destinationCity) {
        notifyObservers();
    }

    @Override
    public void notifyObservers() {
        for (Observer observer : observers) {
            int nr = 0;
            String departureCity = observer.getDepartureCity();
            String destinationCity = observer.getDestinationCity();

            for (Observer o : observers) {
                if (o.getDepartureCity().equals(departureCity) && o.getDestinationCity().equals(destinationCity)) {
                    nr++;
                }
            }

            observer.update(nr);
        }
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    public Iterable<Long> findAllTrainIds(String departureCity) {
        List<Long> trainIds = new ArrayList<>();

        List<City> cities = (List<City>) cityService.findAll();

        Optional<City> opt = cities.stream().filter(city -> city.getName().equals(departureCity)).findFirst();

        if (opt.isEmpty()) {
            return trainIds;
        }

        long cityId = opt.get().getId();

        List<TrainStation> trainStations = (List<TrainStation>) trainStationService.findAll();

        for (TrainStation trainStation : trainStations) {
            if (trainStation.getDepartureCityId() == cityId) {
                trainIds.add(trainStation.getTrainId());
            }
        }

        return trainIds;
    }

    public void buyTicket(Long trainId, String departureCity, LocalDate date) {
        List<City> cities = (List<City>) cityService.findAll();

        Optional<City> opt = cities.stream().filter(city -> city.getName().equals(departureCity)).findFirst();

        if (opt.isEmpty()) {
            return;
        }

        long cityId = opt.get().getId();

        Ticket ticket = new Ticket(trainId, cityId, date);

        ticketService.addTicket(ticket);

        notifyObservers();
    }
}
