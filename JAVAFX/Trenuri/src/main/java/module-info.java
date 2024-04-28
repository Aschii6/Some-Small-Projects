module com.example.trenuri {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.trenuri to javafx.fxml;
    exports com.example.trenuri;

    opens com.example.trenuri.controllers to javafx.fxml;
    exports com.example.trenuri.controllers;

    opens com.example.trenuri.service to javafx.fxml;
    exports com.example.trenuri.service;

    opens com.example.trenuri.repository to javafx.fxml;
    exports com.example.trenuri.repository;

    opens com.example.trenuri.domain to javafx.fxml;
    exports com.example.trenuri.domain;

    opens com.example.trenuri.utils to javafx.fxml;
    exports com.example.trenuri.utils;
}