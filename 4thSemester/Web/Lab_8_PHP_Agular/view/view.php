<?php
require_once '../model/entity/Car.php';

class View {

    public function __construct() {
    }

    public function output($param) {
        echo json_encode($param);
    }

    public function returnResult($result) {
        echo "{\"result\" : \"$result\"}";
    }

}
?>
