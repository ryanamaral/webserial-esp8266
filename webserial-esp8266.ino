// WebSerial ESP-8266
//
// Hardware:
// * ESP-01S (ESP-8266)
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>

const char *ssid = "WebSerial-2022";
const char *psk = "xUEzxbg98MN9rjcNrsmBvRRkYNxK4FHDRvxmp2rc6chgpFx9ydDzQFvyyCdzdes";
// https://zxing.org/w/chart?cht=qr&chs=350x350&chld=L&choe=UTF-8&chl=WIFI%3AS%3AWebSerial-2022%3BT%3AWPA%3BP%3AxUEzxbg98MN9rjcNrsmBvRRkYNxK4FHDRvxmp2rc6chgpFx9ydDzQFvyyCdzdes%3B%3B
// Tool to generate WiFi QR-Codes: http://zxing.appspot.com/generator/

extern const char index_html[];
extern const char style_css[];
extern const char main_js[];
#define PORT_HTTP 80
#define PORT_WEBSOCKET 81
#define PORT_DNS 53
ESP8266WebServer server(PORT_HTTP);
WebSocketsServer webSocket = WebSocketsServer(PORT_WEBSOCKET);
String subnetMask = "255.255.255.128";
IPAddress staticIpAddress(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 128); // = 126 usable IP addresses
const int ssidMaxClient = 2;
const int ssidChannel = 7;
const bool ssidHidden = false;
DNSServer dnsServer;
static uint8_t connectedClients = 0;
String logString;
unsigned long lastDumpLogsMillis; // init in setup()


///////////////////
// WebSerial Log //
///////////////////

void log(String value, bool newLine) {
  if (connectedClients > 0) {
    if (newLine) {
      broadcastString("println", value);
    } else {
      broadcastString("print", value);
    }
  } else {
    logString += value;
    if (newLine) {
      logString += "\n";
    }
  }
}

void println() {
  Serial.println();
  log("", true);
}

void println(String value) {
  Serial.println(value);
  log(value, true);
}

void println(uint8_t value) {
  Serial.println(String(value));
  log(String(value), true);
}

void println(uint16_t value) {
  Serial.println(String(value));
  log(String(value), true);
}

void println(uint32_t value) {
  Serial.println(String(value));
  log(String(value), true);
}

void println(unsigned long value) {
  Serial.println(String(value));
  log(String(value), true);
}

void print(String value) {
  Serial.print(value);
  log(value, false);
}

void print(int value) {
  Serial.print(String(value));
  log(String(value), false);
}

void print(long value) {
  Serial.print(String(value));
  log(String(value), false);
}

void dumpCachedLogs() {
  logString = "";
}


//////////
// LOOP //
//////////

void loop() {
  unsigned long now = millis();

  // DNS
  dnsServer.processNextRequest();

  // WebSockets
  webSocket.loop();

  // Listen for HTTP requests
  server.handleClient();

  if ((now - lastDumpLogsMillis) > (1000 * 60 * 10)) { // dump logs every 10min
    dumpCachedLogs();
    lastDumpLogsMillis = now;
  }
}

/*
   Setup WiFi AP + DNS (for redirect)
*/
void wifiSetupAccessPointMode() {
  print("Setting soft-AP configuration... ");
  WiFi.mode(WIFI_AP);
  WiFi.setSleepMode(WIFI_NONE_SLEEP); // default=MODEM_SLEEP
  println(WiFi.softAPConfig(staticIpAddress, staticIpAddress, subnet) ? "Ready" : "Failed!");

  print("Starting soft-AP... ");
  println(WiFi.softAP(ssid, psk, ssidChannel, ssidHidden, ssidMaxClient) ? "Ready" : "Failed!");

  delay(500); // Without delay I've seen the IP address blank
  IPAddress ipAddress = WiFi.softAPIP();

  print("Access Point \"");
  print(ssid);
  println("\" started");
  print("AP IP address: ");
  println(toStringIp(ipAddress));
  println();

  // Setup the DNS server redirecting all http requests
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(PORT_DNS, "*", ipAddress);
}

/////////////////////////
// WebServer Functions //
/////////////////////////

void setupWebServer() {
  println("HTTP server setup");
  server.on("/", handleIndexHtml);
  server.on("/style.css", handleStyleCss);
  server.on("/main.js", handleMainJs);
  server.on("/isRunning", handleIsRunning);
  server.on("/logCached", handleLogCached);
  server.on("/systemInfo", handleSystemInfo);
  server.on("/generate_204", handleCaptivePortal); // Android captive portal
  server.on("/fwlink", handleCaptivePortal);       // Microsoft captive portal
  server.onNotFound(handleNotFound);
  server.begin(); // WebServer start

  println("HTTP server started");
  println();
}

void handleIndexHtml() {
  server.send_P(200, "text/html", index_html);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleStyleCss() {
  server.send_P(200, "text/css", style_css);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleMainJs() {
  server.send_P(200, "application/javascript", main_js);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleNotFound() {
  printRequest();
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(404, "text/plain", "404 Page Not Found");
}

void handleIsRunning() {
  server.send(200, "text/plain", "true");
}

void handleLogCached() {
  server.send(200, "text/plain", logString);
  dumpCachedLogs();
}

/*
   Callback for Captive Portal web page

   Android: http://10.0.0.1/generate_204
   Microsoft: http://10.0.0.1/fwlink
*/
void handleCaptivePortal() {
  printRequest();
  println("Request redirected to captive portal");

  server.sendHeader("Location", String("http://") + toStringIp(staticIpAddress), true);
  server.send(302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  //server.client().stop(); // Stop is needed because we sent no content length
}

/*
  Print the URI and query string of the current request
*/
void printRequest() {
  print("Received HTTP request for: ");
  print(server.uri());
  println();
}

/**
  IP to String
*/
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

void handleSystemInfo() {
  println();
  println("Network Info:");
  println("SSID: " + String(ssid));
  println("MAC Address: " + WiFi.macAddress());
  println("Subnet Mask: " + subnetMask);
  println("Gateway: " + toStringIp(WiFi.softAPIP()));
  println();
  println("System Info:");
  print("Heap: "); println(system_get_free_heap_size());
  print("Boot Vers: "); println(system_get_boot_version());
  print("CPU: "); println(system_get_cpu_freq());
  print("SDK: "); println(system_get_sdk_version());
  print("Chip ID: "); println(system_get_chip_id());
  print("Flash ID: "); println(spi_flash_get_id());
  print("Flash Size: "); println(ESP.getFlashChipRealSize());
  print("Vcc: "); println(ESP.getVcc());
  println();
}


////////////////
// WebSockets //
////////////////

void broadcastBool(String name, bool value) {
  String json = "{\"name\":\"" + name + "\",\"value\":" + value + "}";
  webSocket.broadcastTXT(json);
}

void broadcastInt(String name, uint8_t value) {
  String json = "{\"name\":\"" + name + "\",\"value\":" + String(value) + "}";
  webSocket.broadcastTXT(json);
}

void broadcastString(String name, String value) {
  String json = "{\"name\":\"" + name + "\",\"value\":\"" + String(value) + "\"}";
  webSocket.broadcastTXT(json);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED: {
        println("<WebSocket> Disconnected");
        connectedClients--;
        print("Connected Clients: ");
        println(connectedClients);
        break;
      }
    case WStype_CONNECTED: {
        connectedClients++;
        IPAddress ip = webSocket.remoteIP(num);
        print("Client IP: ");
        println(toStringIp(ip));
        print("Connected Clients: ");
        println(connectedClients);

        // send message to connected client
        webSocket.sendTXT(num, "Connected");
        break;
      }
  }
}

void setup() {
  lastDumpLogsMillis = millis();
  logString = String();

  Serial.begin(115200);
  println("------------------------------------");
  println("------------  WebSerial");
  println("------------------------------------");
  println("----> MCU: Esp8266");
  println("----> Version: 1.0");
  println("------------------------------------");
  println("------------- Changelog");
  println("------------------------------------");
  println("----> Print system info");
  println("----> Scroll to end automatically");
  println("----> WebSockets to update logs");
  println("----> print() & println()");
  println("----> Retrieve cached log");
  println("----> WebSerial 100% offline");
  println("----> WiFi AP Mode");
  println("------------------------------------");
  println("Starting...");
  delay(100); // power-up safety delay

  println("Wifi setup");
  wifiSetupAccessPointMode();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  setupWebServer();
}
