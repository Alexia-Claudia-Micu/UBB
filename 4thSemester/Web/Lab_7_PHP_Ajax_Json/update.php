<?php
use FTP\Connection;
include ('database/connection.php');
session_start();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $con = OpenConnection();
    
    if (isset($_POST['update'])) {
        $id = $_POST['id'];
        $model = $_POST['model'];
        $enginePower = $_POST['enginePower'];
        $fuel = $_POST['fuel'];
        $price = $_POST['price'];
        $color = $_POST['color'];
        $age = $_POST['age'];
        $history = $_POST['history'];
        
        $stmt = $con->prepare("UPDATE Car SET model=?, enginePower=?, fuel=?, price=?, color=?, age=?, history=? WHERE id=?");
        $stmt->bind_param("sisisisi", $model, $enginePower, $fuel, $price, $color, $age, $history, $id);
        $stmt->execute();
    }

    CloseConnection($con);
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Car Information Update</title>
    <script src="https://code.jquery.com/jquery-3.3.1.js"></script>
    <link rel="stylesheet" type="text/css" href="style.css">
    <script type="text/javascript" src="script.js"></script>
</head>

<body>
    <button class="home" type="button" onclick="location.href='./index.html'">HOME</button>
    <br>

    <section class="update_form">
        <form action="update.php" method="post">
            <input id="id" type="text" name="id" placeholder="ID">
            <input id="model" type="text" name="model" placeholder="Model">
            <input id="enginePower" type="text" name="enginePower" placeholder="Engine Power">
            <input id="fuel" type="text" name="fuel" placeholder="Fuel">
            <input id="price" type="text" name="price" placeholder="Price">
            <input id="color" type="text" name="color" placeholder="Color">
            <input id="age" type="text" name="age" placeholder="Age">
            <input id="history" type="text" name="history" placeholder="History">
            <input id="update" type="submit" name="update" value="Update Car Information">
        </form>
    </section>

    <section class="display_update">
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
                <th>Actions</th>
            </thead>
            <tbody>
                <?php
                $con = OpenConnection();
                $result_set = mysqli_query($con, "SELECT * FROM Car");
                
                while($row = mysqli_fetch_array($result_set)){
                    echo "<tr>";
                    echo "<td class='carId'>" . $row['id'] . "</td>";
                    echo "<td class='carModel'>" . $row['model'] . "</td>";
                    echo "<td class='carEnginePower'>" . $row['enginePower'] . "</td>";
                    echo "<td class='carFuel'>" . $row['fuel'] . "</td>";
                    echo "<td class='carPrice'>" . $row['price'] . "</td>";
                    echo "<td class='carColor'>" . $row['color'] . "</td>";
                    echo "<td class='carAge'>" . $row['age'] . "</td>";
                    echo "<td class='carHistory'>" . $row['history'] . "</td>";
                    echo "<td> <button class='btnUpdate' type='button'>Update</button> </td>";
                    echo "</tr>";
                }
                CloseConnection($con);
                ?>
            </tbody>
        </table>
    </section>
</body>
</html>
