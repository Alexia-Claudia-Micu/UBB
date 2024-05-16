<?php
use FTP\Connection;

include ('database/connection.php');
session_start();
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $connection = OpenConnection();
    $id = $connection->real_escape_string($_POST['id']);
    $stmt = $connection->prepare("DELETE FROM car WHERE id=?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    CloseConnection($connection);
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

<section class="display_delete">
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
            <th></th>
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
                echo "<td> 
                            <form method='post'>
                                <input type='hidden' name='id' value='" . $row['id'] . "'>
                                <button class='btnDelete' type='submit'>Delete</button>
                            </form>
                      </td>";
                echo "</tr>";
            }
            CloseConnection($con);
            ?>

        </tbody>
    </table>
</section>

</body>
</html>
