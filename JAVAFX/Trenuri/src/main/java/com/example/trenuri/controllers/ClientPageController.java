package com.example.trenuri.controllers;

import com.example.trenuri.service.Service;
import com.example.trenuri.utils.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;

import java.time.LocalDate;
import java.util.Date;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientPageController implements Observer {
    private Service service;

    private String departureCity, destinationCity;
    private Long trainId;
    private Date date;

    @FXML
    ComboBox<String> departureCityCB;
    @FXML
    ComboBox<String> destinationCityCB;
    @FXML
    ComboBox<Long> trainIdCB;
    @FXML
    DatePicker datePicker;

    @FXML
    Label label;

    @FXML
    public void initialize() {
        departureCityCB.getSelectionModel().selectedItemProperty().addListener(((observable, oldValue, newValue) -> {
            if (newValue != null) {
                departureCity = newValue;
                updateRoutes();

                trainIdCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.findAllTrainIds(departureCity).
                                spliterator(), false).collect(Collectors.toList())));
            }
        }));
        
        destinationCityCB.getSelectionModel().selectedItemProperty().addListener(((observable, oldValue, newValue) -> {
            if (newValue != null) {
                destinationCity = newValue;
                updateRoutes();
            }
        }));

        trainIdCB.getSelectionModel().selectedItemProperty().addListener(((observable, oldValue, newValue) -> {
            if (newValue != null) {
                trainId = newValue;
            }
        }));

        datePicker.valueProperty().addListener(((observable, oldValue, newValue) -> {
            if (newValue != null) {
                date = java.sql.Date.valueOf(newValue);
            }
        }));
    }

    private void updateRoutes() {
        if (departureCity != null && destinationCity != null) {
            service.findRoutes(departureCity, destinationCity);
        }
    }

    public void setService(Service service) {
        this.service = service;
        initModels();

        service.addObserver(this);

        departureCityCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.findAllCityNames().spliterator(),
                false).collect(Collectors.toList())));

        destinationCityCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.findAllCityNames().spliterator(),
                false).collect(Collectors.toList())));
    }

    public void handleSearch(ActionEvent actionEvent) {
        updateRoutes();
    }

    public void handleBuy(ActionEvent actionEvent) {
        if (departureCity != null && trainId != null && date != null) {
            service.buyTicket(trainId, departureCity, date.toInstant().atZone(java.time.ZoneId.systemDefault()).toLocalDate());
        }
    }

    @Override
    public String getDepartureCity() {
        return departureCityCB.getSelectionModel().getSelectedItem();
    }

    @Override
    public String getDestinationCity() {
        return destinationCityCB.getSelectionModel().getSelectedItem();
    }

    @Override
    public void update(int nr) {
        initModels();
        if (nr == 1) {
            label.setText("");
        } else {
            label.setText(nr - 1 + " other user(s) are looking at the same route");
        }
    }

    private void initModels() {
    }
}
