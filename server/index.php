<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Arduino Sensor Data</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/chartjs-adapter-date-fns"></script>
</head>
<body>
    <h1>Arduino Sensor Data1</h1>
    <p>Last updated: <span id="last-updated"></span></p>
    <div id="data">
        <div class="chart-container">
            <canvas id="sensorChart"></canvas>
        </div>
    </div>
    <script src="script.js"></script>
</body>
</html>
