#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 5 // D1
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

float hum;
float temp;

void setup() {
  Serial.begin(115200);
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
