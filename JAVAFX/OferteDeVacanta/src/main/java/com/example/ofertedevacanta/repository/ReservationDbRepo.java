package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.Reservation;

import java.sql.*;
import java.util.Optional;

public class ReservationDbRepo implements ReservationRepository {
    private final String url, username, password;

    public ReservationDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Reservation> save(Reservation reservation) {
        try (
                Connection connection = DriverManager.getConnection(url, this.username, password);
                PreparedStatement preparedStatement = connection.prepareStatement(
                        "INSERT INTO reservation (id_client, id_hotel, start_date, no_of_nights) VALUES (?, ?, ?, ?)")
        ) {
            preparedStatement.setLong(1, reservation.getClientId());
            preparedStatement.setLong(2, reservation.getHotelId());
            preparedStatement.setDate(3, Date.valueOf(reservation.getStartDate()));
            preparedStatement.setInt(4, reservation.getNoOfNights());

            int affectedRows = preparedStatement.executeUpdate();

            return affectedRows == 0 ? Optional.of(reservation) : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
