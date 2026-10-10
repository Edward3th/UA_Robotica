// Enciende y apaga el LED integrado del NodeMCU cada segundo.
// En el ESP8266 este LED funciona al revés: LOW lo enciende, HIGH lo apaga.
const int LED = LED_BUILTIN;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, LOW);   // encendido
  delay(1000);
  digitalWrite(LED, HIGH);  // apagado
  delay(1000);
}
