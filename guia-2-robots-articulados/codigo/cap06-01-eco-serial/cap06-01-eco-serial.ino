// Eco por puerto serial: el programa más pequeño que demuestra que Python y
// Arduino se están entendiendo. Recibe una línea terminada en '\n' y la
// devuelve precedida de "OK ". Si esto no funciona, nada de lo que venga
// después va a funcionar (Capítulo 6).

const int LARGO_MAX = 48;    // el buffer serial del UNO son 64 bytes
char linea[LARGO_MAX];
int cuantos = 0;

void setup() {
  Serial.begin(115200);
  // Espera a que el puerto esté listo y anuncia que el firmware arrancó.
  // El anfitrión usa este mensaje para saber que puede empezar a hablar.
  delay(200);
  Serial.println(F("LISTO"));
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      if (cuantos == 0) continue;    // ignora líneas vacías
      linea[cuantos] = '\0';         // cierra la cadena
      Serial.print(F("OK "));
      Serial.println(linea);
      cuantos = 0;
    } else if (cuantos < LARGO_MAX - 1) {
      linea[cuantos++] = c;
    } else {
      // Línea más larga que el buffer: se descarta entera y se avisa.
      cuantos = 0;
      Serial.println(F("ERR linea muy larga"));
    }
  }
}
