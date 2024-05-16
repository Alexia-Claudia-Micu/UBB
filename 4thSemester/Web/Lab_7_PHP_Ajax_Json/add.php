<?php
use FTP\Connection;
session_start();
include ('database/connection.php');

if ($_SERVER['REQUEST_METHOD'] == 'POST'){
    $con = OpenConnection();
    
    if(isset($_POST['add'])){
        $model = $con->real_escape_string($_POST['model']);
        $enginePower = $con->real_escape_string($_POST['enginePower']);
        $fuel = $con->real_escape_string($_POST['fuel']);
        $price = $con->real_escape_string($_POST['price']);
        $color = $con->real_escape_string($_POST['color']);
        $age = $con->real_escape_string($_POST['age']);
        $history = $con->real_escape_string($_POST['history']);
        
        $stmt = $con->prepare("INSERT INTO car (model, enginePower, fuel, price, color, age, history) VALUES (?, ?, ?, ?, ?, ?, ?)");
        $stmt->bind_param("sisisis",$model, $enginePower, $fuel, $price, $color, $age, $history);
        $stmt->execute();
    }
    
    CloseConnection($con);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Car Processing</title>
    <script src="https://code.jquery.com/jquery-3.3.1.js"></script>
    <link rel="stylesheet" type="text/css" href="style.css">
    <script type="text/javascript" src="script.js"></script>
</head>
<body>
<button class="home" type="button" onclick="location.href='./index.html'">HOME</button>
<br>

<section class="add_form">
    <form action="add.php" method="post">
        <input id="model" type="text" name="model" placeholder="model">
        <input id="enginePower" type="text" name="enginePower" placeholder="enginePower">
        <input id="fuel" type="text" name="fuel" placeholder="fuel">
        <input id="price" type="text" name="price" placeholder="price">
        <input id="color" type="text" name="color" placeholder="color">
        <input id="age" type="text" name="age" placeholder="age">
        <input id="history" type="text" name="history" placeholder="history">
        <input id="add" type="submit" name="add" value="Add new car">
    </form>
</section>

<section class="display_add">
    <br>
    <table class="display-table">
        <thead>
            <th>ID</th>
            <th>Model</th>
            <th>Engine Power</th>
            <th>Fuel</th>
            <th>Price</th>
            <th>Color</th>
            <th>Age</th>
            <th>History</th>
        </thead>
        <tbody>
            <?php
            $con = OpenConnection();
            $result_set = mysqli_query($con, "SELECT * FROM car");
            
            while($row = mysqli_fetch_array($result_set)){
                echo "<tr>";
                echo "<td>" . $row['id'] . "</td>";
                echo "<td>" . $row['model'] . "</td>";
                echo "<td>" . $row['enginePower'] . "</td>";
                echo "<td>" . $row['fuel'] . "</td>";
                echo "<td>" . $row['price'] . "</td>";
                echo "<td>" . $row['color'] . "</td>";
                echo "<td>" . $row['age'] . "</td>";
                echo "<td>" . $row['history'] . "</td>";
                echo "</tr>";
            }
            CloseConnection($con);
            ?>
        </tbody>
    </table>
</section>
</body>
</html>
