package com.example.zboruri.domain;

import java.time.LocalDateTime;

public class SuperFlight extends Flight{
    private int freeSeats;

    public SuperFlight(String from, String to, LocalDateTime departureTime, LocalDateTime landingTime, int seats, int freeSeats) {
        super(from, to, departureTime, landingTime, seats);
        this.freeSeats = freeSeats;
    }

    public void setFreeSeats(int freeSeats) {
        this.freeSeats = freeSeats;
    }
    public int getFreeSeats() {
        return freeSeats;
    }
}
