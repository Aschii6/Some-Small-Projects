package com.example.trenuri.domain;

public class TrainStation extends Entity<Long> {
    private final long trainId;
    private final long departureCityId;
    private final long destinationCityId;

    public TrainStation(long trainId, long departureCityId, long destinationCityId) {
        this.trainId = trainId;
        this.departureCityId = departureCityId;
        this.destinationCityId = destinationCityId;
    }

    public long getTrainId() {
        return trainId;
    }

    public long getDepartureCityId() {
        return departureCityId;
    }

    public long getDestinationCityId() {
        return destinationCityId;
    }

    @Override
    public String toString() {
        return departureCityId + " - " + trainId + " -> ";
    }
}
