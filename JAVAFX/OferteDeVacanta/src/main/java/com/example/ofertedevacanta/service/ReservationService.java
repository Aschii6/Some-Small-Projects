package com.example.ofertedevacanta.service;

import com.example.ofertedevacanta.domain.Reservation;
import com.example.ofertedevacanta.repository.ReservationRepository;

import java.util.Optional;

public class ReservationService {
    private final ReservationRepository reservationRepo;

    public ReservationService(ReservationRepository reservationRepo) {
        this.reservationRepo = reservationRepo;
    }

    public Optional<Reservation> save(Reservation reservation) {
        return reservationRepo.save(reservation);
    }
}
