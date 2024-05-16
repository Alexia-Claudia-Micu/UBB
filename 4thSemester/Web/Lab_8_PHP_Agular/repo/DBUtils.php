<?php

class DBUtils {

    private $host = "127.0.0.1";
    private $user = "root";
    private $password = "";
    private $db = "ems"; // Change the database name
    private $charset = 'utf8';

    private $pdo;
    private $error;

    public function __construct()
    {
        $dsn = "mysql:host=$this->host;dbname=$this->db;charset=$this->charset";
        $opt = array(
            PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES   => false
        );
        try {
            $this->pdo = new PDO($dsn, $this->user, $this->password, $opt);      
        } catch(PDOException $e) {
            $this->error = $e->getMessage();
            echo "Error connecting to DB: " . $this->error;
        }        
    }

    public function getCarsByColor($color){ // Previously getFilteredDocsByType
        $stmt = $this->pdo->prepare("SELECT * FROM car WHERE color = ?");
        $stmt->execute([$color]);
        return $stmt->fetchAll();
    }

    public function getCarsByModel($model){ // Previously getFilteredDocsByFormat
        $stmt = $this->pdo->prepare("SELECT * FROM car WHERE model = ?");
        $stmt->execute([$model]);
        return $stmt->fetchAll();
    }

    public function getModels(){ // Previously getTypes
        $stmt = $this->pdo->query("SELECT DISTINCT model FROM car");
        return $stmt->fetchAll();
    }

    public function getColors(){ // Previously getFormats
        $stmt = $this->pdo->query("SELECT DISTINCT color FROM car");
        return $stmt->fetchAll();
    }

    public function selectAllCars(){ // Previously selectAllDocuments
        $stmt = $this->pdo->query("SELECT * FROM car");
        return $stmt->fetchAll();
    }

    public function addCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history){ // Previously addDocument
        $stmt = $this->pdo->prepare("INSERT INTO car(id, model, enginePower, fuel, price, color, age, history) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        return $stmt->execute([$id, $model, $enginePower, $fuel, $price, $color, $age, $history]);
    }

    public function deleteCar($id){ // Previously deleteDocument
        $stmt = $this->pdo->prepare("DELETE FROM car WHERE id = ?");
        return $stmt->execute([$id]);
    }

    public function updateCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history){ // Previously updateDocument
        $stmt = $this->pdo->prepare("UPDATE car SET model = ?, enginePower = ?, fuel = ?, price = ?, color = ?, age = ?, history = ? WHERE id = ?");
        return $stmt->execute([$model, $enginePower, $fuel, $price, $color, $age, $history, $id]);
    }

}


?>
