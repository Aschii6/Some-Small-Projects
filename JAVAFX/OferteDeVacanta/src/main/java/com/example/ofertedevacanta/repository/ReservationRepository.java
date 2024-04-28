package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.Reservation;

import java.util.Optional;

public interface ReservationRepository extends Repository<Long, Reservation>{
    Optional<Reservation> save(Reservation reservation);
}
