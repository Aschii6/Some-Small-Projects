package com.example.ofertedevacanta.domain;

import java.time.LocalDate;

public class Offer {
    private final String hotelName;
    private final String locationName;
    private final LocalDate startDate;
    private final LocalDate endDate;

    public Offer(String hotelName, String locationName, LocalDate startDate, LocalDate endDate) {
        this.hotelName = hotelName;
        this.locationName = locationName;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public String getHotelName() {
        return hotelName;
    }

    public String getLocationName() {
        return locationName;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }
}
