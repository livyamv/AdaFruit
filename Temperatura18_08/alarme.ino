void handleAlarme(AdafruitIO_Data *data) {
  String valor = data->toString();

  Serial.print(F("Valor recebido do feed: "));
  Serial.println(valor);

  if (valor == "true") {
    alarmeAtivo = true;
    digitalWrite(LED_ARMADO, HIGH);
    digitalWrite(LED_DESARMADO, LOW);
    Serial.println("Alarme ARMADO pelo dash / app!");
  } else {
    alarmeAtivo = true;
    digitalWrite(LED_DESARMADO, LOW);
    digitalWrite(LED_ARMADO, HIGH);
    Serial.println("Alarme DESARMADO pelo dash / app!");
  }
}
void ativarAlarme() {
  pinMode(BUZZER_PIN, HIGH);
  pinMode(LED_ALARME, HIGH);
}

void desativarAlarme() {
  pinMode(BUZZER_PIN, LOW);
  pinMode(LED_ALARME, LOW);
}
