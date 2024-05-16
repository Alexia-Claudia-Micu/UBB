<?php

class Car implements JsonSerializable {
    private $id;
    private $model;
    private $enginePower;
    private $fuel;
    private $price;
    private $color;
    private $age;
    private $history;

    function __construct($id, $model, $enginePower, $fuel, $price, $color, $age, $history) {
        $this->id = $id;
        $this->model = $model;
        $this->enginePower = $enginePower;
        $this->fuel = $fuel;
        $this->price = $price;
        $this->color = $color;
        $this->age = $age;
        $this->history = $history;
    }

    // Getter methods
    public function get_id(){
        return $this->id;
    }

    public function getModel() {
        return $this->model;
    }

    public function getEnginePower() {
        return $this->enginePower;
    }

    public function getFuel() {
        return $this->fuel;
    }

    public function getPrice() {
        return $this->price;
    }

    public function getColor() {
        return $this->color;
    }

    public function getAge() {
        return $this->age;
    }

    public function getHistory() {
        return $this->history;
    }

    // Setter methods
    public function set_id($newId){
        $this->id = $newId;
    }

    public function setModel($model) {
        $this->model = $model;
    }

    public function setEnginePower($enginePower) {
        $this->enginePower = $enginePower;
    }

    public function setFuel($fuel) {
        $this->fuel = $fuel;
    }

    public function setPrice($price) {
        $this->price = $price;
    }

    public function setColor($color) {
        $this->color = $color;
    }

    public function setAge($age) {
        $this->age = $age;
    }

    public function setHistory($history) {
        $this->history = $history;
    }

    // Implementing JsonSerializable interface
        public function jsonSerialize()
    {
        $vars = get_object_vars($this);
        return $vars;

    }

}

?>
