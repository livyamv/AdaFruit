#include "AdafruitIO_WiFi.h"

#define WIFI_SSID "malu"
#define WIFI_PASS "13061306"

// Autenticação Adafruit IO
#define IO_USERNAME "livmaria"
#define IO_KEY "aio_NNhv22WAg9WBs6GgbYGB3lk4Ybu3"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinLed 14  // pino do LED

// variavel / ponteiro para referencia o feed temperatura
AdafruitIO_Feed *botaoled = io.feed("botaoled");

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  // Aguarda inicializar o Serial
  while (!Serial);

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  // Configura callback do feed
  botaoled->onMessage(handleBotaoLed);

  // Espera conexão
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Mostra status quando conecta
  Serial.println();
  Serial.println(io.statusText());

  //Último valor do feed
  botaoled->get();
}

void loop() {
  io.run();
}

// callback
void handleBotaoLed(AdafruitIO_Data *data) {
  Serial.print("Novo valor no feed botaoLed: ");
  Serial.println(data->toString());

  if (data->toBool()) {
    digitalWrite(pinLed, HIGH);
    Serial.println("Led ligado!!");
  } else {
    digitalWrite(pinLed, LOW);
    Serial.println("Led desligado!!");
  }
}