// Rutina de prueba del robot: verifica avance, retroceso, giro y ambos
// servos, uno por uno, con aviso por el Monitor Serie.
#include <Servo.h>

// Motores (módulo L298N, ver Tabla 4.2, Capítulo 4)
const int ENA = D8, IN1 = D7, IN2 = D6;  // Motor izquierdo
const int ENB = D3, IN3 = D5, IN4 = D4;  // Motor derecho

// Servos: paletas tipo pinball (Capítulo 4)
Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = D0, PIN_SERVO_DER = D1;
const int ANGULO_REPOSO = 90;
const int PATEO_IZQ = 40, PATEO_DER = 140;

const int VELOCIDAD_PRUEBA = 150;

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

void patear(Servo &servo, int anguloPateo, const char *nombre) {
  Serial.print("Pateando: ");
  Serial.println(nombre);
  servo.write(anguloPateo);
  delay(200);
  servo.write(ANGULO_REPOSO);
}

void setup() {
  Serial.begin(9600);
  analogWriteRange(255);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  detener();

  servoIzquierdo.attach(PIN_SERVO_IZQ, 500, 2400);
  servoDerecho.attach(PIN_SERVO_DER, 500, 2400);
  servoIzquierdo.write(ANGULO_REPOSO);
  servoDerecho.write(ANGULO_REPOSO);

  Serial.println();
  Serial.println("Rutina de prueba lista.");
}

void loop() {
  Serial.println("Avanzar");
  avanzar(VELOCIDAD_PRUEBA);
  delay(1500);
  detener();
  delay(500);

  Serial.println("Retroceder");
  retroceder(VELOCIDAD_PRUEBA);
  delay(1500);
  detener();
  delay(500);

  Serial.println("Girar izquierda");
  girarIzquierda(VELOCIDAD_PRUEBA);
  delay(1000);
  detener();
  delay(500);

  Serial.println("Girar derecha");
  girarDerecha(VELOCIDAD_PRUEBA);
  delay(1000);
  detener();
  delay(500);

  patear(servoIzquierdo, PATEO_IZQ, "servo izquierdo");
  delay(1000);
  patear(servoDerecho, PATEO_DER, "servo derecho");
  delay(2000);
}
