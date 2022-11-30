// Resources: https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int index = 0;
float values[5];

void setup() {
  Serial.begin(115200);
  dht.begin();
} 
void loop() {

  // read in values
  float hum = dht.readHumidity();
  float temp_f = dht.readTemperature(true);
  float temp_c = dht.readTemperature();

  // check that values exist
  if (isnan(hum) || isnan(temp_f) || isnan(temp_c) ) {
    Serial.println(F("Value failed to be read in"));
    return;
  }

  // compute heat index
  float heat_index_f = dht.computeHeatIndex(temp_f, hum);
  float heat_index_c = dht.computeHeatIndex(temp_c, hum, false);

  // construct string to send data
  String to_send = String(hum) + "$" + String(temp_f) + "$" + String(heat_index_f);

  Serial.println(to_send);

  delay(1000);
}
