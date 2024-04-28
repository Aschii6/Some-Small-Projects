package com.example.ofertedevacanta.utils;


import com.example.ofertedevacanta.domain.Hobby;

public interface Observer {
    public void update();
    public Hobby getHobby();
    public Long getId();
}
