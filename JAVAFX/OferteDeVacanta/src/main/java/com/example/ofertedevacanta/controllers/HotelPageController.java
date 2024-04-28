package com.example.ofertedevacanta.controllers;

import com.example.ofertedevacanta.domain.Client;
import com.example.ofertedevacanta.domain.Hotel;
import com.example.ofertedevacanta.domain.SpecialOffer;
import com.example.ofertedevacanta.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class HotelPageController {
    private Service service;
    private Hotel hotel;
    private Client client;

    ObservableList<SpecialOffer> offersModel = FXCollections.observableArrayList();

    LocalDate startDate, endDate;
    @FXML
    DatePicker startDatePicker;
    @FXML
    DatePicker endDatePicker;

    @FXML
    TableView<SpecialOffer> offersTableView;
    @FXML
    TableColumn<SpecialOffer, LocalDate> startDateColumn;
    @FXML
    TableColumn<SpecialOffer, LocalDate> endDateColumn;

    @FXML
    public void initialize(){
        offersTableView.setItems(offersModel);

        startDateColumn.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        endDateColumn.setCellValueFactory(new PropertyValueFactory<>("endDate"));

        startDatePicker.valueProperty().addListener((observable, oldValue, newValue) -> {
            startDate = newValue;
            initModels();
        });

        endDatePicker.valueProperty().addListener((observable, oldValue, newValue) -> {
            endDate = newValue;
            initModels();
        });
    }

    public void setService(Service service, Hotel hotel, Client client) {
        this.service = service;
        this.hotel = hotel;
        this.client = client;

        initModels();
    }

    private void initModels() {
        offersModel.setAll(StreamSupport.stream(service.getAllSpecialOffersFiltered(hotel.getId(), startDate, endDate).spliterator(),
                false).collect(Collectors.toList()));
    }

    public void handleReservation(ActionEvent actionEvent) {
        LocalDate startDate = startDatePicker.getValue();
        LocalDate endDate = endDatePicker.getValue();

        startDatePicker.setValue(null);
        endDatePicker.setValue(null);

        if (startDate == null || endDate == null) {
            MessageAlert.showErrorMessage(null, "Please select a start date and an end date");
            return;
        }

        if (startDate.isAfter(endDate) || startDate.isEqual(endDate)) {
            MessageAlert.showErrorMessage(null, "Start date must be before end date");
            return;
        }

        int noOfNights = endDate.getDayOfYear() - startDate.getDayOfYear();

        try {
            service.addReservation(client.getId(), hotel.getId(), startDate, noOfNights, client.getHobby());
        } catch (RuntimeException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }
}
