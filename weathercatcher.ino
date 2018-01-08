#include <EEPROM.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

//int relayPin = 6; // Pin for Relay Control

int j = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //Set Serial Baud Rate

  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the IR-receiver
  Serial.println("Enabled IRin");

  Serial.println("Humidity (%)\tTemperature (°C)");
  dht.begin(); //Configure Temp and Hum Sensor

  //pinMode(8, OUTPUT); //Configure Pin of Relay as Output


  lcd.begin(16, 2); //Configure LCD Display with 16 Columns and 2 Rows
  lcd.print("Measuring...");
  delay(2000);
  lcd.noDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  lcd.clear();
  lcd.print("Temp C");
  lcd.setCursor(9, 0);
  lcd.print("Hum %");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(9, 1);
  lcd.print(humidity);
  delay(1000);

  long i = 0;
  if (irrecv.decode(&results)) {   //irrecv.decode(&results) is 1 for pressed button, 0 for no button pressed
    i = long(results.value);
    if (i == 16761405) { //if "Play" is pressed the LCD is turned on
      lcd.display();
    }
    if (i != 16761405) { //any other key turns the LCD off again
      lcd.noDisplay();
    }
    //Serial.println("i:");
    //Serial.println(results.value);
    irrecv.resume();
  }

  Serial.print(humidity);
  Serial.print("\t\t");
  Serial.println(temperature);
  if (j == 900000) { // Every roughly 15 min the values are saved in EEPROM
    save(humidity, temperature);
    j = 0;
  }
  j++;  
}

void save(float humidity, float temperature) { //Saves the value of humidity and temperature in EEPROM
  int i = 0;
  byte hum = byte(humidity);
  byte temp = byte(temperature);
  EEPROM.update(i, hum);
  i++;
  EEPROM.update(i,temp);
  i++;
  return;
}
