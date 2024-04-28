package com.example.zboruri.controllers;

import com.example.zboruri.domain.Client;
import com.example.zboruri.domain.Ticket;
import com.example.zboruri.service.Service;
import com.example.zboruri.service.ServiceException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDateTime;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class LoginController {
    private Service service;

    ObservableList<Ticket> ticketsModel = FXCollections.observableArrayList();

    @FXML
    TextField usernameTextField;

    @FXML
    TableView<Ticket> ticketsTableView;
    @FXML
    TableColumn<Ticket, String> usernameColumn;
    @FXML
    TableColumn<Ticket, String> flightIdColumn;
    @FXML
    TableColumn<Ticket, LocalDateTime> purchaseTimeColumn;

    public void setService(Service service) {
        this.service = service;
        initModel();
    }

    @FXML
    public void initialize() {
        ticketsTableView.setItems(ticketsModel);
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        flightIdColumn.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        purchaseTimeColumn.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));
    }

    public void handleLogin(ActionEvent actionEvent) {
        String username = usernameTextField.getText();
        usernameTextField.clear();

        if (username.isEmpty()) {
            MessageAlert.showErrorMessage(null, "Username can't be empty");
            return;
        }

        try {
            Client client = service.login(username);

            openClientPage(client);
        } catch (ServiceException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    private void openClientPage(Client client) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/com/example/zboruri/views/client-page-view.fxml"));

            AnchorPane root = (AnchorPane) fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle(client.getName());
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setScene(scene);

            ClientPageController clientPageController = fxmlLoader.getController();
            clientPageController.setService(service, client, dialogStage);

            dialogStage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void initModel() {
        ticketsModel.setAll(StreamSupport.stream(service.getAllTicketsFromDate().spliterator(), false)
                .collect(Collectors.toList()));
    }
}
