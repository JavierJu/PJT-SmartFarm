<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Arduino Sensor Data</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/chartjs-adapter-date-fns"></script>

    <!-- <script>
        function controlPump(action) {
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "control_pump.php?action=" + action, true);
            xhttp.onreadystatechange = function() {
                if (xhttp.readyState == 4 && xhttp.status == 200) {
                    alert(xhttp.responseText); // 서버 응답을 경고창으로 표시
                }
            };
        xhttp.send();
        }
    </script> -->

</head>
<body>
    <h1>Arduino Sensor Data</h1>
    <p>Last updated: <span id="last-updated"></span></p>
    <div id="data">
        <div class="chart-container">
            <canvas id="sensorChart"></canvas>
        </div>
    </div>
    <script src="script.js"></script>
    
    <!-- <h2>모터 제어</h2>
    <button onclick="controlPump('on')">모터 켜기</button>
    <button onclick="controlPump('off')">모터 끄기</button>
    <button onclick="controlPump('auto')">자동 제어</button> -->

</body>
</html>
