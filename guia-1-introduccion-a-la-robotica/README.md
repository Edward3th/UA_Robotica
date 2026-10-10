# Guía 1 · Introducción a la Robótica

Guía de iniciación: construyes un robot futbolista controlado por Bluetooth,
desde el diseño del chasis hasta la app del celular.

**Libro:** [Introduccion-a-la-Robotica.pdf](Introduccion-a-la-Robotica.pdf)

## Código (Arduino UNO)

| Carpeta | Qué hace | Capítulo |
|---|---|---|
| [`codigo/cap05-01-parpadeo/`](codigo/cap05-01-parpadeo/) | Parpadeo del LED integrado: el primer programa | 5 |
| [`codigo/cap05-02-motores/`](codigo/cap05-02-motores/) | Funciones de movimiento sobre el módulo L298N | 5 |
| [`codigo/cap05-03-servos/`](codigo/cap05-03-servos/) | Control de las paletas con rango angular acotado | 5 |
| [`codigo/rutina-prueba/`](codigo/rutina-prueba/) | Rutina de prueba: los dos motores y los dos servos, en secuencia | 5 |
| [`codigo/control-bluetooth/`](codigo/control-bluetooth/) | Control del robot por Bluetooth (HC-06), comandos `F` `B` `L` `R` `S` `K` | 6 |

Cada programa está dentro de una carpeta con su mismo nombre, porque el Arduino
IDE así lo exige. Ábrelo desde esa carpeta, sin moverlo ni renombrarlo.

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
