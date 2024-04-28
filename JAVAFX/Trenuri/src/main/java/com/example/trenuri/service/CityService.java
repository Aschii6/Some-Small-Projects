package com.example.trenuri.service;

import com.example.trenuri.domain.City;
import com.example.trenuri.repository.CityRepository;

import java.util.List;

public class CityService {
    private final CityRepository cityRepository;

    public CityService(CityRepository cityRepository) {
        this.cityRepository = cityRepository;
    }

    public Iterable<City> findAll() {
        return cityRepository.findAll();
    }

    public Iterable<String> findAllNames() {
        return ((List<City>) cityRepository.findAll()).stream().map(City::getName).toList();
    }
}
