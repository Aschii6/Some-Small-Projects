package com.example.faptebune.repository;

import com.example.faptebune.domain.Person;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class PersonRepo implements Repository<Long, Person> {
    private final String url, username, password;

    public PersonRepo(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Iterable<Person> findAll() {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from person")
        ){
            List<Person> persons = new ArrayList<>();

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id_person");
                String lastName = resultSet.getString("last_name");
                String firstName = resultSet.getString("first_name");
                String username = resultSet.getString("username");
                String password = resultSet.getString("password");
                String city = resultSet.getString("city");
                String street = resultSet.getString("street");
                String streetNo = resultSet.getString("street_no");
                String phoneNo = resultSet.getString("phone_no");

                Person person = new Person(lastName, firstName, username, password, city, street, streetNo, phoneNo);
                person.setId(id);

                persons.add(person);
            }

            return persons;
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Optional<Person> save(Person person) {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement(
                        "insert into person(last_name, first_name, username, password, city, street, street_no, " +
                                "phone_no) values (?, ?, ?, ?, ?, ?, ?, ?)"
                )
        ) {
            preparedStatement.setString(1, person.getLastName());
            preparedStatement.setString(2, person.getFirstName());
            preparedStatement.setString(3, person.getUsername());
            preparedStatement.setString(4, person.getPassword());
            preparedStatement.setString(5, person.getCity());
            preparedStatement.setString(6, person.getStreet());
            preparedStatement.setString(7, person.getStreetNo());
            preparedStatement.setString(8, person.getPhoneNo());

            int affectedRows = preparedStatement.executeUpdate();

            return affectedRows == 0 ? Optional.of(person) : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Optional<Person> findOne(Long personInNeedId) {
        try (
                Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement preparedStatement = connection.prepareStatement("select * from person where " +
                        "id_person = ?")
        ){
            preparedStatement.setLong(1, personInNeedId);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                Long id = resultSet.getLong("id_person");
                String lastName = resultSet.getString("last_name");
                String firstName = resultSet.getString("first_name");
                String username = resultSet.getString("username");
                String password = resultSet.getString("password");
                String city = resultSet.getString("city");
                String street = resultSet.getString("street");
                String streetNo = resultSet.getString("street_no");
                String phoneNo = resultSet.getString("phone_no");

                Person person = new Person(lastName, firstName, username, password, city, street, streetNo, phoneNo);
                person.setId(id);

                return Optional.of(person);
            }
            return Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
