<?php

header("Access-Control-Allow-Origin: *");

require_once '../model/model.php';
require_once '../view/view.php';

class Controller
{
    private $view;
    private $model;

    public function __construct()
    {
        $this->view = new View();
        $this->model = new Model();
    }

    public function service()
    {
        if (isset($_GET['action']) && !empty($_GET['action'])) {
            if ($_GET['action'] == "selectAllCars") {
                $this->{$_GET['action']}();
            } else if ($_GET['action'] == 'addCar') {
                $this->{$_GET['action']}($_GET['id'], $_GET['model'], $_GET['enginePower'], $_GET['fuel'], $_GET['price'], $_GET['color'], $_GET['age'], $_GET['history']);
            } else if ($_GET['action'] == 'deleteCar') {
                $this->{$_GET['action']}($_GET['id']);
            } else if ($_GET['action'] == 'updateCar') {
                $this->{$_GET['action']}($_GET['id'], $_GET['model'], $_GET['enginePower'], $_GET['fuel'], $_GET['price'], $_GET['color'], $_GET['age'], $_GET['history']);
            } else if ($_GET['action'] == "getModels") {
                $this->{$_GET['action']}();
            } else if ($_GET['action'] == "getColors") {
                $this->{$_GET['action']}();
            } else if ($_GET['action'] == "getCarsByModel") {
                $this->{$_GET['action']}($_GET['model']);
            } else if ($_GET['action'] == "getCarsByColor") {
                $this->{$_GET['action']}($_GET['color']);
            }
        }
    }

    private function selectAllCars()
    {
        $cars = $this->model->selectAllCars();
        return $this->view->output($cars);
    }

    private function getModels()
    {
        $models = $this->model->getModels();
        $this->view->output($models);
    }

    private function getColors()
    {
        $colors = $this->model->getColors();
        $this->view->output($colors);
    }

    private function getCarsByModel($model)
    {
        $cars = $this->model->getCarsByModel($model);
        $this->view->output($cars);
    }

    private function getCarsByColor($color)
    {
        $cars = $this->model->getCarsByColor($color);
        $this->view->output($cars);
    }

    private function addCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history)
    {
        $result = $this->model->addCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history);
        $this->view->returnResult($result > 0 ? "Success" : "Failure");
    }

    private function deleteCar($id)
    {
        $result = $this->model->deleteCar($id);
        $this->view->returnResult($result > 0 ? "Success" : "Failure");
    }

    private function updateCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history)
    {
        $result = $this->model->updateCar($id, $model, $enginePower, $fuel, $price, $color, $age, $history);
        $this->view->returnResult($result > 0 ? "Success" : "Failure");
    }
}

$controller = new Controller();
$controller->service();

?>
