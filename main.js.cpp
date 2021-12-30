#include <pgmspace.h>
char main_js[] PROGMEM = R"=====(
var connection; // WebSocket
document.addEventListener('DOMContentLoaded', function() {
    requestStatus();
    requestLogCached();
    connection = new WebSocket('ws://10.0.0.1:81/', ['arduino']);
    connection.onopen = function () {
      connection.send('Connect ' + new Date());
    };
    connection.onerror = function (error) {
      console.log('WebSocket Error ', error);
    };
    connection.onmessage = function (m) {
      console.log('Server: ', m.data);
      var json = JSON.parse(m.data);
      if (json != undefined) {
          if (json.name == "print") {
              updateLogView(json.value, false);
          } else if (json.name == "println") {
              updateLogView(json.value, true);
          }
      } else {
          console.log('error parsing json response');
      }
    };
}, false);
function updateConnectionStatus(isConnected) {
    var statusBadge = document.getElementById('statusBadge');
    if (isConnected) {
        statusBadge.className = 'btn btn-success';
        statusBadge.innerText = 'Connected';
    } else {
        statusBadge.className = 'btn btn-danger';
        statusBadge.innerText = 'Disconnected';
    }
}
function logCached(logCache) {
    if (logCache === "") {
        return;
    }
    var logView = document.getElementById('logView');
    var logTemp = logView.value;
    logView.value = logCache + logTemp;
    logView.scrollTop = logView.scrollHeight;
}
function updateLogView(logText, printNewLine) {
    if (logText === "") {
        return;
    }
    var logView = document.getElementById('logView');
    var timestamp = new Date().toLocaleTimeString();
    logView.value += '[';
    logView.value += timestamp;
    logView.value += '] ';
    logView.value += logText;
    logView.value += '\n';
    if (printNewLine === true) logView.value += '\n';
    logView.scrollTop = logView.scrollHeight;
}
function clearLogView() {
    var logView = document.getElementById('logView');
    logView.value = '';
}
function requestSystemInfo() {
    var uri = '/systemInfo';
    var xhr = new XMLHttpRequest();
    xhr.open('GET', uri);
    xhr.send();
}
function requestLogCached() {
    var logRequest = new XMLHttpRequest();
    logRequest.open('GET', '/logCached');
    logRequest.onreadystatechange = function() {
        if (logRequest.readyState == 4) {
            if (logRequest.status == 200) {
                logCached(logRequest.response);
            }
        }
    }
    logRequest.send();
}
function requestStatus() {
    var statusRequest = new XMLHttpRequest();
    statusRequest.open('GET', '/isRunning');
    statusRequest.onreadystatechange = function() {
        if (statusRequest.readyState == 4) {
            if (statusRequest.status == 200) {
                updateConnectionStatus(true);
            } else {
                updateConnectionStatus(false);
            }
        }
    }
    statusRequest.send();
}
)=====";
