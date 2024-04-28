package com.example.taximetrie.domain;

public class Driver extends Person{
    private String carPlate;

    public Driver(String username, String name, String carPlate) {
        super(username, name);
        this.carPlate = carPlate;
    }

    public String getCarPlate() {
        return carPlate;
    }

    public void setCarPlate(String carPlate) {
        this.carPlate = carPlate;
    }
}
