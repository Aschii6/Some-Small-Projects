package com.example.ofertedevacanta.domain;

public class Client extends Entity<Long> {
    private final String name;
    private final int fidelityGrade;
    private final int age;
    private final Hobby hobby;

    public Client(String name, int fidelityGrade, int age, Hobby hobby) {
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.age = age;
        this.hobby = hobby;
    }

    public String getName() {
        return name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public int getAge() {
        return age;
    }

    public Hobby getHobby() {
        return hobby;
    }
}
