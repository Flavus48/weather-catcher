#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Humidity (%)\tTemperature (°C)");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(4000);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print(humidity);
  Serial.print("\t\t");
  Serial.println(temperature);
}
