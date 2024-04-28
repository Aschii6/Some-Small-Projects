package com.example.faptebune.controllers;

import com.example.faptebune.domain.City;
import com.example.faptebune.domain.Person;
import com.example.faptebune.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.IOException;
import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class StartController {
    private Service service;

    @FXML
    TextField lastNameTF;
    @FXML
    TextField firstNameTF;
    @FXML
    TextField usernameTF;
    @FXML
    TextField passwordTF;
    @FXML
    ComboBox<String> cityCB;
    @FXML
    TextField streetTF;
    @FXML
    TextField streetNoTF;
    @FXML
    TextField phoneNoTF;

    ObservableList<Person> personsModel = FXCollections.observableArrayList();
    @FXML
    ListView<Person> personsLV;

    @FXML
    public void initialize() {
        personsLV.setItems(personsModel);

        personsLV.setCellFactory(new Callback<ListView<Person>, ListCell<Person>>() {
            @Override
            public ListCell<Person> call(ListView<Person> param) {
                return new ListCell<Person>() {
                    @Override
                    protected void updateItem(Person item, boolean empty) {
                        super.updateItem(item, empty);
                        if (item != null) {
                            setText(item.getUsername());
                        }
                    }
                };
            }
        });

        personsLV.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                openPersonPage(newValue);
            }
        });

        cityCB.setItems(FXCollections.observableArrayList(Arrays.stream(City.values())
                .map(City::toString).collect(Collectors.toList())));
    }

    private void openPersonPage(Person person) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/com/example/faptebune/views/person-page-view.fxml"));

            AnchorPane root = (AnchorPane) fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle(person.getUsername());
            dialogStage.initModality(Modality.WINDOW_MODAL);

            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            PersonPageController personPageController = fxmlLoader.getController();
            personPageController.setService(service, person);

            dialogStage.show();
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void setService(Service service) {
        this.service = service;
        initModels();
    }

    private void initModels() {
        personsModel.setAll(StreamSupport.stream(service.getAllPersons().spliterator(), false)
                .collect(Collectors.toList()));
    }

    public void handleRegister(ActionEvent actionEvent) {
        String lastName = lastNameTF.getText();
        String firstName = firstNameTF.getText();
        String username = usernameTF.getText();
        String password = passwordTF.getText();
        String city = cityCB.getValue();
        String street = streetTF.getText();
        String streetNo = streetNoTF.getText();
        String phoneNo = phoneNoTF.getText();

        if (lastName.isEmpty() || firstName.isEmpty() || username.isEmpty() || password.isEmpty() || city.isEmpty() ||
                street.isEmpty() || streetNo.isEmpty() || phoneNo.isEmpty()) {
            MessageAlert.showErrorMessage(null, "All fields must be completed");
            return;
        }

        lastNameTF.clear(); firstNameTF.clear(); usernameTF.clear(); passwordTF.clear();
        streetTF.clear(); streetNoTF.clear(); phoneNoTF.clear();

        try {
            service.register(lastName, firstName, username, password, city, street, streetNo, phoneNo);
            initModels();

            Person person = service.getPersonByUsername(username);
            openPersonPage(person);
        } catch (RuntimeException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }
}
