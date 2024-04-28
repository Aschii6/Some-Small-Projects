package com.example.zboruri;

import com.example.zboruri.controllers.LoginController;
import com.example.zboruri.repository.ClientDbRepo;
import com.example.zboruri.repository.FlightDbRepo;
import com.example.zboruri.repository.TicketDbRepo;
import com.example.zboruri.service.ClientService;
import com.example.zboruri.service.FlightService;
import com.example.zboruri.service.Service;
import com.example.zboruri.service.TicketService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class StartApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StartApplication.class.getResource("views/login-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);

        LoginController loginController = fxmlLoader.getController();
        loginController.setService(getService());

        stage.setTitle("Zboruri");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

    private Service getService() {
        ClientDbRepo clientRepo = new ClientDbRepo("jdbc:postgresql://localhost:5432/zboruri",
                "postgres", "parola");

        FlightDbRepo flightRepo = new FlightDbRepo("jdbc:postgresql://localhost:5432/zboruri",
                "postgres", "parola");

        TicketDbRepo ticketRepo = new TicketDbRepo("jdbc:postgresql://localhost:5432/zboruri",
                "postgres", "parola");

        ClientService clientService = new ClientService(clientRepo);
        FlightService flightService = new FlightService(flightRepo);
        TicketService ticketService = new TicketService(ticketRepo);

        return new Service(clientService, flightService, ticketService);
    }
}