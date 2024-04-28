module com.example.taximetrie {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.taximetrie to javafx.fxml;
    exports com.example.taximetrie;

    opens com.example.taximetrie.controllers to javafx.fxml;
    exports com.example.taximetrie.controllers to javafx.fxml;
}