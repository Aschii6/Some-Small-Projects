package com.example.ofertedevacanta.service;

import com.example.ofertedevacanta.domain.*;
import com.example.ofertedevacanta.utils.Observable;
import com.example.ofertedevacanta.utils.Observer;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements Observable {
    private final HotelService hotelService;
    private final SpecialOfferService specialOfferService;
    private final ClientService clientService;
    private final ReservationService reservationService;

    List<Observer> observers = new ArrayList<>();

    public Service(HotelService hotelService, SpecialOfferService specialOfferService, ClientService clientService, ReservationService reservationService) {
        this.hotelService = hotelService;
        this.specialOfferService = specialOfferService;
        this.clientService = clientService;
        this.reservationService = reservationService;
    }

    public Iterable<Hotel> getAllHotelsFromLocation(String location) {
        return hotelService.getAllHotelsFromLocation(location);
    }

    public Iterable<String> getAllLocationNames() {
        return hotelService.getAllLocationNames();
    }

    public Iterable<SpecialOffer> getAllSpecialOffersFiltered(Long hotelId, LocalDate startDate, LocalDate endDate) {
        return specialOfferService.getAllSpecialOffersFiltered(hotelId, startDate, endDate);
    }

    public Iterable<Client> getAllClients() {
        return clientService.getAllClients();
    }

    public Iterable<Offer> getAllOffers(int fidelityGrade) {
        List<SpecialOffer> specialOffers = (List<SpecialOffer>) specialOfferService.getAllSpecialOffers();

        List<Hotel> hotels = (List<Hotel>) hotelService.getAllHotels();

        List<Location> locations = (List<Location>) hotelService.getAllLocations();

        specialOffers.removeIf(specialOffer -> specialOffer.getPercents() > fidelityGrade);

        specialOffers.removeIf(specialOffer -> specialOffer.getStartDate().isBefore(LocalDate.now()));

        List<Offer> offers = new ArrayList<>();

        for (SpecialOffer specialOffer : specialOffers) {
            Hotel hotel = hotels.stream().filter(h -> h.getId().equals(specialOffer.getHotelId())).findFirst().orElse(null);
            Location location = locations.stream().filter(l -> l.getId().equals(hotel.getLocationId())).findFirst().orElse(null);

            offers.add(new Offer(hotel.getName(), location.getName(), specialOffer.getStartDate(), specialOffer.getEndDate()));
        }

        return offers;
    }

    public void addReservation(Long idClient, Long idHotel, LocalDate startDate, int noOfNights, Hobby hobby) {
        Reservation reservation = new Reservation(idClient, idHotel, startDate, noOfNights);

        Optional<Reservation> opt = reservationService.save(reservation);

        if (opt.isPresent()) {
            throw new RuntimeException("Reservation add problem");
        }

        notifyObservers(hobby, idClient);
    }

    @Override
    public void notifyObservers(Hobby hobby, Long idClient) {
        observers.forEach(observer -> {
            if (observer.getHobby().equals(hobby) && !observer.getId().equals(idClient)) {
                observer.update();
            }
        });
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }
}
