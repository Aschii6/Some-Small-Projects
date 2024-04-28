package com.example.trenuri.repository;

import com.example.trenuri.domain.TrainStation;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TrainStationDbRepo implements TrainStationRepository{
    private final String url, username, password;

    public TrainStationDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<TrainStation> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement statement = connection.prepareStatement("SELECT * FROM trainstation")
        ) {
            List<TrainStation> trainStations = new ArrayList<>();

            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                long id = resultSet.getLong("id_station");
                long trainId = resultSet.getLong("id_train");
                long departureCityId = resultSet.getLong("id_departure_city");
                long destinationCityId = resultSet.getLong("id_destination_city");
                TrainStation trainStation = new TrainStation(trainId, departureCityId, destinationCityId);
                trainStation.setId(id);

                trainStations.add(trainStation);
            }
            return trainStations;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
