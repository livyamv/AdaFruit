#include <math.h>
#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

//configurações da rede Wifi
#define WIFI_SSID "malu"
#define WIFI_PASS "13131313"

//Autenticação Adafruit IO
#define IO_USERNAME "livmaria"
#define IO_KEY "aio_gXYa52pp1ADvBXYnsCkeKac0fBBu"

//AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34
#define pinLed 14 // Pino do LED
#define BUZZER_PIN 27 //Pino da buzzer
#define LED_ALARME 13 
#define BOTAO_FISICO 26
#define TRIG_PIN 12 
#define ECHO_PIN 14

//Configuração do ultrassônico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

//Variável / ponteiro para referenciar o feed temperatura
//AdafruitIO_Feed *botaoled = io.feed("botaoled");

const float Rfixo = 10000.0; //Resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000; // Nominal do ntc
const float T0_kelvin = 298.15; // 25°C em Kelvin
const float Vcc = 3.3;

void setup() {
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ALARME, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);


  delay(1000);

  Serial.begin(115200);

  while(!Serial);

  // Serial.print("Conectando ao Adafruit IO");
  // io.connect();

  // while(io.status() < AIO_CONNECTED){
  //   Serial.print(".");
  //   delay(500);
  // }

  // Serial.println();
  // Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber(atualizar) um valor
  // botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback 
  // Ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {
  Serial.print(F("Distacia Lida: "));
  Serial.println(sonar.ping_cm());
  delay(500);
  // //Manter a conexão com o Adafruit IO ativa
  // io.run();
  
  // //publicacao(); // Chamada da função publish

  // delay(500);

  // testeBuzzer();
  // testeLed();
  testeBotao(BOTAO_FISICO);

}
