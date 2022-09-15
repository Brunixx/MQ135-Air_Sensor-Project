#include <MQ135.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include "Wire.h"

// Letra personalizada:
byte calavera[8]{
  0b00000,
  0b01110,
  0b10101,
  0b11111,
  0b01010,
  0b00000,
  0b00000,
  0b00000
};

byte aspa[8]{
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
};

// 0x27 is the address of the I2C :D - Remember it.
LiquidCrystal_I2C lcd(0x27, 20, 4);

DHT dht(3, DHT22);
MQ135 gasSensor(A2);

float temperatura = 0.00;
float humedad = 0.00;

float nivelDeGas = 0.00;
float nivelDeGasEXACTO = 0.00;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);

  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, calavera);

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

  humedad = dht.readHumidity();
  temperatura = dht.readHumidity();
  
  nivelDeGas = gasSensor.getPPM();
  nivelDeGasEXACTO = gasSensor.getCorrectedPPM(temperatura, humedad);

  lcd.setCursor(0,0);
  lcd.print("Calidad del Aire:");
  
  lcd.setCursor(0,1);
  lcd.print("--------------------");
  
  lcd.setCursor(0,2);
  lcd.print("Humedad: ");
  lcd.print(humedad);
  lcd.print("%");
  
  lcd.setCursor(0,3);
  lcd.print("C. del Aire: ");

  lcd.print(nivelDeGasEXACTO);
  
  Serial.println(nivelDeGasEXACTO);
}
