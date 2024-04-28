package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.Hotel;
import com.example.ofertedevacanta.domain.Location;

public interface HotelRepository extends Repository<Long, Hotel>{
    Long getLocationId(String locationName);

    Iterable<Hotel> findAll();

    Iterable<String> findAllLocationNames();

    Iterable<Location> findAllLocations();
}
