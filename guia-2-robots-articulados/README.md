# Guía 2 · Robots Articulados

Guía para especificar, calcular y controlar un brazo robótico propio de 2, 3 o
4 grados de libertad.

**Libro:** [Robots-Articulados.pdf](Robots-Articulados.pdf)

## Código

| Carpeta | Qué hace | Capítulo |
|---|---|---|
| [`codigo/cap03-cinematica-directa/`](codigo/cap03-cinematica-directa/) | Cinemática directa por geometría y por Denavit-Hartenberg, con comprobación cruzada | 3 |
| [`codigo/cap04-cinematica-inversa/`](codigo/cap04-cinematica-inversa/) | Cinemática inversa cerrada de 2, 3 y 4 GDL, con prueba de ida y vuelta | 4 |
| [`codigo/cap05-01-servo-limites/`](codigo/cap05-01-servo-limites/) | Prueba de una articulación con servomotor: límites y rampa | 5 |
| [`codigo/cap05-02-stepper-paso-dir/`](codigo/cap05-02-stepper-paso-dir/) | Motor paso a paso con driver A4988 o DRV8825, con búsqueda de origen | 5 |
| [`codigo/cap06-01-eco-serial/`](codigo/cap06-01-eco-serial/) | Eco por puerto serial: la prueba mínima del enlace | 6 |
| [`codigo/cap06-02-firmware-brazo/`](codigo/cap06-02-firmware-brazo/) | Firmware del brazo: protocolo, calibración e interpolación | 6 |
| [`codigo/cap06-03-control-brazo/`](codigo/cap06-03-control-brazo/) | Anfitrión en Python: conexión, protocolo y órdenes de alto nivel | 6 |
| [`codigo/cap07-01-recoger-y-soltar/`](codigo/cap07-01-recoger-y-soltar/) | Ciclo completo de recoger y soltar en coordenadas cartesianas | 7 |

- Los dos programas de cinemática solo necesitan Python y su biblioteca
  estándar: corren sin ningún componente conectado.
- `control_brazo.py` y `recoger_y_soltar.py` necesitan además `pyserial`
  (`pip install pyserial`) y el brazo armado con el firmware cargado.
- Para adaptar el código a tu brazo, cambia solo las constantes de la cabecera:
  los largos `d0`, `L1`, `L2`, `L3` en los programas de cinemática y la tabla de
  calibración en el firmware.

## Plantillas

| Archivo | Para qué sirve | Capítulo |
|---|---|---|
| [`plantillas/hoja-dimensionamiento.ods`](plantillas/hoja-dimensionamiento.ods) | Planilla para sumar momentos y elegir los servos. Viene cargada con el brazo de referencia: reemplaza masas y distancias por las tuyas | 5 |
| [`plantillas/hoja-calibracion.pdf`](plantillas/hoja-calibracion.pdf) | Hoja imprimible para anotar pulso cero, signo y límites de cada articulación, y pasarlos al firmware | 5 y 6 |
