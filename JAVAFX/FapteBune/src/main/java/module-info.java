module com.example.faptebune {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    opens com.example.faptebune to javafx.fxml;
    exports com.example.faptebune;

    opens com.example.faptebune.controllers to javafx.fxml;
    exports com.example.faptebune.controllers;

    opens com.example.faptebune.service to javafx.fxml;
    exports com.example.faptebune.service;

    opens com.example.faptebune.utils to javafx.fxml;
    exports com.example.faptebune.utils;

    opens com.example.faptebune.domain to javafx.fxml;
    exports com.example.faptebune.domain;

    opens com.example.faptebune.repository to javafx.fxml;
    exports com.example.faptebune.repository;
}