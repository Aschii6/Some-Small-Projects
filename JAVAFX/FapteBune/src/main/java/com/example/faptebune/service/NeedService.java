package com.example.faptebune.service;

import com.example.faptebune.domain.Need;
import com.example.faptebune.repository.NeedRepo;

import java.util.Optional;

public class NeedService {
    private final NeedRepo needRepo;

    public NeedService(NeedRepo needRepo) {
        this.needRepo = needRepo;
    }

    public Iterable<Need> getAllNeeds() {
        return needRepo.findAll();
    }

    public void updateNeed(Long needId, Long personHelpingId) {
        needRepo.update(needId, personHelpingId);
    }
}
