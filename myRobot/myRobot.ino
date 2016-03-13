#include <Servo.h>
#include <SPI.h>
#include <WiFi101.h>
#include <Wire.h>

Servo servo1;
Servo servo2;
const int buttonPin = PIN_SW0;
int buttonState = 0;              
char input;                       // input du port Serial afin de controller les Servo
String buffer;                    // buffer permettant de lire l'input du serveur web
char ssid[] = "SSID";             // your network SSID (name)
char pass[] = "PASSWORD";         // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)


int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT_PULLUP);


  servo1.attach(16);
  servo2.attach(17);

  servo1.write(90);
  servo2.write(90);
  
  Serial.begin(115200);
  while(!Serial){
    
  }
  wifi_init();

}

void Move(char input) {
//Move forward, backward, right and left depending on the input.
//Valid input:
// z(forward)
// s(backward)
// q(left)
// d(right)

  switch(input){
      case 'z' :
        // Move forward;
        servo1.write(0);
        servo2.write(180);
        break;
      case 's':
        // Move backward;
        servo1.write(180);
        servo2.write(0);
        break;
      case 'q' :
        // Move left;
        servo1.write(0);
        servo2.write(0);
        break;
      case 'd':
        // Move right;
        servo1.write(180);
        servo2.write(180);
        break;
      case 'p':
        // Pause/Stop both servos
        servo1.write(90);
        servo2.write(90);
        break;
    }
}

void serialMove() {
//Read the serial inputs and call the move function to move accordingly

  if(Serial.available()) {   
    input = Serial.read();
    Serial.println(input);
    Move(input);
   }
}

void remoteMove() {
//Read inputs received on the webserver and call the move function to move accordingly 

  //char input = ??;
  
  //Move(input);
}

void loop() {
  // put your main code here, to run repeatedly
  serialMove();
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = false;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        buffer += c;
        //A chaque itération du while on ajoute le caractère que le client envois
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        // send a standard http response header
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          // output the value of each analog input pin
          client.println("<body>");
          client.println("<a href=\"./4\">Avancer</a><br>");
          client.println("<a href=\"./3\">Droite</a><br>");
          client.println("<a href=\"./2\">Gauche</a><br>");
          client.println("<a href=\"./1\">Reculer</a><br>");
          client.println("<a href=\"./0\">Stop</a>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
          buffer="";
        } 
        else if (c == '\r') 
        {
          //Si le client demande la page http://IP/1 la led s'allume
          if(buffer.indexOf("GET /4")>=0)
            Move('z');
          if(buffer.indexOf("GET /3")>=0)
            Move('d');
          if(buffer.indexOf("GET /2")>=0)
            Move('q');
          if(buffer.indexOf("GET /1")>=0)
            Move('s');            
          //Si le client demande la page http://IP/0 la led s'éteint
          if(buffer.indexOf("GET /0")>=0)
            Move('p');
      }
    }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
void wifi_init(void)
{
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  server.begin();

  //  connected now, so print out the status:
  printWifiStatus();
}

