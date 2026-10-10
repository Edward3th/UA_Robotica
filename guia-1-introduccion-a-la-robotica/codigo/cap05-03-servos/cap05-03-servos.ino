// Control de las dos paletas (servos) con rango angular acotado.
// El límite entre reposo y pateo evita forzar el engranaje (ver Capítulo 4).
#include <Servo.h>

Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = D0, PIN_SERVO_DER = D1;
const int ANGULO_REPOSO = 90;
// Servos montados en espejo: para ir hacia el balón, uno baja y el otro sube.
const int PATEO_IZQ = 40, PATEO_DER = 140;

void patear(Servo &servo, int anguloPateo) {
  servo.write(anguloPateo);
  delay(200);
  servo.write(ANGULO_REPOSO);
}

void setup() {
  // Pulsos de 0.5 a 2.4 ms: el recorrido completo de un SG90.
  servoIzquierdo.attach(PIN_SERVO_IZQ, 500, 2400);
  servoDerecho.attach(PIN_SERVO_DER, 500, 2400);
  servoIzquierdo.write(ANGULO_REPOSO);
  servoDerecho.write(ANGULO_REPOSO);
}

void loop() {
  patear(servoIzquierdo, PATEO_IZQ);
  delay(1000);
  patear(servoDerecho, PATEO_DER);
  delay(1000);
}
