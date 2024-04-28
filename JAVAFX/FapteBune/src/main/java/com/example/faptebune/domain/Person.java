package com.example.faptebune.domain;

public class Person extends Entity<Long> {
    // FIXME: trebuie enum la city??
    private final String lastName, firstName, username, password, city, street, streetNo, phoneNo;

    public Person(String lastName, String firstName, String username, String password, String city,
                  String street, String streetNo, String phoneNo) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.username = username;
        this.password = password;
        this.city = city;
        this.street = street;
        this.streetNo = streetNo;
        this.phoneNo = phoneNo;
    }

    public String getLastName() {
        return lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getCity() {
        return city;
    }

    public String getStreet() {
        return street;
    }

    public String getStreetNo() {
        return streetNo;
    }

    public String getPhoneNo() {
        return phoneNo;
    }
}
