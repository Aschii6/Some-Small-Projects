package com.example.taximetrie.service;

import com.example.taximetrie.repo.TaxiOrderDbRepo;

public class TaxiOrderService {
    private final TaxiOrderDbRepo taxiOrderRepo;

    public TaxiOrderService(TaxiOrderDbRepo taxiOrderRepo) {
        this.taxiOrderRepo = taxiOrderRepo;
    }
}
