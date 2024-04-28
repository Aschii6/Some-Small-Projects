package com.example.faptebune.domain;

import java.time.LocalDateTime;

public class Need extends Entity<Long> {
    private final String title, description;
    private final LocalDateTime deadline;
    private final Long personInNeedId;
    private Long personHelpingId = null;
    private final String status;

    public Need(String title, String description, LocalDateTime deadline, Long personInNeedId, String status) {
        this.title = title;
        this.description = description;
        this.deadline = deadline;
        this.personInNeedId = personInNeedId;
        this.status = status;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public LocalDateTime getDeadline() {
        return deadline;
    }

    public Long getPersonInNeedId() {
        return personInNeedId;
    }

    public Long getPersonHelpingId() {
        return personHelpingId;
    }

    public String getStatus() {
        return status;
    }

    public void setPersonHelpingId(Long personHelpingId) {
        this.personHelpingId = personHelpingId;
    }
}
