#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <secrets.h>


#define DHTPIN 5 // D1
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

IPAddress local_IP(192, 168, 1, 110);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

WiFiClient wifiClient;

const char *availTopic = "chateau-sadler/chicken-coop/temperature/availability";
const char *tempTopic = "chateau-sadler/chicken-coop/temperature";
const char *humTopic = "chateau-sadler/chicken-coop/humidity";

const char *broker = "192.168.1.104";
const int port = 1883;
PubSubClient client(wifiClient);

float hum;
float temp;

void setup() {
  Serial.begin(115200);
  Serial.println();

  if (!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println("Station failed to configure.");
  }

  Serial.print("Connecting to wifi network: ");
  Serial.print(SECRET_SSID);

  WiFi.begin(SECRET_SSID, SECRET_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi.");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());


  dht.begin();
}

void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature(true);

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("% Temperature: ");
  Serial.print(temp);
  Serial.println(" degrees celsius");

  delay(1000);
}
