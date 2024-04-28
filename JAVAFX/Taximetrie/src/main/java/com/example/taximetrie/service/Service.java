package com.example.taximetrie.service;

public class Service {
    private final PersonService personService;
    private final DriverService driverService;
    private final TaxiOrderService taxiOrderService;

    public Service(PersonService personService, DriverService driverService, TaxiOrderService taxiOrderService) {
        this.personService = personService;
        this.driverService = driverService;
        this.taxiOrderService = taxiOrderService;
    }
}
