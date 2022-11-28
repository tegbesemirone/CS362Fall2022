/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLPMgo9YwE"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "A7LNh_ZgX3WOe521lolSjbA85jbn1G35"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ARRIS-1D45";
char pass[] = "236005282435";
String sensorVal;
float values[5];
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  if (Serial.available() > 0) {
    sensorVal = Serial.readStringUntil('\n');
    Serial.println("Signal Received");
  }
  // Set incoming value from pin V0 to a variable
  String value = param.asStr();;

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  if (Serial.available() > 0) {
      sensorVal = Serial.readStringUntil('\n');
      Serial.println(sensorVal);
    }
  Blynk.virtualWrite(V0, sensorVal);
  String working = sensorVal;
  String val = "";
  int index = 0;
  for( index; index < 5; index++ ) {
    val = sensorVal.substring(0, sensorVal.indexOf('$'));
    values[index] = val.toFloat();
    sensorVal = sensorVal.substring(sensorVal.indexOf('$')+1);
    //index = index + 1;
  }
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float val4 = values[0];
  float val3 = values[1];
  float val5 = values[2];
  Blynk.virtualWrite(V4, val4);
  Blynk.virtualWrite(V3, val3);
  Blynk.virtualWrite(V5, val5);
  
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  if (Serial.available() > 0) {
    sensorVal = Serial.readStringUntil('\n');
    Serial.println("Signal Received");
  }
  
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
