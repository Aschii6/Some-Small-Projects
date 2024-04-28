package com.example.trenuri.repository;

import com.example.trenuri.domain.City;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class CityDbRepo implements CityRepository{
    private final String url, username, password;

    public CityDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<City> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement statement = connection.prepareStatement("SELECT * FROM city")
        ) {
            List<City> cities = new ArrayList<>();

            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                long id = resultSet.getLong("id_city");
                String name = resultSet.getString("name");
                City city = new City(name);
                city.setId(id);

                cities.add(city);
            }

            return cities;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
