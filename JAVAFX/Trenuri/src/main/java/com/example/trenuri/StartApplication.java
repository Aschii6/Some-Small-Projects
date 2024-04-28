package com.example.trenuri;

import com.example.trenuri.controllers.StartController;
import com.example.trenuri.repository.CityDbRepo;
import com.example.trenuri.repository.TicketDbRepo;
import com.example.trenuri.repository.TrainStationDbRepo;
import com.example.trenuri.service.CityService;
import com.example.trenuri.service.Service;
import com.example.trenuri.service.TicketService;
import com.example.trenuri.service.TrainStationService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class StartApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StartApplication.class.getResource("views/start-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 400, 250);

        Service service = getService();

        StartController startController = fxmlLoader.getController();
        startController.setService(service);

        stage.setTitle("Start Page");
        stage.setScene(scene);
        stage.show();
    }

    private Service getService() {
        CityDbRepo cityDbRepo = new CityDbRepo("jdbc:postgresql://localhost:5432/trenuri",
                "postgres", "parola");

        CityService cityService = new CityService(cityDbRepo);

        TrainStationDbRepo trainsStationDbRepo = new TrainStationDbRepo("jdbc:postgresql://localhost:5432/trenuri",
                "postgres", "parola");

        TrainStationService trainStationService = new TrainStationService(trainsStationDbRepo);

        TicketDbRepo ticketDbRepo = new TicketDbRepo("jdbc:postgresql://localhost:5432/trenuri",
                "postgres", "parola");

        TicketService ticketService = new TicketService(ticketDbRepo);

        return new Service(cityService, trainStationService, ticketService);
    }

    public static void main(String[] args) {
        launch();
    }
}