package com.example.ofertedevacanta.service;

import com.example.ofertedevacanta.domain.Hotel;
import com.example.ofertedevacanta.domain.Location;
import com.example.ofertedevacanta.repository.HotelRepository;

import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;

public class HotelService {
    private final HotelRepository hotelRepo;

    public HotelService(HotelRepository hotelRepo) {
        this.hotelRepo = hotelRepo;
    }

    public Iterable<Hotel> getAllHotelsFromLocation(String location) {
        List<Hotel> hotels = (List<Hotel>) hotelRepo.findAll();

        Long locationId = hotelRepo.getLocationId(location);

        Predicate<Hotel> predicate = hotel -> Objects.equals(hotel.getLocationId(), locationId);

        hotels.removeIf(predicate.negate());

        return hotels;
    }

    public Iterable<String> getAllLocationNames() {
        return hotelRepo.findAllLocationNames();
    }

    public Iterable<Hotel> getAllHotels() {
        return hotelRepo.findAll();
    }

    public Iterable<Location> getAllLocations() {
        return hotelRepo.findAllLocations();
    }
}

