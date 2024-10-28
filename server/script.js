document.addEventListener('DOMContentLoaded', (event) => {
    function fetchData() {
        fetch('get_data.php')
            .then(response => response.json())
            .then(data => {
                console.log('Data fetched:', data);

                const lastUpdated = new Date();
                document.getElementById('last-updated').textContent = lastUpdated.toLocaleString();

                const temperatureData = data.map(d => ({ x: new Date(d.time), y: parseFloat(d.temperature) }));
                const humidityData = data.map(d => ({ x: new Date(d.time), y: parseFloat(d.humidity) }));
                const lightData = data.map(d => ({ x: new Date(d.time), y: parseFloat(d.light) }));
                const soilMoistureData = data.map(d => ({ x: new Date(d.time), y: parseFloat(d.soil_moisture) }));

                console.log('Temperature Data:', temperatureData);
                console.log('Humidity Data:', humidityData);
                console.log('Light Data:', lightData);
                console.log('Soil Moisture Data:', soilMoistureData);

                updateChart(sensorChart, temperatureData, humidityData, lightData, soilMoistureData);
            })
            .catch(error => console.error('Error fetching data:', error));
    }

    function updateChart(chart, temperatureData, humidityData, lightData, soilMoistureData) {
        chart.data.datasets[0].data = temperatureData;
        chart.data.datasets[1].data = humidityData;
        chart.data.datasets[2].data = lightData;
        chart.data.datasets[3].data = soilMoistureData;
        chart.update();
    }

    const ctxSensor = document.getElementById('sensorChart').getContext('2d');

    const sensorChart = new Chart(ctxSensor, {
        type: 'line',
        data: {
            datasets: [
                {
                    label: 'Temperature (°C)',
                    data: [],
                    borderColor: 'rgba(255, 99, 132, 1)',
                    borderWidth: 1,
                    fill: false
                },
                {
                    label: 'Humidity (%)',
                    data: [],
                    borderColor: 'rgba(54, 162, 235, 1)',
                    borderWidth: 1,
                    fill: false
                },
                {
                    label: 'Light',
                    data: [],
                    borderColor: 'rgba(255, 206, 86, 1)',
                    borderWidth: 1,
                    fill: false
                },
                {
                    label: 'Soil Moisture',
                    data: [],
                    borderColor: 'rgba(75, 192, 192, 1)',
                    borderWidth: 1,
                    fill: false
                }
            ]
        },
        options: {
            responsive: true, // 창 크기에 따라 그래프 크기 조정
            maintainAspectRatio: false, // 화면 비율에 따라 크기 유지 안함
            aspectRatio: 1, // 가로:세로 비율을 1:1로 설정 (값을 낮추면 세로가 길어짐)
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'hour',
                        tooltipFormat: 'dd.MM.yyyy HH:mm'
                    }
                },
                y: {
                    beginAtZero: true,
                    min: 0, // y축 최소값
                    max: 100, // y축 최대값
                    ticks: {
                        stepSize: 10, // y축 간격을 10으로 설정
                        //callback: function(value) { 
                        //    return value + ' %'; // y축 레이블에 '%' 추가
                        //}
                    },
                }
            }
        }
    });

    setInterval(fetchData, 5000); // 5초마다 데이터 갱신
    fetchData();
});

// function openRelayControl() {
//     window.open(
//         "http://13.208.254.200/Controlpump/index.html", // 팝업으로 열고 싶은 페이지 URL
// "RelayControlPopup",  // 팝업 창의 이름
//         "width=400,height=300,top=100,left=100" // 팝업 크기와 위치 설정
//     );
// }
