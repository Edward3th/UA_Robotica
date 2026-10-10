// Prueba de una articulación con servomotor: límites por software y
// movimiento por rampa. Este es el sketch mínimo que debes cargar en cada
// articulación nueva ANTES de montarla en el brazo (Capítulo 5).
#include <Servo.h>

Servo articulacion;
const int PIN_SERVO = 9;

// --- Límites mecánicos, en microsegundos de ancho de pulso ---
// Se miden a mano, con el brazo desmontado: mueve el servo de a poco hasta
// que el eslabón toque su tope físico y retrocede 100 us de margen.
const int PULSO_MIN = 900;    // extremo seguro en un sentido
const int PULSO_MAX = 2100;   // extremo seguro en el otro
const int PULSO_HOME = 1500;  // posición de reposo (centro)

// Velocidad del movimiento: cuántos microsegundos avanza por paso.
const int PASO_US = 4;
const int MS_POR_PASO = 12;

int pulsoActual = PULSO_HOME;

// Lleva el servo hasta un pulso objetivo de a poco, no de un salto.
// Un servo sin rampa arranca a máxima velocidad y el brazo rebota.
void moverA(int pulsoObjetivo) {
  pulsoObjetivo = constrain(pulsoObjetivo, PULSO_MIN, PULSO_MAX);
  int paso = (pulsoObjetivo > pulsoActual) ? PASO_US : -PASO_US;

  while (abs(pulsoObjetivo - pulsoActual) > PASO_US) {
    pulsoActual += paso;
    articulacion.writeMicroseconds(pulsoActual);
    delay(MS_POR_PASO);
  }
  pulsoActual = pulsoObjetivo;
  articulacion.writeMicroseconds(pulsoActual);
}

// Convierte un ángulo del modelo cinemático a ancho de pulso.
// 90 grados de recorrido equivalen a 1000 us en un servo típico.
int anguloAPulso(float grados) {
  return (int)(PULSO_HOME + grados * (1000.0 / 90.0));
}

void setup() {
  Serial.begin(115200);
  articulacion.attach(PIN_SERVO, PULSO_MIN, PULSO_MAX);
  articulacion.writeMicroseconds(PULSO_HOME);
  delay(1000);
  Serial.println(F("Prueba de articulacion lista."));
}

void loop() {
  Serial.println(F("-> +45 grados"));
  moverA(anguloAPulso(45.0));
  delay(800);

  Serial.println(F("-> centro"));
  moverA(PULSO_HOME);
  delay(800);

  Serial.println(F("-> -45 grados"));
  moverA(anguloAPulso(-45.0));
  delay(800);

  Serial.println(F("-> centro"));
  moverA(PULSO_HOME);
  delay(2000);
}
