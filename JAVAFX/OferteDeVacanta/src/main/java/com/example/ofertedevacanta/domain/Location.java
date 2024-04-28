package com.example.ofertedevacanta.domain;

public class Location extends Entity<Long> {
    private final String name;

    public Location(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
