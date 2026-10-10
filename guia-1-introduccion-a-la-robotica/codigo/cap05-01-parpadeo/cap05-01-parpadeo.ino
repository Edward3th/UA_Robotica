// Enciende y apaga el LED integrado del Arduino cada segundo.
const int LED = LED_BUILTIN;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
