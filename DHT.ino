#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_TEMPLATE_ID "TMPL369TOPMSA"
#define BLYNK_TEMPLATE_NAME "AC"
#define BLYNK_AUTH_TOKEN "e6UZCFSTqMCb6IClCfj1e3ei1jwBt_KT"

char auth[] =BLYNK_AUTH_TOKEN; //Enter the Auth code which was send by Blink

char ssid[] = "Asdf  ";  //Enter your WIFI Name
char pass[] = "@bcd#";  //Enter your WIFI Password

#define DHTPIN 2         
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  
  Serial.println("humidity");
  Serial.println(h);
  Serial.println("temperature:");
  Serial.println(t);
  if(h>45.00)
  {
    Blynk.logEvent("notify","High Humidity");
    
  }
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
  
}

void setup()
{
  Serial.begin(115200);
  delay(10);// See the connection status in Serial Monitor
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  
  
  timer.setInterval(1000L, sendSensor);
  
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

 
  
}
