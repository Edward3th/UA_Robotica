# Guía 1 · Introducción a la Robótica

Guía de iniciación: construyes un robot futbolista controlado por Bluetooth,
desde el diseño del chasis hasta la app del celular.

**Libro:** [Introduccion-a-la-Robotica.pdf](Introduccion-a-la-Robotica.pdf)

**Hardware:** NodeMCU ESP8266 v1.0 (Amica) sobre shield HW-588A, módulo L298N
para los motores, módulo Bluetooth HC-05, dos servos SG90/MG90S y 4 pilas AA.

## Código (NodeMCU ESP8266)

| Carpeta | Qué hace | Capítulo |
|---|---|---|
| [`codigo/cap05-01-parpadeo/`](codigo/cap05-01-parpadeo/) | Parpadeo del LED integrado: el primer programa | 5 |
| [`codigo/cap05-02-motores/`](codigo/cap05-02-motores/) | Funciones de movimiento sobre el módulo L298N | 5 |
| [`codigo/cap05-03-servos/`](codigo/cap05-03-servos/) | Control de las paletas con rango angular acotado | 5 |
| [`codigo/rutina-prueba/`](codigo/rutina-prueba/) | Rutina de prueba: los dos motores y los dos servos, en secuencia | 5 |
| [`codigo/control-bluetooth/`](codigo/control-bluetooth/) | Control del robot por Bluetooth (HC-05) con la app de abajo | 6 |

- En el Arduino IDE, agrega el paquete del ESP8266 (URL de tarjetas
  `https://arduino.esp8266.com/stable/package_esp8266com_index.json`) y elige la
  placa **NodeMCU 1.0 (ESP-12E Module)**.
- Cada programa está dentro de una carpeta con su mismo nombre, porque el
  Arduino IDE así lo exige. Ábrelo desde esa carpeta, sin moverlo ni renombrarlo.
- El HC-05 va a los pines RX/TX del NodeMCU: **desconéctalo antes de subir un
  programa**.

## App de control (MIT App Inventor)

| Archivo | Para qué sirve |
|---|---|
| [`app/App_Robotiza_2.apk`](app/App_Robotiza_2.apk) | App lista para instalar en un celular Android |
| [`app/App_Robotiza_2.aia`](app/App_Robotiza_2.aia) | Proyecto para abrir y modificar en MIT App Inventor |

| Botón | Envía | Acción |
|---|---|---|
| Arriba / abajo / izquierda / derecha | `U` `D` `L` `R` | Avanzar, retroceder, girar |
| Diagonales | `Q` `E` `Z` `C` | Curvas hacia adelante y hacia atrás |
| Al soltar cualquier dirección | `S` | Detenerse |
| A / B | `A` `B` | Patear con la paleta izquierda / derecha |

El menú «Seguidor de líneas» de la app (`I` / `P`) es para otra versión del
robot y el programa del libro lo ignora.

## Chasis del autor (STL)

| Archivo | Pieza |
|---|---|
| [`chasis/chasis.stl`](chasis/chasis.stl) | Placa del chasis, 250 × 130 × 9 mm |
| [`chasis/guardabarros.stl`](chasis/guardabarros.stl) | Guardabarros |
| [`chasis/union-motor-1.stl`](chasis/union-motor-1.stl) | Pieza de unión de los motores al chasis |
| [`chasis/union-motor-2.stl`](chasis/union-motor-2.stl) | Segunda pieza de unión de los motores |

> **Atención:** la placa mide 250 × 130 mm y no cabe en las camas de
> 220 × 220 mm de muchas impresoras. Compruébalo en Cura antes de laminar. Si no
> cabe, úsala como referencia y diseña tu propia placa, como propone el
> Capítulo 2.
