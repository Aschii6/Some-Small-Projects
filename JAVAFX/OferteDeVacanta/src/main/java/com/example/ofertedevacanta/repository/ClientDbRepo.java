package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.Client;
import com.example.ofertedevacanta.domain.Hobby;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ClientDbRepo implements ClientRepository {
    private final String url, username, password;

    public ClientDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<Client> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM client")
        ) {
            List<Client> clients = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_client");
                String name = resultSet.getString("name");
                int fidelityGrade = resultSet.getInt("fidelity_grade");
                int age = resultSet.getInt("age");
                Hobby hobby = Hobby.valueOf(resultSet.getString("hobby"));

                Client client = new Client(name, fidelityGrade, age, hobby);
                client.setId(id);

                clients.add(client);
            }
            return clients;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
