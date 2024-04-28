package com.example.ofertedevacanta.domain;

import java.time.LocalDate;

public class SpecialOffer extends Entity<Long> {
    private final Long hotelId;
    private final LocalDate startDate;
    private final LocalDate endDate;
    private final int percents;

    public SpecialOffer(Long hotelId, LocalDate startDate, LocalDate endDate, int percents) {
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public Long getHotelId() {
        return hotelId;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public int getPercents() {
        return percents;
    }
}
