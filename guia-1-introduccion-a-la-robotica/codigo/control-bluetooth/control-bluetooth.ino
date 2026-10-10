// Control del robot por Bluetooth con la app App_Robotiza_2 (Capítulo 6).
// El HC-05 va al puerto serial del NodeMCU (RX y TX): desconéctalo antes de
// subir el programa. Un carácter por comando (ver Tabla 6.2).
#include <Servo.h>

// Motores (módulo L298N, ver Tabla 4.2, Capítulo 4)
const int ENA = D8, IN1 = D7, IN2 = D6;  // Motor izquierdo
const int ENB = D3, IN3 = D5, IN4 = D4;  // Motor derecho
const int VELOCIDAD = 200;        // rectas y giros en el lugar
const int VELOCIDAD_CURVA = 90;   // rueda interior en las diagonales

// Servos: paletas tipo pinball (Capítulo 4)
Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = D0, PIN_SERVO_DER = D1;
const int ANGULO_REPOSO = 90;
const int PATEO_IZQ = 40, PATEO_DER = 140;

void moverMotor(int in1, int in2, int en, int velocidad, bool adelante) {
  digitalWrite(in1, adelante ? LOW : HIGH);
  digitalWrite(in2, adelante ? HIGH : LOW);
  analogWrite(en, velocidad);
}

// Velocidad y sentido de cada rueda: con esto se arma cualquier movimiento.
void mover(int velIzq, bool adelanteIzq, int velDer, bool adelanteDer) {
  moverMotor(IN1, IN2, ENA, velIzq, adelanteIzq);
  moverMotor(IN3, IN4, ENB, velDer, adelanteDer);
}

void detener() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void patear(Servo &servo, int anguloPateo) {
  servo.write(anguloPateo);
  delay(200);
  servo.write(ANGULO_REPOSO);
}

void ejecutarComando(char comando) {
  const int V = VELOCIDAD, VC = VELOCIDAD_CURVA;  // nombres cortos
  switch (comando) {
    case 'U': mover(V, true,  V, true);  break;  // adelante
    case 'D': mover(V, false, V, false); break;  // atrás
    case 'L': mover(V, false, V, true);  break;  // gira a la izquierda
    case 'R': mover(V, true,  V, false); break;  // gira a la derecha
    case 'Q': mover(VC, true,  V, true);  break;  // adelante a la izquierda
    case 'E': mover(V, true,  VC, true);  break;  // adelante a la derecha
    case 'Z': mover(VC, false, V, false); break;  // atrás a la izquierda
    case 'C': mover(V, false, VC, false); break;  // atrás a la derecha
    case 'S': detener(); break;
    case 'A': patear(servoIzquierdo, PATEO_IZQ); break;
    case 'B': patear(servoDerecho, PATEO_DER); break;
    // 'I' y 'P' (seguidor de línea) o cualquier otro carácter: se ignoran.
  }
}

void setup() {
  Serial.begin(9600);  // velocidad de fábrica del HC-05
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
}

void loop() {
  if (Serial.available()) {
    ejecutarComando(Serial.read());
  }
}
