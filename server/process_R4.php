<?php
$servername = "localhost";
$username = "javier";
$password = "@Javierju12";
$dbname = "test"; // Use the existing database 'test'

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Check if data is sent via POST request
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $temperature = $_POST['temperature'];
    $humidity = $_POST['humidity'];
    $light = $_POST['light'];
    $soil_moisture = $_POST['soil_moisture'];

    $sql = "INSERT INTO sensor_readings_R4 (temperature, humidity, light, soil_moisture)
            VALUES ('$temperature', '$humidity', '$light', '$soil_moisture')";

    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "No data received";
}

$conn->close();
?>
