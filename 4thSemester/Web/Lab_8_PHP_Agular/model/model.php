<?php
require_once '../repo/DBUtils.php';
require_once 'entity/car.php'; // Update the include to car.php

class Model{
    private $db;

    public function __construct()
    {
        $this->db = new DBUtils();
    }

    public function getModels() // Previously getTypes
    {
        $modelsSet = $this->db->getModels(); // Update to match your database function
        $models = array();
        foreach($modelsSet as $m){
            array_push($models, $m['model']);
        }
        return $models;
    }

    public function getColors(){ // Previously getFormats
        $colorsSet = $this->db->getColors(); // Update to match your database function
        $colors = array();
        foreach($colorsSet as $c){
            array_push($colors, $c['color']);
        }
        return $colors;
    }

    public function getCarsByModel($model){ // Previously getFilteredDocsByType
        $resultSet = $this->db->getCarsByModel($model); // Update to match your database function
        $cars = array();
        foreach($resultSet as $key=>$val){
            $car = new Car($val['id'], $val['model'], $val['enginePower'], $val['fuel'], $val['price'], $val['color'], $val['age'], $val['history']);
            array_push($cars, $car);
        }
        return $cars;
    }

    public function getCarsByColor($color){ // Previously getFilteredDocsByFormat
        $resultSet = $this->db->getCarsByColor($color); // Update to match your database function
        $cars = array();
        foreach($resultSet as $key=>$val){
            $car = new Car($val['id'], $val['model'], $val['enginePower'], $val['fuel'], $val['price'], $val['color'], $val['age'], $val['history']);
            array_push($cars, $car);
        }
        return $cars;
    }

    public function selectAllCars(){ // Previously selectAllDocuments
        $resultSet = $this->db->selectAllCars(); // Update to match your database function
        $cars = array();
        foreach($resultSet as $key=>$val){
            $car = new Car($val['id'], $val['model'], $val['enginePower'], $val['fuel'], $val['price'], $val['color'], $val['age'], $val['history']);
            array_push($cars, $car);
        }
        return $cars;
    }

    public function addCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history){ // Previously addDocument
        return $this->db->addCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history); // Update to match your database function
    }

    public function deleteCar($id){ // Previously deleteDocument
        return $this->db->deleteCar($id); // Update to match your database function
    }

    public function updateCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history){ // Previously updateDocument
        return $this->db->updateCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history); // Update to match your database function
    }

}


?>
