package com.example.zboruri.repository;

import com.example.zboruri.domain.Flight;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FlightDbRepo implements FlightRepo {
    private final String url, username, password;

    public FlightDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Flight> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Flight> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM flight")
        ) {
            List<Flight> flights = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_flight");
                String from = resultSet.getString("is_from");
                String to = resultSet.getString("goes_to");
                LocalDateTime departureTime = resultSet.getTimestamp("departure_time").toLocalDateTime();
                LocalDateTime landingTime = resultSet.getTimestamp("landing_time").toLocalDateTime();
                int seats = resultSet.getInt("seats");
                Flight flight = new Flight(from, to,  departureTime, landingTime, seats);
                flight.setId(id);

                flights.add(flight);
            }
            return flights;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Flight> save(Flight entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Flight> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Flight> update(Flight entity) {
        return Optional.empty();
    }
}
