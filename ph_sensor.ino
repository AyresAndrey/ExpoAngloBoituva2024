#include <Wire.h>               // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h>  // Biblioteca utilizada para fazer a comunicação com o display 16x2 

#define col 16     // Serve para definir o numero de colunas do display utilizado
#define lin  2     // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

int contagem = 0;           // Variável de contagem
float soma_tensao = 0;      // Variável para soma de tensão
float media_tensao = 0;     // Variável que calcula a media
float entrada_A0;           // Variável de leitura do pino A0
float entrada_A1;           // Variável de leitura do pino A1
float tensao;               // Variável para conversão em tensão
float temperatura;          // Variável para temperatura
float soma_temperatura;
float media_temperatura;

void setup() {
  Serial.begin(9600);
  delay(2000);

  lcd.init();      // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear();     // Serve para limpar a tela do display

  lcd.setCursor(0,0); // Coloca o cursor do display na coluna 0 e linha 0 = 1
  lcd.print("Expo Anglo 2024");
}

void loop() {
  soma_tensao = 0;      // Inicia soma_tensão em 0
  soma_temperatura = 0; // Inicia soma_temperatura em 0
  contagem = 0;         // Inicia a contagem em 0
  
  while (contagem < 10) {                   // Executa enquanto contagem menor que 10
    lcd.setCursor(15,1);                    // Mostra indicador de leitura 
    lcd.print("*");     
    
    entrada_A0 = analogRead(A0);            // Lê a entrada analógica
    entrada_A1 = analogRead(A1);            // Lê a entrada analógica
    
    tensao = 5 / 1024.0 * entrada_A0;
    temperatura = entrada_A1 * 1100 / (1024 * 10);
    
    soma_tensao = (soma_tensao + tensao);                   // Soma a tensão anterior com a atual
    soma_temperatura = (soma_temperatura + temperatura);    // Soma a temperatura anterior com a atual
    contagem++;                                             // Soma 1 a variável de contagem
    delay(100);                                             // Aguarda para próxima leitura
  }

  media_tensao = soma_tensao / 10;                    // Calcula a média das leituras
  media_temperatura = soma_temperatura / 10;
  
  float valor_pH = 7 + ((2.5 - media_tensao) / 0.18);           // Calcula valor de pH 
  float valor_temperaturaC = (media_temperatura - 32) * 5 /9;   // Converte temperatura em fahrenheit para celsius

  //Saída para o LCD do PH
  lcd.setCursor(0,1);       // Cursor na linha 2 coluna 0
  lcd.print("pH:");         // Imprime o texto pH
  lcd.setCursor(3,1);
  lcd.print(valor_pH,1);    // Imprime o valor do PH

  //Saída para o LCD da temperatura
  lcd.setCursor(8,1);                   // Cursor na linha 2 coluna 8
  lcd.print("Tp:");                     // Imprime o texto Tp
  lcd.setCursor(11,1);
  lcd.print(valor_temperaturaC,1);      // Imprime o valor da temperatura  

  lcd.setCursor(15,1);     // Limpa indicador de leittura
  lcd.print(" ");   

  //Saída para o Serial
  Serial.print("Valor PH:");
  Serial.println(valor_pH);

  //Saída para o Serial
  Serial.print("Temperatura:");
  Serial.println(valor_temperaturaC);  

  delay(1000); // Aguarda para próxima leitura
}
