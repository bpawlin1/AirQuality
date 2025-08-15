#include "Adafruit_LC709203F.h"
#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include "Adafruit_PM25AQI.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_SHT4x.h"
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
#define CONNECTION_TIMEOUT 10
#define ARDUINO_ADAFRUIT_FEATHER_ESP32S2

const char* ssid = "xxx"; 
const char* password = "xxxxx";
const char* serverName = "http://xxx.xx.xx.xxx:xxx/addShedWeather/";

float batt_volt = 0;
float batt_perc = 0;
float batt_temp = 0;
float bme_temp = 0;
float bme_humidity = 0;
float bme_pressure = 0;
float bme_altitude = 0;
float bme_gas = 0;
float pm_1 = 0;
float pm_25 = 0;
float pm_10 = 0;

Adafruit_BME280 bme; // I2C
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
Adafruit_LC709203F lc;

uint32_t timestamp = millis();

void enableInternalPower()
{
  #if defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
    pinMode(PIN_I2C_POWER, INPUT);
    delay(1);
    bool polarity = digitalRead(PIN_I2C_POWER);
    Serial.print(polarity);
    pinMode(PIN_I2C_POWER, OUTPUT);
    digitalWrite(PIN_I2C_POWER, !polarity);
  #endif
}

void disableInternalPower()
{
  #if defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
    pinMode(PIN_I2C_POWER, INPUT);
    delay(1);
    bool polarity = digitalRead(PIN_I2C_POWER);
    Serial.print(polarity);
    pinMode(PIN_I2C_POWER, OUTPUT);
    digitalWrite(PIN_I2C_POWER, polarity);
  #endif
}

void battery() {
  Serial.print("Batt Voltage: "); Serial.println(lc.cellVoltage(), 3);
  Serial.print("Batt Percent: "); Serial.println(lc.cellPercent(), 1);
  Serial.print("Batt Temp: "); Serial.println(lc.getCellTemperature(), 1);
  batt_volt = lc.cellVoltage();
  batt_perc = lc.cellPercent();
  batt_temp = lc.getCellTemperature();

}

void particleSensorReading(){
  delay(15000);
  PM25_AQI_Data data;
  
  if (! aqi.read(&data)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
    return;
  }
  pm_1 = data.pm10_env;
  pm_25 = data.pm25_env;
  pm_10 = data.pm100_env;
  delay(1000);
}

void bme688Reading(){
  sensors_event_t humidity, temp;
  
  uint32_t timestamp = millis();
  sht4.getEvent(&humidity, &temp);
  timestamp = millis() - timestamp;

  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  Serial.print("Read duration (ms): ");
  Serial.println(timestamp);

  Serial.print(F("Temperature = "));


  bme_temp = temp.temperature * 9/5 + 32;
  bme_humidity = humidity.relative_humidity;
}

void postData() 
{
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "device=ShedWeather&bme_temp=" + String(bme_temp) + "&bme_humidity=" + String(bme_humidity) + "&bme_pressure=" + String(bme_pressure) + "&bme_altitude=" + String(bme_altitude) + "&bme_gas=" + String(bme_gas)+ "&pm_1=" + String(pm_1) + "&pm_25=" + String(pm_25)+ "&pm_10=" + String(pm_10) + "&batt_volt=" + String(batt_volt) + "&batt_perc=" + String(batt_perc);           
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void BME280() {

    bme_pressure = bme.readPressure() / 100.0F;
    bme_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

}

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print("\nShed weather demo");
  // For the Feather ESP32-S2, we need to enable I2C power first!
  // this section can be deleted for other boards
  
  enableInternalPower();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\nconnecting");
  int timeout_counter = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    timeout_counter++;
    if(timeout_counter >= CONNECTION_TIMEOUT*5){
      Serial.print("Error: Restarting WIFI");
      ESP.restart();
    }
  }
  Serial.print("");
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  
  delay(5000);
  
  //Battery Set up
  if (!lc.begin()) {
    Serial.print(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    Serial.print(F("Error: Battery restart"));
    delay(10000);
    ESP.restart();
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);


  lc.setThermistorB(3950);
  Serial.print("Thermistor B = "); Serial.println(lc.getThermistorB());
  lc.setPackSize(LC709203F_APA_3000MAH);
  lc.setAlarmRSOC(25);

  Serial.println("Adafruit SHT4x test");
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    Serial.print(F("Error: sht restart"));
    delay(10000);
    ESP.restart();
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);


  if (! aqi.begin_I2C()) { 
    Serial.println("Could not find PM 2.5 sensor!");
    Serial.print(F("Error: pm restart"));
    delay(10000);
    ESP.restart();
  }

  Serial.println("PM25 found!");

  Serial.println(F("BME280 test"));

  unsigned status;
    
  status = bme.begin();  

  if (!status) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print(F("Error: BME restart"));
    delay(10000);
    ESP.restart();
  }

  delay(5000);
  bme688Reading();
  particleSensorReading();
  BME280();
  battery();
  postData();
  delay(5000);

  disableInternalPower();
  //ESP.deepSleep(200e6);
  esp_sleep_enable_timer_wakeup(600e6);
  esp_deep_sleep_start();
  //ESP.deepSleep(600e6);

}

void loop() {
}
