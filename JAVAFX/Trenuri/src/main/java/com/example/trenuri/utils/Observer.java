package com.example.trenuri.utils;

public interface Observer {
    public String getDepartureCity();
    public String getDestinationCity();
    public void update(int nr);
}
