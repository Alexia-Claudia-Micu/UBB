module com.example.lockmechanism {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lockmechanism to javafx.fxml;
    exports com.example.lockmechanism;
}