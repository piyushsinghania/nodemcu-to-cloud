#include <ESP8266WiFi.h>

const char *ssid =  "your devie ssid name";     // replace with your wifi ssid and wpa2 key
const char *pass =  "your wifi password";
const char* server = "api.thingspeak.com";

String apiKey = "your api key";                 // write key from your thinkspeak project

String postStr = "";

// Initialize the client library
WiFiClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  delay(10);
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
void loop() { // run over and over
  if (Serial.available()) {
    postStr = Serial.readString();
    Serial.println(postStr);
  }
  if (postStr.length() == 0) 
  {
         Serial.println("Waiting to read from aduino!");
          return;
  }
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(15000);
}
