package com.example.faptebune.controllers;

import com.example.faptebune.domain.Need;
import com.example.faptebune.domain.Person;
import com.example.faptebune.service.Service;
import com.example.faptebune.utils.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDateTime;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class PersonPageController implements Observer {
    private Service service;
    private Person person;

    ObservableList<Need> needsModel = FXCollections.observableArrayList();
    @FXML
    TableView<Need> needsTV;
    @FXML
    TableColumn<Need, String> titleColumn;
    @FXML
    TableColumn<Need, String> descriptionColumn;
    @FXML
    TableColumn<Need, LocalDateTime> deadlineColumn;
    @FXML
    TableColumn<Need, Long> personInNeedIdColumn;
    @FXML
    TableColumn<Need, String> statusColumn;


    @FXML
    public void initialize() {
        needsTV.setItems(needsModel);

        titleColumn.setCellValueFactory(new PropertyValueFactory<>("title"));
        descriptionColumn.setCellValueFactory(new PropertyValueFactory<>("description"));
        deadlineColumn.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        personInNeedIdColumn.setCellValueFactory(new PropertyValueFactory<>("personInNeedId"));
        statusColumn.setCellValueFactory(new PropertyValueFactory<>("status"));

        needsTV.setRowFactory(tableView -> new TableRow<Need>() {
            @Override
            protected void updateItem(Need item, boolean empty) {
                super.updateItem(item, empty);

                setDisable(item == null || item.getPersonHelpingId() != 0);
            }
        });
    }

    public void setService(Service service, Person person) {
        this.service = service;
        this.person = person;

        service.addObserver(this);

        initModels();
    }

    private void initModels() {
        needsModel.setAll(StreamSupport.stream(service.getAllNeedsFromYourCity(person.getCity(), person.getId()).spliterator(),
                false).collect(Collectors.toList()));
    }

    public void handleSolve(ActionEvent actionEvent) {
        if (needsTV.getSelectionModel().getSelectedItem() == null) {
            MessageAlert.showErrorMessage(null, "No need selected");
            return;
        }

        Need need = needsTV.getSelectionModel().getSelectedItem();

        service.updateNeed(need.getId(), person.getId());

        MessageAlert.showMessage(null, Alert.AlertType.INFORMATION,
                person.getLastName() + ' ' + person.getFirstName(), "You are responsible for " + need.getTitle());

        initModels();
    }

    @Override
    public void update() {
        initModels();
        needsTV.getSelectionModel().clearSelection();
    }
}
