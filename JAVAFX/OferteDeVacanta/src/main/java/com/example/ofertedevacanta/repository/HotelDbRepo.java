package com.example.ofertedevacanta.repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

import com.example.ofertedevacanta.domain.Hotel;
import com.example.ofertedevacanta.domain.Location;
import com.example.ofertedevacanta.domain.Type;

public class HotelDbRepo implements HotelRepository {
    private final String url, username, password;

    public HotelDbRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Long getLocationId(String locationName) {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from location where " +
                        "name = ?")
        ) {
            preparedStatement.setString(1, locationName);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getLong("id_location");
            }
            return 0L;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Hotel> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from hotel")
        ){
            List<Hotel> hotels = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_hotel");
                Long locationId = resultSet.getLong("id_location");
                String name = resultSet.getString("name");
                Integer noOfRooms = resultSet.getInt("no_of_rooms");
                Double pricePerNight = resultSet.getDouble("price_per_night");
                Type type = Type.valueOf(resultSet.getString("type"));

                Hotel hotel = new Hotel(locationId, name, noOfRooms, pricePerNight, type);
                hotel.setId(id);

                hotels.add(hotel);
            }
            return hotels;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Location> findAllLocations() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from location")
        ){
            List<Location> locations = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_location");
                String name = resultSet.getString("name");

                Location location = new Location(name);
                location.setId(id);

                locations.add(location);
            }
            return locations;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<String> findAllLocationNames() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from location")
        ) {
            List<String> locationNames = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                locationNames.add(resultSet.getString("name"));
            }

            return locationNames;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
