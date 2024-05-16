<?php
use FTP\Connection;
include ('database/connection.php');
include ('database/car.php');

try {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $con = OpenConnection();
        $model = json_decode(file_get_contents('php://input'), true)['model'];
        $stmt = $con->prepare("SELECT * FROM car WHERE model=?");
        $stmt->bind_param("s", $model);
        $stmt->execute();
        $result_set = $stmt->get_result();
        $cars = array();
        while ($row = mysqli_fetch_array($result_set, MYSQLI_NUM)) {
            $cars[] = new Car($row[0], $row[1], $row[2], $row[3], $row[4], $row[5] ,$row[6],$row[7]);
        }
        header('HTTP/1.1 200 OK');
        echo json_encode($cars);
        CloseConnection($con);
        exit;
    }
} catch (Exception $e) {
    echo json_encode(
        array(
            'status' => false,
            'error' => $e->getMessage(),
            'error_code' => $e->getCode()
        )
    );
    CloseConnection($con);
    exit;
}
?>
