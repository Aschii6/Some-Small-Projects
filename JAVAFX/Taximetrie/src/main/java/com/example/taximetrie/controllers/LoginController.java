package com.example.taximetrie.controllers;

import com.example.taximetrie.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;

public class LoginController {
    private Service service;

    @FXML
    TextField usernameTextField;

    public void setService(Service service) {
        this.service = service;
    }

    public void handleLogin(ActionEvent actionEvent) {
        String username = usernameTextField.getText();
        usernameTextField.clear();


    }
}
