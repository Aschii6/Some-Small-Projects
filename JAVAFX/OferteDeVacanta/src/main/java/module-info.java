module com.example.ofertedevacanta {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.ofertedevacanta to javafx.fxml;
    exports com.example.ofertedevacanta;

    opens com.example.ofertedevacanta.service to javafx.fxml;
    exports com.example.ofertedevacanta.service;

    opens com.example.ofertedevacanta.domain to javafx.fxml;
    exports com.example.ofertedevacanta.domain;

    opens com.example.ofertedevacanta.repository to javafx.fxml;
    exports com.example.ofertedevacanta.repository;

    opens com.example.ofertedevacanta.controllers to javafx.fxml;
    exports com.example.ofertedevacanta.controllers;

    opens com.example.ofertedevacanta.utils to javafx.fxml;
    exports com.example.ofertedevacanta.utils;
}