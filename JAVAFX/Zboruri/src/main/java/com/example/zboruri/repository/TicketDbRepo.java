package com.example.zboruri.repository;

import com.example.zboruri.domain.Ticket;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.sql.*;

public class TicketDbRepo implements TicketRepo {
    private final String url, username, password;

    public TicketDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Ticket> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Ticket> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, this.username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM ticket")
        ) {
            List<Ticket> tickets = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_ticket");
                String username = resultSet.getString("username");
                long id_flight = resultSet.getLong("id_flight");
                LocalDateTime purchaseTime = resultSet.getTimestamp("purchase_time").toLocalDateTime();
                Ticket ticket = new Ticket(username, id_flight, purchaseTime);
                ticket.setId(id);
                tickets.add(ticket);
            }
            return tickets;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Ticket> save(Ticket ticket) {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO ticket(username, " +
                        "id_flight, purchase_time) VALUES (?, ?, ?)")
        ) {
            preparedStatement.setString(1, ticket.getUsername());
            preparedStatement.setLong(2, ticket.getFlightId());
            preparedStatement.setTimestamp(3, Timestamp.valueOf(ticket.getPurchaseTime()));

            int affectedRows = preparedStatement.executeUpdate();

            return affectedRows == 0 ? Optional.of(ticket) : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Ticket> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Ticket> update(Ticket entity) {
        return Optional.empty();
    }
}
