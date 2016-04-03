// extracted from https://github.com/djsb/arduino-websocketclient
#include <Ethernet.h>
#include <SPI.h>
#include <WSClient.h>

// Ethernet Configuration
EthernetClient client;
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

// Websocket initialization
WSClient websocket;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Demo example on WSClient usage"));
  Ethernet.begin(mac); // initialize ethernet
  Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
  delay(300); // this is arduino baby ;-)

  // Connect and test websocket server connectivity
  if (client.connect("echo.websocket.org", 80)) {
    Serial.println("Connected");
  } 
  else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Define path and host for Handshaking with the server
  websocket.path = "/";
  websocket.host = "echo.websocket.org";

  if (websocket.handshake(client)) {
    Serial.println("Handshake successful");
  } 
  else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }
  }

}


void loop() {
  String data;

  if (client.connected()) {
    data = websocket.getData();
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }

    Serial.println(F("")); Serial.println(F("Sending Data"));
    websocket.sendData("echo test");
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }

  delay(3000);  // wait to fully let the client disconnect

}