package com.example.ofertedevacanta.repository;

import com.example.ofertedevacanta.domain.SpecialOffer;

public interface SpecialOfferRepository extends Repository<Long, SpecialOffer> {
    Iterable<SpecialOffer> findAll();
}
