// Control de los dos motores DC vía el módulo L298N (ver Tabla 4.2, Capítulo 4).
const int ENA = 10, IN1 = 8, IN2 = 9;  // Motor izquierdo
const int ENB = 5,  IN3 = 6, IN4 = 7;  // Motor derecho

// Mueve un motor: adelante o atrás, a la velocidad indicada (0-255).
void moverMotor(int in1, int in2, int en, int velocidad, bool adelante) {
  digitalWrite(in1, adelante ? HIGH : LOW);
  digitalWrite(in2, adelante ? LOW : HIGH);
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
