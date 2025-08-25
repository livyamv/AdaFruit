// #include <math.h>
// #include "AdafruitIO_WiFi.h"

// #define WIFI_SSID "malu"
// #define WIFI_PASS "13061306"

// //Autenticação Adafruit IO
// #define IO_USERNAME  "livmaria"
// #define IO_KEY       "..."

// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34  // pino ADC
#define pinLed 14  // pino do LED

// Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

// variavel / ponteiro para referencia o feed temperatura
AdafruitIO_Feed *temperatura = io.feed("temperatura");

const float Rfixo = 10000.0;  // resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000.0;        // nominal do ntc
const float T0_kelvin = 298.15;  // 25 graus ceusius
const float Vcc = 3.3;

void setup() {
  Serial.begin(115200);
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);

  while (!Serial)
    ;

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber um valor(atualizar) um valor
  temperatura -> onMessage(handleTemperatura);
  // registra a função de callback
  // ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {

  //Manter a conexão com o Adafruit IO ativa
  io.run();

  //publicacao(); //chamada da função publish
  
  delay(7000);
}
