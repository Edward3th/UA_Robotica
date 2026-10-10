// Control de los dos motores DC con el módulo L298N (ver Tabla 4.2, Capítulo 4).
const int ENA = D8, IN1 = D7, IN2 = D6;  // Motor izquierdo
const int ENB = D3, IN3 = D5, IN4 = D4;  // Motor derecho

// Mueve un motor hacia adelante o hacia atrás, con velocidad de 0 a 255.
// En el robot del libro, IN1 en LOW e IN2 en HIGH hacen avanzar la rueda.
void moverMotor(int in1, int in2, int en, int velocidad, bool adelante) {
  digitalWrite(in1, adelante ? LOW : HIGH);
  digitalWrite(in2, adelante ? HIGH : LOW);
  analogWrite(en, velocidad);
}

void avanzar(int velocidad) {
  moverMotor(IN1, IN2, ENA, velocidad, true);
  moverMotor(IN3, IN4, ENB, velocidad, true);
}

void retroceder(int velocidad) {
  moverMotor(IN1, IN2, ENA, velocidad, false);
  moverMotor(IN3, IN4, ENB, velocidad, false);
}

void girarIzquierda(int velocidad) {
  moverMotor(IN1, IN2, ENA, velocidad, false);
  moverMotor(IN3, IN4, ENB, velocidad, true);
}

void girarDerecha(int velocidad) {
  moverMotor(IN1, IN2, ENA, velocidad, true);
  moverMotor(IN3, IN4, ENB, velocidad, false);
}

void detener() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void setup() {
  analogWriteRange(255);  // velocidades de 0 a 255, igual que en un Arduino
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  avanzar(150);
  delay(1000);
  detener();
  delay(500);
}
