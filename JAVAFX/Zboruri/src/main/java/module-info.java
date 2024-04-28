module com.example.zboruri {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.zboruri to javafx.fxml;
    exports com.example.zboruri;

    opens com.example.zboruri.controllers to javafx.fxml;
    exports com.example.zboruri.controllers;

    opens com.example.zboruri.domain to javafx.base;
    exports com.example.zboruri.domain;

    opens com.example.zboruri.repository to javafx.base;
    exports com.example.zboruri.repository;

    opens com.example.zboruri.service to javafx.base;
    exports com.example.zboruri.service;
}