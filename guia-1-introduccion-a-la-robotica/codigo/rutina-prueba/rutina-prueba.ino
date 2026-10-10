// Rutina de prueba del robot: verifica avance, retroceso, giro y ambos
// servos, uno por uno, con aviso por el Monitor Serie.
#include <Servo.h>

// Motores (módulo L298N, ver Tabla 4.2, Capítulo 4)
const int ENA = 10, IN1 = 8, IN2 = 9;  // Motor izquierdo
const int ENB = 5,  IN3 = 6, IN4 = 7;  // Motor derecho

// Servos: paletas tipo pinball (Capítulo 4)
Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = 3, PIN_SERVO_DER = 11;
const int ANGULO_REPOSO = 90;
const int ANGULO_PATEO = 40;

const int VELOCIDAD_PRUEBA = 150;

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

void patear(Servo &servo, const char *nombre) {
  Serial.print("Pateando: ");
  Serial.println(nombre);
  servo.write(ANGULO_PATEO);
  delay(200);
  servo.write(ANGULO_REPOSO);
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  servoIzquierdo.attach(PIN_SERVO_IZQ);
  servoDerecho.attach(PIN_SERVO_DER);
  servoIzquierdo.write(ANGULO_REPOSO);
  servoDerecho.write(ANGULO_REPOSO);

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

  patear(servoIzquierdo, "servo izquierdo");
  delay(1000);
  patear(servoDerecho, "servo derecho");
  delay(2000);
}
