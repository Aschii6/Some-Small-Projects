package com.example.trenuri.domain;

public class City extends Entity<Long> {
    private final String name;

    public City(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
