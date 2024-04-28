package com.example.taximetrie.domain;

import java.time.LocalDateTime;

public class TaxiOrder extends Entity<Long> {
    private final Person person;
    private final Driver taxiDriver;
    private final LocalDateTime date;

    public TaxiOrder(Person person, Driver taxiDriver, LocalDateTime date) {
        this.person = person;
        this.taxiDriver = taxiDriver;
        this.date = date;
    }

    public Person getPerson() {
        return person;
    }

    public Driver getTaxiDriver() {
        return taxiDriver;
    }

    public LocalDateTime getDate() {
        return date;
    }
}
