// Control del robot por Bluetooth (módulo HC-06 vía SoftwareSerial).
// Protocolo de un carácter por comando: F, B, L, R, S, K (ver Tabla 6.2).
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(2, 4);  // RX, TX (TX va al HC-06 a través del divisor)

// Motores (módulo L298N, ver Tabla 4.2, Capítulo 4)
const int ENA = 10, IN1 = 8, IN2 = 9;  // Motor izquierdo
const int ENB = 5,  IN3 = 6, IN4 = 7;  // Motor derecho
const int VELOCIDAD = 180;

// Servos: paletas tipo pinball (Capítulo 4)
Servo servoIzquierdo, servoDerecho;
const int PIN_SERVO_IZQ = 3, PIN_SERVO_DER = 11;
const int ANGULO_REPOSO = 90;
const int ANGULO_PATEO = 40;

void moverMotor(int in1, int in2, int en, int velocidad, bool adelante) {
  digitalWrite(in1, adelante ? HIGH : LOW);
  digitalWrite(in2, adelante ? LOW : HIGH);
  analogWrite(en, velocidad);
}

void avanzar()        { moverMotor(IN1, IN2, ENA, VELOCIDAD, true);
                         moverMotor(IN3, IN4, ENB, VELOCIDAD, true); }
void retroceder()     { moverMotor(IN1, IN2, ENA, VELOCIDAD, false);
                         moverMotor(IN3, IN4, ENB, VELOCIDAD, false); }
void girarIzquierda() { moverMotor(IN1, IN2, ENA, VELOCIDAD, false);
                         moverMotor(IN3, IN4, ENB, VELOCIDAD, true); }
void girarDerecha()   { moverMotor(IN1, IN2, ENA, VELOCIDAD, true);
                         moverMotor(IN3, IN4, ENB, VELOCIDAD, false); }
void detener()        { analogWrite(ENA, 0); analogWrite(ENB, 0); }

void patear() {
  servoIzquierdo.write(ANGULO_PATEO);
  servoDerecho.write(ANGULO_PATEO);
  delay(200);
  servoIzquierdo.write(ANGULO_REPOSO);
  servoDerecho.write(ANGULO_REPOSO);
}

void ejecutarComando(char comando) {
  switch (comando) {
    case 'F': avanzar(); break;
    case 'B': retroceder(); break;
    case 'L': girarIzquierda(); break;
    case 'R': girarDerecha(); break;
    case 'S': detener(); break;
    case 'K': patear(); break;
  }
}

void setup() {
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

  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    ejecutarComando(bluetooth.read());
  }
}
