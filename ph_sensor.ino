#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 16    
#define lin  2    
#define ende  0x27 

LiquidCrystal_I2C lcd(ende,col,lin); 

const float Vref = 5.0; // Tensão de referência
const int numReadings = 10; // Número de leituras para a média
const float fahrenheitToCelsius = 5.0/9.0; // Fator de conversão

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Expo Anglo 2024");
  lcd.setCursor(0,1);
  lcd.print("Inicializando..");
}

void loop() {
  float sumVoltagePH = 0;
  float sumTemperature = 0;

  lcd.setCursor(15,1); //Mostra indicador de leitura 
  lcd.print(" ");  
  for (int i = 0; i < numReadings; i++) {
    int analogA0 = analogRead(A0);
    int analogA1 = analogRead(A1);

    float voltagePH = analogA0 * Vref / 1024.0;
    float temperatureF = analogA1 * 950.0 / (1024.0 * 10.0); // Temperatura em Fahrenheit
    
    sumVoltagePH += voltagePH;
    sumTemperature += temperatureF;
    delay(100);
  }
  float avgVoltagePH = sumVoltagePH / numReadings;
  float avgTemperature = sumTemperature / numReadings;

  float temperatureC = (avgTemperature - 32) * fahrenheitToCelsius; // Conversão para Celsius
  float pH = 7 + ((2.4 - avgVoltagePH) / 0.18); // Converte para pH

  lcd.setCursor(6,1); //Limpa duas posições a partir da 6 na segunda linha, remove informação de inicialização
  lcd.print("  ");

  lcd.setCursor(0,1);
  lcd.print("pH:");
  lcd.print(pH, 1);
  lcd.setCursor(8,1);
  lcd.print("Tp:");
  lcd.print(temperatureC, 1);

  lcd.setCursor(15,1); //Mostra indicador de leitura 
  lcd.print("*");  

  Serial.print("Valor PH:");
  Serial.println(pH);
  Serial.print("Temperatura:");
  Serial.println(temperatureC);

  delay(1000);
}
