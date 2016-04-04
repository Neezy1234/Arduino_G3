#include <SPI.h>        
#include <WiFi101.h>
#include <WiFiUdp.h>

char ssid[] = "Wifi_Arduino";      			// your network SSID (name)
char pass[] = "aarduino";   			      // your network password
int keyIndex = 0;                 		  // your network key Index number (needed only for WEP)
unsigned int localPort = 8888;          // local port to listen on
bool isLeader = true;
char packetBuffer[255];                 //buffer to hold incoming packet
char  ReplyBuffer[] = "hello";          // a string to send back
IPAddress IPLead;
const int ledPin = PIN_LED_13;
WiFiUDP Udp;

int status = WL_IDLE_STATUS;

void setup() {
    pinMode(ledPin, OUTPUT);

    Serial.begin(115200);
    while (!Serial) {}
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        while (true);
    }


  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid,pass);
    // wait 10 seconds for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
  Udp.beginPacket("255.255.255.255", 8888);
  Udp.write("Je suis le leader");
  Udp.endPacket();
}



void loop() {
    if(isLeader){
      digitalWrite(ledPin, LOW);
    }
    else {
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
        delay(1000);
    }
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      IPAddress remoteIP = Udp.remoteIP();
      localPort = Udp.remotePort();
  
      int len = Udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0;
      }
      String message = packetBuffer;
      message.trim();
      if(message == "Je suis le leader"){
        isLeader = false;
        IPLead = remoteIP;
        Serial.print("Nouveau leader : ");
        Serial.println(IPLead);
      }
    }
}
