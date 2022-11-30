


// include the library code:
#include <LiquidCrystal.h>
String sensorData = "50.0$22.0$91.0";
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String data;
int index = 0;
float values[5];

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

void scroll(int line, char str1[]) {
  
  int a = 40 - strlen(str1);
  
  line = line - 1;
  
  for (int b = a; b <= a + 21; b++) {
  
    for (int c = 0; c <= 20; c++) {
      
      lcd.print(" "); // Clear line
    
    }
    
    lcd.setCursor(b, line);
    
    lcd.print(str1);
    
    delay(500);
  
  }

}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Weather Machine");
  Serial.begin(115200);
  //Serial.println(sensorData);
}

void loop(){
  //Serial.println(sensorData);
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    splitData(data);
    lcd.setCursor(0, 0);
    lcd.print("Heat Idx: "+String(values[2]));
    //char* scroller = values[2].c_str();
    lcd.setCursor(0, 1);
    lcd.print("Temp: "+String(values[1]));
  }
  int i = 0;
  int rand = random(200);
  //char* scroller = data.c_str();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //lcd.print(scroller);
  
}
