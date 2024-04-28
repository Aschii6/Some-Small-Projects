package com.example.trenuri.repository;

import com.example.trenuri.domain.Ticket;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class TicketDbRepo implements TicketRepository {
    private final String url;
    private final String user;
    private final String password;

    public TicketDbRepo(String url, String user, String password) {
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Iterable<Ticket> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, user, password);
                PreparedStatement statement = connection.prepareStatement("SELECT * FROM ticket")
        ){
            List<Ticket> tickets = new ArrayList<>();

            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                long id = resultSet.getLong("id_ticket");
                long idTrain = resultSet.getLong("id_train");
                long departureCityId = resultSet.getLong("id_departure_city");
                LocalDate date = resultSet.getDate("ticket_date").toLocalDate();

                Ticket ticket = new Ticket(idTrain, departureCityId, date);
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
                Connection connection = DriverManager.getConnection(url, user, password);
                PreparedStatement statement = connection.prepareStatement("INSERT INTO ticket (id_train, id_departure_city, " +
                        "ticket_date) VALUES (?, ?, ?)")
        ) {
            statement.setLong(1, ticket.getTrainId());
            statement.setLong(2, ticket.getDepartureCityId());
            statement.setDate(3, Date.valueOf(ticket.getDate()));

            int affectedRows = statement.executeUpdate();

            return affectedRows == 0 ? Optional.of(ticket) : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
