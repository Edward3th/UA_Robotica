// Control de las dos paletas (servos) con rango angular acotado.
// El límite entre reposo y pateo evita forzar el engranaje (ver Capítulo 4).
#include <Servo.h>

Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = 3, PIN_SERVO_DER = 11;
const int ANGULO_REPOSO = 90;
const int ANGULO_PATEO = 40;

void patear(Servo &servo) {
  servo.write(ANGULO_PATEO);
  delay(200);
  servo.write(ANGULO_REPOSO);
}

void setup() {
  servoIzquierdo.attach(PIN_SERVO_IZQ);
  servoDerecho.attach(PIN_SERVO_DER);
  servoIzquierdo.write(ANGULO_REPOSO);
  servoDerecho.write(ANGULO_REPOSO);
}

void loop() {
  patear(servoIzquierdo);
  delay(1000);
  patear(servoDerecho);
  delay(1000);
}
