package com.example.zboruri.domain;

import java.time.LocalDateTime;

public class Ticket extends Entity<Long> {
    private String username;
    private long flightId;
    private LocalDateTime purchaseTime;

    public Ticket(String username, long flightId, LocalDateTime purchaseTime) {
        this.username = username;
        this.flightId = flightId;
        this.purchaseTime = purchaseTime;
    }

    public String getUsername() {
        return username;
    }

    public long getFlightId() {
        return flightId;
    }

    public LocalDateTime getPurchaseTime() {
        return purchaseTime;
    }
}
