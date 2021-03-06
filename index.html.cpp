#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(
<!doctype html>
<html lang='en' dir='ltr'>
<head>
    <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
    <meta name='viewport' content='width=device-width, initial-scale=1.0' />
    
    <title>ESP8266 WebSerial</title>

    <link type='text/css' href='style.css' rel='stylesheet'>
    
    <script type='text/javascript' src='main.js'></script>
</head>
<body>
    <div class='navbar navbar-expand-lg navbar-dark bg-primary mb-3'>
        <div class='container'>
            <span class='navbar-brand'>ESP8266 WebSerial</span>
            <div class='navbar-right'>
                <span id='statusBadge' class='btn btn-danger' style='pointer-events: none;'>Disconnected</span>
            </div>
        </div>
    </div>
    <div class='container'>
        <div class='card mb-3'>
            <div class='card-body'>
                <h4 class='card-title'>WebSerial</h4>
                <button class='btn btn-primary mr-3' onclick='requestSystemInfo();'>Log System Info</button>
                <button class='btn btn-danger mr-3' onclick='clearLogView();'>Clear Logs</button>
                <br><br>
                <textarea readonly id='logView' rows=20 placeholder="Logs will appear here..."></textarea>
            </div>
        </div>
    </div>
</body>
</html>
)=====";
