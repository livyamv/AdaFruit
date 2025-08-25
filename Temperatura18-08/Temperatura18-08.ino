#include <math.h> // Necessário para usar a função log()

// --- Configuração de hardware ---
define pinNTC 34 // Pino ADC onde o NTC está conectado (ESP32: 32, 33, 34, 35, 36, 39)

// --- Constantes do NTC ---
const float Rfixo = 10000.0;      // Resistor fixo do divisor de tensão (ohms)
const float Beta = 3950.0;        // Constante Beta do NTC (fornecida pelo fabricante)
const float R0 = 10000.0;         // Resistência nominal do NTC a 25°C (ohms)
const float T0_kelvin = 298.15;   // 25°C em Kelvin
const float Vcc = 3.3;            // Tensão de alimentação do divisor (ESP32 = 3,3V)

// --- Função para calcular temperatura com média de leituras ---
float lerTemperaturaNTC(int pino, int numLeituras) {
    long somaLeituras = 0;

    // Faz várias leituras para reduzir ruído
    for (int i = 0; i < numLeituras; i++) {
        somaLeituras += analogRead(pino);
        delay(5); // pequeno atraso para estabilizar
    }

    // Calcula média das leituras
    float leituraMedia = somaLeituras / (float)numLeituras;

    // Converte para tensão real (ESP32: ADC de 12 bits = 0 a 4095)
    float Vout = leituraMedia * (Vcc / 4095.0);

    // Calcula resistência do NTC pelo divisor de tensão
    float Rntc = Rfixo * ((Vcc / Vout) - 1.0);

    // Aplica equação Beta para calcular temperatura em Kelvin
    float tempK = 1.0 / ((1.0 / T0_kelvin) + (1.0 / Beta) * log(Rntc / R0));

    // Retorna temperatura em Celsius
    return tempK - 273.15;
}

void setup() {
		//modo do pino
		pinMode(pinNTC, INPUT);
    Serial.begin(115200); // Inicializa comunicação serial
}

void loop() {		
    // Lê temperatura com média de 10 leituras
    float temperatura = lerTemperaturaNTC(pinNTC, 10);

    // Exibe no Serial Monitor
    Serial.print("Temperatura: ");
    Serial.print(temperatura, 2); // duas casas decimais
    Serial.println(" °C");

    delay(1000); // espera 1 segundo antes de repetir
}