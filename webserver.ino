/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010  by dlf (Metodo2 srl)
 modified 31 May 2012  by Tom Igoe
 modified 27 Oct 2015  by Bob Martin

 */

#include <SPI.h>
#include <WiFi101.h>
#include <Wire.h>

String buffer;
char ssid[] = "jawifi";            // your network SSID (name)
char pass[] = "test1234";         // your network password
int keyIndex = 0;                     // your network key Index number (needed only for WEP)


// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = PIN_SW0;    // the number of the pushbutton pin
const int ledPin    = PIN_LED_13; // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup()
{
  // STS Led
  pinMode(PIN_LED_13,OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  wifi_init();
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
  while ( status != WL_CONNECTED)
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

void loop()
{

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // listen for incoming clients

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
          client.println("<a href=\"./1\">Allumer la led</a><br>");
          client.println("<a href=\"./0\">Eteindre la led</a>");
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
          if(buffer.indexOf("GET /1")>=0)
            digitalWrite(PIN_LED_13, LOW);
          //Si le client demande la page http://IP/0 la led s'éteint
          if(buffer.indexOf("GET /0")>=0)
            digitalWrite(PIN_LED_13, HIGH);
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



