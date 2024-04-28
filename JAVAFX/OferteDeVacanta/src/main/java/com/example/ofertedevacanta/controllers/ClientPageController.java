package com.example.ofertedevacanta.controllers;

import com.example.ofertedevacanta.domain.*;
import com.example.ofertedevacanta.service.Service;
import com.example.ofertedevacanta.utils.Observer;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientPageController implements Observer {
    private Service service;
    private Client client;
    private String location;
    private Stage stage;
    ObservableList<Hotel> hotelsModel = FXCollections.observableArrayList();
    @FXML
    TableView<Hotel> hotelsTableView;
    @FXML
    TableColumn<Hotel, String> hotelNameColumn;
    @FXML
    TableColumn<Hotel, Integer> noOfRoomsColumn;
    @FXML
    TableColumn<Hotel, Double> pricePerNightColumn;
    @FXML
    TableColumn<Hotel, Type> typeColumn;

    ObservableList<Offer> offersModel = FXCollections.observableArrayList();
    @FXML
    TableView<Offer> offersTableView;
    @FXML
    TableColumn<Offer, String> hotelNameColumn2;
    @FXML
    TableColumn<Offer, Integer> locationColumn2;
    @FXML
    TableColumn<Offer, LocalDate> startDateColumn2;
    @FXML
    TableColumn<Offer, LocalDate> endDateColumn2;

    @FXML
    ComboBox<String> locationCB;

    @FXML
    public void initialize() {
        hotelsTableView.setItems(hotelsModel);

        hotelNameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        noOfRoomsColumn.setCellValueFactory(new PropertyValueFactory<>("noOfRooms"));
        pricePerNightColumn.setCellValueFactory(new PropertyValueFactory<>("pricePerNight"));
        typeColumn.setCellValueFactory(new PropertyValueFactory<>("type"));

        hotelsTableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                openHotelPage(newValue);
            }
        });

        locationCB.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                location = newValue;
                initModels();
            }
        });

        offersTableView.setItems(offersModel);

        hotelNameColumn2.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        locationColumn2.setCellValueFactory(new PropertyValueFactory<>("locationName"));
        startDateColumn2.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        endDateColumn2.setCellValueFactory(new PropertyValueFactory<>("endDate"));
    }

    private void openHotelPage(Hotel hotel) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/ofertedevacanta/views/hotel-page-view.fxml"));
            AnchorPane root = (AnchorPane) loader.load();

            Stage dialogStage = new Stage();
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setTitle(hotel.getName());
            dialogStage.setScene(scene);

            HotelPageController hotelPageController = loader.getController();
            hotelPageController.setService(service, hotel, client);

            dialogStage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void setService(Service service, Client c, Stage stage) {
        this.service = service;
        this.client = c;
        this.stage = stage;

        service.addObserver(this);

        locationCB.setItems(FXCollections.observableArrayList(StreamSupport.stream(service.getAllLocationNames().spliterator(),
                false).collect(Collectors.toList())));

        initModels();
    }

    private void initModels() {
        hotelsModel.setAll(StreamSupport.stream(service.getAllHotelsFromLocation(location).spliterator(), false)
                .collect(Collectors.toList()));

        offersModel.setAll(StreamSupport.stream(service.getAllOffers(client.getFidelityGrade()).spliterator(), false)
                .collect(Collectors.toList()));
    }

    @Override
    public void update() {
        MessageAlert.showMessage(stage, Alert.AlertType.INFORMATION, client.getName(),
                "Another user that likes " + client.getHobby() + " has made a reservation");
    }

    @Override
    public Hobby getHobby() {
        return client.getHobby();
    }

    @Override
    public Long getId() {
        return client.getId();
    }
}
