#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>



//const char* ssid = "FRITZ!Box 7312";
//const char* password = "88767327694885648772";

const char* ssid = "TestWLAN-doNotConnect";
const char* password = "NBSWLAN2017";

#define BUFFER_SIZE 100

WiFiClient client;

long now;
long lastMsg;

int val;

HTTPClient http;


void setup() {
  Serial.begin(115200);
  val = analogRead(A0);
  //val = map(val, 0, 1023, 0, 5000);
  Serial.print("ADC Value:");
  Serial.println(val);


  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(" Http Request...");
  
    if(val>178&&val<183)  
    {
      http.begin("http://test6.techahead.de/dataInputIncrease.php?code=2534Ax3&id=1");
    }
    else if(val>188&&val<193)  
    {
      http.begin("http://test6.techahead.de/dataInputIncrease.php?code=2534Ax3&id=2");
    }
    else if(val>196&&val<202)  
    {
      http.begin("http://test6.techahead.de/dataInputIncrease.php?code=2534Ax3&id=3");
    }
    else if(val>203&&val<208)  
    {
      http.begin("http://test6.techahead.de/dataInputIncrease.php?code=2534Ax3&id=4");
    }
  
           
    int httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK)
    {
       Serial.print("HTTP response code ");
       Serial.println(httpCode);
       String response = http.getString();
       Serial.println(response);
    }
    else
    {
       Serial.println("Error in HTTP request");
    }
     
    http.end();
    Serial.println("DONE");
  }

  delay(2000);
  
  // Sleep
  Serial.println("Entering sleep mode");
  ESP.deepSleep(0);
  delay(300);

}

void loop() {
  // Leer lassen 
}


