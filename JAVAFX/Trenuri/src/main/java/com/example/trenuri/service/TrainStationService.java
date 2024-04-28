package com.example.trenuri.service;

import com.example.trenuri.domain.TrainStation;
import com.example.trenuri.repository.TrainStationRepository;

public class TrainStationService {
    private final TrainStationRepository trainStationRepository;

    public TrainStationService(TrainStationRepository trainStationRepository) {
        this.trainStationRepository = trainStationRepository;
    }

    public Iterable<TrainStation> findAll() {
        return trainStationRepository.findAll();
    }
}
