<?php
include 'config.php';

$sql = "SELECT DATE_FORMAT(created_at, '%Y-%m-%d %H:00:00') as time, 
               AVG(temperature) as temperature, 
               AVG(humidity) as humidity, 
               AVG(light) as light, 
               AVG(soil_moisture) as soil_moisture
        FROM sensor_readings_R4
        WHERE created_at >= NOW() - INTERVAL 24 HOUR
        GROUP BY time
        ORDER BY time ASC";
$result = $conn->query($sql);

$data = array();
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
}
$conn->close();

header('Content-Type: application/json');
echo json_encode($data);
?>
