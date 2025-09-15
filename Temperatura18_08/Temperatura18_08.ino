// #include <math.h>
// #include "AdafruitIO_WiFi.h"
// #include "NewPing.h"

// //configurações da rede Wifi
// #define WIFI_SSID "malu"
// #define WIFI_PASS "13131313"

// //Autenticação Adafruit IO
// #define IO_USERNAME "livmaria"
// #define IO_KEY ""

// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34
#define pinLed 14      // Pino do LED
#define BUZZER_PIN 27  //Pino da buzzer
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

const float Rfixo = 10000.0;  //Resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000;          // Nominal do ntc
const float T0_kelvin = 298.15;  // 25°C em Kelvin
const float Vcc = 3.3;

//Definição dos Feeds
AdafruitIO_Feed *botaoAlarme = io.feed("botaoalarme");

//Definição Variáveis de controle
bool alarmeAtivo = false;
unsigned int distancia = 0;
const int LIMITE_DISTANCIA = 15;


void setup() {
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ALARME, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);


  delay(1000);

  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Serial.println();
  // Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber(atualizar) um valor
  // botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado


  // Vincula a função callback ao feed
  botaoAlarme->onMessage(handleAlarme);

  Serial.println("Solicitação o estado inicial do alarme: ");
  botaoAlarme->get();

  delay(1000);
}

void loop() {
  io.run();

  //Leitura do botão físico
  if (digitalRead(BOTAO_FISICO) == 1) {
    delay(200);  //debouce simples
    alarmeAtivo = !alarmeAtivo;

    botaoAlarme->save(String(alarmeAtivo ? "true" : "false"));
    Serial.println(alarmeAtivo ? F("Alarme ARMADO pelo botao físico.") : F("Alarme DESARMADO pelo botao físico."));
  }

  distancia = sonar.ping_cm();
  Serial.print("Distancia lida: ");
  Serial.println(distancia);
  Serial.println("cm");

    //Ativação pu desativaçao do alarme
    if (alarmeAtivo && distancia > 0 && distancia < LIMITE_DISTANCIA) {
    ativarAlarme();
  }

  else {
    desativarAlarme();
  }

  // //publicacao(); // Chamada da função publish
  // delay(500);
  // testeBuzzer();
  // testeLed();
  // testeBotao(BOTAO_FISICO);
}
