package com.example.trenuri.domain;

import java.time.LocalDate;

public class Ticket extends Entity<Long> {
    private final long trainId;
    private final long departureCityId;
    private final LocalDate date;

    public Ticket(long trainId, long departureCityId, LocalDate date) {
        this.trainId = trainId;
        this.departureCityId = departureCityId;
        this.date = date;
    }

    public long getTrainId() {
        return trainId;
    }

    public long getDepartureCityId() {
        return departureCityId;
    }

    public LocalDate getDate() {
        return date;
    }
}
