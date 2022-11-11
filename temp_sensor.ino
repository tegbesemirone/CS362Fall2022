// Resources: https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();
} 
void loop() {

  // read in values
  float hum = dht.readHumidity();
  float temp_f = dht.readTemperature(true);
  float temp_c = dht.readTemperature();

  // check that values exist
  if (isnan(hum) || isnan(temp)) {
    Serial.println(F("Value failed to be read in"));
    return;
  }

  // compute heat index
  float heat_index_f = dht.computeHeatIndex(temp_f, hum);
  float hic = dht.computeHeatIndex(temp_c, hum, false);

  // output values
  Serial.print(F(" Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp_c);
  Serial.print(F("°C "));
  Serial.print(temp_f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(heat_index_f);
  Serial.println(F("°F"));
}
