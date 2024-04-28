package com.example.ofertedevacanta.domain;

import java.time.LocalDate;

public class Reservation extends Entity<Long> {
    private final Long clientId;
    private final Long hotelId;
    private final LocalDate startDate;
    private final int noOfNights;

    public Reservation(Long clientId, Long hotelId, LocalDate startDate, int noOfNights) {
        this.clientId = clientId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.noOfNights = noOfNights;
    }

    public Long getClientId() {
        return clientId;
    }

    public Long getHotelId() {
        return hotelId;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public int getNoOfNights() {
        return noOfNights;
    }
}
