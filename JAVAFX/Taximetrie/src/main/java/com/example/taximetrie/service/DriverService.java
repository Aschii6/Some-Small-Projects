package com.example.taximetrie.service;

import com.example.taximetrie.repo.DriverDbRepo;

public class DriverService {
    private final DriverDbRepo driverRepo;

    public DriverService(DriverDbRepo driverRepo) {
        this.driverRepo = driverRepo;
    }
}
