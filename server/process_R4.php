<?php
$servername = "localhost";
$username = "javier";
$password = "@Javierju12";
$dbname = "smartfarm_sensordata";

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

    // Validate data (check if they are numeric)
    if (is_numeric($temperature) && is_numeric($humidity) && is_numeric($light) && is_numeric($soil_moisture)) {

        // Prepare and bind statement to prevent SQL injection
        $stmt = $conn->prepare("INSERT INTO sensor_readings_R4 (temperature, humidity, light, soil_moisture) VALUES (?, ?, ?, ?)");
        $stmt->bind_param("dddd", $temperature, $humidity, $light, $soil_moisture);

        if ($stmt->execute()) {
            echo "New record created successfully";
        } else {
            echo "Error: " . $stmt->error;
        }

        $stmt->close();
    } else {
        echo "Invalid input data.";
    }
} else {
    echo "No data received";
}

$conn->close();
?>
