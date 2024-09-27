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
            scales: {
                x: {
                    type: 'time',
                    time: {
                        unit: 'hour',
                        tooltipFormat: 'yyyy.MM.dd HH:mm'
                    }
                },
                y: {
                    beginAtZero: true
                }
            }
        }
    });

    setInterval(fetchData, 5000); // 5초마다 데이터 갱신
    fetchData();
});
