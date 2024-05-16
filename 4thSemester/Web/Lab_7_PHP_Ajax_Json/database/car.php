<?php
class Car {
    public $id;
    public $model;
    public $enginePower;
    public $fuel;
    public $price;
    public $color;
    public $age;
    public $history;

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

    function get_id(){
        return $this->id;
    }

    function set_id($newId){
        $this->id = $newId;
    }

    function get_model(){
        return $this->model;
    }

    function set_model($newModel){
        $this->model = $newModel;
    }

    function get_enginePower(){
        return $this->enginePower;
    }

    function set_enginePower($newEnginePower){
        $this->enginePower = $newEnginePower;
    }

    function get_fuel(){
        return $this->fuel;
    }

    function set_fuel($newFuel){
        $this->fuel = $newFuel;
    }

    function get_price(){
        return $this->price;
    }

    function set_price($newPrice){
        $this->price = $newPrice;
    }

    function get_color(){
        return $this->color;
    }

    function set_color($newColor){
        $this->color = $newColor;
    }

    function get_age(){
        return $this->age;
    }

    function set_age($newAge){
        $this->age = $newAge;
    }

    function get_history(){
        return $this->history;
    }

    function set_history($newHistory){
        $this->history = $newHistory;
    }
}
