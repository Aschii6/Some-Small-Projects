package com.example.trenuri.controllers;

import com.example.trenuri.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;

public class StartController {
    private Service service;

    public void setService(Service service){
        this.service = service;
    }

    public void handleOpenClientPage(ActionEvent actionEvent) {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/com/example/trenuri/views/client-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();

            Stage dialogStage = new Stage();
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);
            dialogStage.setTitle("Client Page");
            dialogStage.setScene(scene);

            ClientPageController clientPageController = loader.getController();
            clientPageController.setService(service);

            dialogStage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
