package com.example.zboruri.repository;

import com.example.zboruri.domain.Client;

import java.sql.*;
import java.util.Optional;

public class ClientDbRepo implements ClientRepo {
    private final String url, username, password;

    public ClientDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Client> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Client> findOne(String username) {
        try (
                Connection connection = DriverManager.getConnection(url, this.username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM client WHERE username = ?")
        ) {
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String name = resultSet.getString("name");
                Long id = resultSet.getLong("id_client");
                Client client = new Client(username, name);
                client.setId(id);

                return Optional.of(client);
            }
            return Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Client> findAll() {
        return null;
    }

    @Override
    public Optional<Client> save(Client entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Client> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Client> update(Client entity) {
        return Optional.empty();
    }
}
