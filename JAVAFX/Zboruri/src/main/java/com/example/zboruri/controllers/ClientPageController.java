package com.example.zboruri.controllers;

import com.example.zboruri.domain.Client;
import com.example.zboruri.domain.Flight;
import com.example.zboruri.domain.SuperFlight;
import com.example.zboruri.domain.Ticket;
import com.example.zboruri.service.Service;
import com.example.zboruri.service.ServiceException;
import com.example.zboruri.utils.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientPageController implements Observer {
    private Service service;
    private Client client;
    private Stage stage;

    private String filterFrom, filterTo;
    private LocalDateTime filterDate;

    ObservableList<Ticket> ticketsModel = FXCollections.observableArrayList();

    @FXML
    TableView<Ticket> ticketsTableView;
    @FXML
    TableColumn<Ticket, String> usernameColumn;
    @FXML
    TableColumn<Ticket, Long> flightIdColumn;
    @FXML
    TableColumn<Ticket, LocalDateTime> purchaseTimeColumn;

    ObservableList<SuperFlight> flightsModel = FXCollections.observableArrayList();

    @FXML
    TableView<SuperFlight> flightsTableView;
    @FXML
    TableColumn<SuperFlight, String> fromColumn;
    @FXML
    TableColumn<SuperFlight, String> toColumn;
    @FXML
    TableColumn<SuperFlight, LocalDateTime> depTimeColumn;
    @FXML
    TableColumn<SuperFlight, LocalDateTime> landTimeColumn;
    @FXML
    TableColumn<SuperFlight, Integer> seatsColumn;
    @FXML
    TableColumn<SuperFlight, Integer> freeSeatsColumn;

    @FXML
    ComboBox<String> fromCB;
    @FXML
    ComboBox<String> toCB;
    @FXML
    DatePicker datePicker;

    @FXML
    public void initialize() {
        ticketsTableView.setItems(ticketsModel);
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        flightIdColumn.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        purchaseTimeColumn.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));

        flightsTableView.setItems(flightsModel);
        fromColumn.setCellValueFactory(new PropertyValueFactory<>("from"));
        toColumn.setCellValueFactory(new PropertyValueFactory<>("to"));
        depTimeColumn.setCellValueFactory(new PropertyValueFactory<>("departureTime"));
        landTimeColumn.setCellValueFactory(new PropertyValueFactory<>("landingTime"));
        seatsColumn.setCellValueFactory(new PropertyValueFactory<>("seats"));
        freeSeatsColumn.setCellValueFactory(new PropertyValueFactory<>("freeSeats"));

        fromCB.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                filterFrom = newValue;
                filterFlights();
            }
        });

        toCB.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                filterTo = newValue;
                filterFlights();
            }
        });

        datePicker.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                filterDate = newValue.atStartOfDay();
                filterFlights();
            }
        });
    }

    private void filterFlights() {
        flightsModel.setAll(StreamSupport.stream(service.getAllFlightsFiltered(filterFrom, filterTo, filterDate)
                .spliterator(), false).collect(Collectors.toList()));
    }

    public void setService(Service service, Client user, Stage stage) {
        this.service = service;
        this.client = user;
        this.stage = stage;

        service.addObserver(this);

        initModels();

        fromCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.getAllFroms().spliterator(),
                false).collect(Collectors.toList())));
        fromCB.getItems().add(0, "");

        toCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.getAllTos().spliterator(),
                false).collect(Collectors.toList())));
        toCB.getItems().add(0, "");
    }

    private void initModels() {
        ticketsModel.setAll(StreamSupport.stream(service.getAllTicketsOfAClient(client.getUsername()).spliterator(),
                        false).collect(Collectors.toList()));

        flightsModel.setAll(StreamSupport.stream(service.getAllFlights().spliterator(), false)
                .collect(Collectors.toList()));
    }

    public void handleBuy(ActionEvent actionEvent) {
        SuperFlight flight = flightsTableView.getSelectionModel().getSelectedItem();

        if (flight == null) {
            MessageAlert.showErrorMessage(null, "No flight selected");
            return;
        }

        if (flight.getFreeSeats() == 0) {
            MessageAlert.showErrorMessage(null, "No more free seats");
            return;
        }

        try {
            service.buyTicket(client.getUsername(), flight.getId());
            initModels();
        } catch (ServiceException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    @Override
    public void update() {
        flightsModel.setAll(StreamSupport.stream(service.getAllFlightsFiltered(filterFrom, filterTo, filterDate).
                        spliterator(), false).collect(Collectors.toList()));
    }
}
