<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
        <title>Sensor Data Input</title>
    </head>   
    <body>
        <form action="process_R4.php" method="post">
            <p>Temperature: <input type="number" step="0.1" name="temperature" required></p>
            <p>Humidity: <input type="number" step="0.1" name="humidity" required></p>
            <p>Light: <input type="number" step="0.1" name="light" required></p>
            <p>Soil Moisture: <input type="number" step="0.1" name="soil_moisture" required></p>
            <p><input type="submit" value="Submit" /></p>            
        </form>
    </body>
</html>