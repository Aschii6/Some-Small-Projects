package com.example.faptebune;

import com.example.faptebune.controllers.StartController;
import com.example.faptebune.repository.NeedRepo;
import com.example.faptebune.repository.PersonRepo;
import com.example.faptebune.service.NeedService;
import com.example.faptebune.service.PersonService;
import com.example.faptebune.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class StartApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StartApplication.class.getResource("views/start-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);

        StartController startController = fxmlLoader.getController();
        startController.setService(getService());

        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

    private Service getService() {
        PersonRepo personRepo = new PersonRepo("jdbc:postgresql://localhost:5432/fapteBune",
                "postgres", "parola");

        PersonService personService = new PersonService(personRepo);

        NeedRepo needRepo = new NeedRepo("jdbc:postgresql://localhost:5432/fapteBune",
                "postgres", "parola");

        NeedService needService = new NeedService(needRepo);

        return new Service(personService, needService);
    }
}