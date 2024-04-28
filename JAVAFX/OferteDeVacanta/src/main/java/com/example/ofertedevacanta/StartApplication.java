package com.example.ofertedevacanta;

import com.example.ofertedevacanta.controllers.ClientPageController;
import com.example.ofertedevacanta.domain.Client;
import com.example.ofertedevacanta.repository.ClientDbRepo;
import com.example.ofertedevacanta.repository.HotelDbRepo;
import com.example.ofertedevacanta.repository.ReservationDbRepo;
import com.example.ofertedevacanta.repository.SpecialOfferDbRepo;
import com.example.ofertedevacanta.service.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class StartApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = getService();

        List<Client> clients = (List<Client>) service.getAllClients();

        for (Client c : clients) {
            FXMLLoader fxmlLoader = new FXMLLoader(StartApplication.class.getResource("views/client-page-view.fxml"));
            AnchorPane root = (AnchorPane) fxmlLoader.load();

            Stage dialogStage = new Stage();
            dialogStage.initModality(Modality.WINDOW_MODAL);
            Scene scene = new Scene(root);

            ClientPageController clientPageController = fxmlLoader.getController();
            clientPageController.setService(service, c, dialogStage);

            dialogStage.setTitle(c.getName());
            dialogStage.setScene(scene);
            dialogStage.show();
        }
    }

    public static void main(String[] args) {
        launch();
    }

    private Service getService() {
        HotelDbRepo hotelDbRepo = new HotelDbRepo("jdbc:postgresql://localhost:5432/oferteDeVacanta",
        "postgres", "parola");

        HotelService hotelService = new HotelService(hotelDbRepo);

        SpecialOfferDbRepo specialOfferDbRepo = new SpecialOfferDbRepo("jdbc:postgresql://localhost:5432/oferteDeVacanta",
                "postgres", "parola");

        SpecialOfferService specialOfferService = new SpecialOfferService(specialOfferDbRepo);

        ClientDbRepo clientDbRepo = new ClientDbRepo("jdbc:postgresql://localhost:5432/oferteDeVacanta",
                "postgres", "parola");

        ClientService clientService = new ClientService(clientDbRepo);

        ReservationDbRepo reservationDbRepo = new ReservationDbRepo("jdbc:postgresql://localhost:5432/oferteDeVacanta",
                "postgres", "parola");

        ReservationService reservationService = new ReservationService(reservationDbRepo);

        return new Service(hotelService, specialOfferService, clientService, reservationService);
    }
}