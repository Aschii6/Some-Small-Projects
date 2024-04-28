package com.example.ofertedevacanta.domain;

public class Hotel extends Entity<Long> {
    private final Long locationId;
    private final String name;
    private final int noOfRooms;
    private final double pricePerNight;
    private final Type type;

    public Hotel(Long locationId, String name, int noOfRooms, double pricePerNight, Type type) {
        this.locationId = locationId;
        this.name = name;
        this.noOfRooms = noOfRooms;
        this.pricePerNight = pricePerNight;
        this.type = type;
    }

    public Long getLocationId() {
        return locationId;
    }

    public String getName() {
        return name;
    }

    public int getNoOfRooms() {
        return noOfRooms;
    }

    public double getPricePerNight() {
        return pricePerNight;
    }

    public Type getType() {
        return type;
    }
}
