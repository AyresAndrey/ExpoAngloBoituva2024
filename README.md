# Leitor de pH PH-4502C com Arduino Uno e LCD 16x2 I2C

## Descrição
Este projeto tem como objetivo criar um leitor de pH e temperatura utilizando um Arduino Uno, um sensor PH-4502C e um display LCD 16x2 com interface I2C. O sistema realiza a leitura contínua dos valores e exibe os resultados no display.

## Hardware Necessário
* Arduino Uno
* Sensor PH-4502C
* Display LCD 16x2 I2C
* Conectores e fios
* Fonte de alimentação (5V)

## Software
* Arduino IDE
* Bibliotecas:
    * LiquidCrystal_I2C.h
    * Wire.h

## Funcionamento
1. **Conexões:** Conecte os componentes de acordo com o diagrama esquemático
2. **Código:** Carregue o código Arduino no Arduino Uno.
3. **Inicialização:** Ao iniciar, o sistema realiza a leitura dos valores iniciais.
4. **Leitura Contínua:** O sistema realiza leituras periódicas do sensor e atualiza o display.

## Instalação
1. **Clone o repositório:**
   ```bash
   git clone https://github.com/AyresAndrey/ExpoAngloBoituva2024.git