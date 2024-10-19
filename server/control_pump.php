<?php
if (isset($_GET['action'])) {
    $action = $_GET['action'];
    file_put_contents('pump_control.txt', $action, LOCK_EX); // 명령을 텍스트 파일에 저장
    echo "Pump control command received: " . $action;
}
?>
