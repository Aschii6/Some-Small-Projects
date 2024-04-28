package com.example.ofertedevacanta.service;

import com.example.ofertedevacanta.domain.SpecialOffer;
import com.example.ofertedevacanta.repository.SpecialOfferRepository;

import java.time.LocalDate;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class SpecialOfferService {
    private final SpecialOfferRepository specialOfferRepo;

    public SpecialOfferService(SpecialOfferRepository specialOfferRepo) {
        this.specialOfferRepo = specialOfferRepo;
    }

    public Iterable<SpecialOffer> getAllSpecialOffersFiltered(Long hotelId, LocalDate startDate, LocalDate endDate) {
        List<SpecialOffer> specialOffers = (List<SpecialOffer>) specialOfferRepo.findAll();

        if (hotelId != null)
            specialOffers = specialOffers.stream().filter(s -> Objects.equals(s.getHotelId(), hotelId)).collect(Collectors.toList());

        if (startDate != null && endDate != null) {
            specialOffers = specialOffers.stream().filter(s -> (s.getStartDate().isAfter(startDate) ||
                    s.getStartDate().isEqual(startDate)) && (s.getEndDate().isBefore(endDate) ||
                    s.getEndDate().isEqual(endDate)))
                    .collect(Collectors.toList());
        }

        return specialOffers;
    }

    public Iterable<SpecialOffer> getAllSpecialOffers() {
        return specialOfferRepo.findAll();
    }
}
