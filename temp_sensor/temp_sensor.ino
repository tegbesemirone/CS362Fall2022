// Resources: https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int iterations = 0;
int index = 0;
float values[5];

void setup() {
  Serial.begin(9600);
  dht.begin();
} 
void loop() {

  if( iterations > 10 ) {
    return;  
  } else {
    iterations++;  
  }

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
  String to_send = String(hum) + "$" + String(temp_f) + "$" + String(temp_c) + "$" + String(heat_index_f) + "$" + String(heat_index_c);

  Serial.println(to_send);
  
  // split data after sending
  splitData(to_send);

  // verify splitting worked
  for( int i = 0; i < 5; i++ ) {
    Serial.print(values[index]);
    Serial.print(" ");
  }
  Serial.println();

  
 /* // output values
  Serial.print(F(" Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp_c);
  Serial.print(F("°C "));
  Serial.print(temp_f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(heat_index_f);
  Serial.println(F("°F"));*/
}

void splitData( String data ) {
  String working = data;
  String val = "";
  index = 0;
  while( index < 5 ) {
    val = data.substring(0, data.indexOf('$'));
    values[index] = val.toFloat();
    Serial.println(values[index]);
    data = data.substring(data.indexOf('$')+1);
    index = index + 1;
  }
}
