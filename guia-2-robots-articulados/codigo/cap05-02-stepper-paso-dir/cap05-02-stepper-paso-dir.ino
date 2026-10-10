// Control de un motor paso a paso NEMA 17 con driver A4988 o DRV8825.
// Sin librerías: el driver solo necesita un pulso por paso y un nivel que
// indique el sentido. Incluye búsqueda de origen con final de carrera,
// obligatoria en todo motor paso a paso (Capítulo 5).

const int PIN_PASO = 3;      // STEP del driver
const int PIN_DIR = 4;       // DIR del driver
const int PIN_ENABLE = 5;    // ENABLE del driver (activo en bajo)
const int PIN_FINAL = 6;     // final de carrera del origen, a GND

// --- Geometría del eje ---
const int PASOS_POR_VUELTA = 200;   // NEMA 17 de 1.8 grados por paso
const int MICROPASOS = 16;          // configurado con los jumpers del driver
const float REDUCCION = 5.0;        // relación de la correa o del engranaje

// Micropasos que hay que dar para girar un grado del eslabón
const float PASOS_POR_GRADO =
    (PASOS_POR_VUELTA * MICROPASOS * REDUCCION) / 360.0;

// Ancho del pulso y pausa entre pasos: define la velocidad
const int ANCHO_PULSO_US = 3;
const int PAUSA_PASO_US = 700;

long posicionPasos = 0;   // posición actual, en micropasos desde el origen

void darPaso() {
  digitalWrite(PIN_PASO, HIGH);
  delayMicroseconds(ANCHO_PULSO_US);
  digitalWrite(PIN_PASO, LOW);
  delayMicroseconds(PAUSA_PASO_US);
}

// Gira una cantidad de micropasos. El signo indica el sentido.
void moverPasos(long pasos) {
  digitalWrite(PIN_DIR, pasos >= 0 ? HIGH : LOW);
  long cantidad = abs(pasos);
  for (long i = 0; i < cantidad; i++) {
    darPaso();
  }
  posicionPasos += pasos;
}

// Mueve el eslabón a un ángulo absoluto, medido desde el origen.
void moverAGrados(float grados) {
  long objetivo = (long)(grados * PASOS_POR_GRADO);
  moverPasos(objetivo - posicionPasos);
}

// Un motor paso a paso no sabe dónde está al encender: hay que llevarlo
// contra un final de carrera y declarar ese punto como cero.
void buscarOrigen() {
  Serial.println(F("Buscando origen..."));
  digitalWrite(PIN_DIR, LOW);                 // sentido hacia el final de carrera
  while (digitalRead(PIN_FINAL) == HIGH) {    // HIGH = sin tocar (pull-up interno)
    darPaso();
  }
  moverPasos(20);          // se despega un poco del sensor
  posicionPasos = 0;       // este punto es el cero del eje
  Serial.println(F("Origen encontrado."));
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PASO, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_FINAL, INPUT_PULLUP);

  digitalWrite(PIN_ENABLE, LOW);   // activo: el motor queda con par de retención
  buscarOrigen();
}

void loop() {
  Serial.println(F("-> 30 grados"));
  moverAGrados(30.0);
  delay(1000);

  Serial.println(F("-> 90 grados"));
  moverAGrados(90.0);
  delay(1000);

  Serial.println(F("-> 0 grados"));
  moverAGrados(0.0);
  delay(2000);
}
