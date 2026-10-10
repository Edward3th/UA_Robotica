"""Secuencia de recoger y soltar: junta todas las piezas del libro.

Se escriben coordenadas cartesianas en milimetros; la cinematica inversa
del Capitulo 4 las convierte en angulos y el anfitrion del Capitulo 6 los
envia al firmware. En ningun momento se escribe un angulo a mano.

Ejecutalo con el brazo conectado:
    python recoger_y_soltar.py
"""

import math
import os
import sys
import time

# Los modulos de los capitulos anteriores viven en sus propias carpetas.
AQUI = os.path.dirname(os.path.abspath(__file__))
for carpeta in ("cap04-cinematica-inversa", "cap06-03-control-brazo"):
    sys.path.append(os.path.join(AQUI, "..", carpeta))

from cinematica_inversa import ik_4gdl          # noqa: E402
from control_brazo import Brazo, ErrorBrazo     # noqa: E402


def ir_a(brazo, x, y, z, inclinacion_grados=-45.0):
    """Lleva la punta de la herramienta a un punto del espacio."""
    angulos = ik_4gdl(x, y, z, math.radians(inclinacion_grados))
    if angulos is None:
        raise ErrorBrazo("el punto (%.0f, %.0f, %.0f) esta fuera de alcance"
                         % (x, y, z))
    brazo.mover([math.degrees(a) for a in angulos])


# Puntos de trabajo, en milimetros desde el centro de la base.
# Cambiar la tarea es cambiar esta tabla, no el codigo.
ORIGEN = (170.0, -60.0, 40.0)
DESTINO = (170.0, 60.0, 40.0)
ALTURA_SEGURA = 120.0     # altura a la que el brazo se desplaza sin chocar


def recoger_y_soltar(brazo, origen, destino):
    x1, y1, z1 = origen
    x2, y2, z2 = destino

    ir_a(brazo, x1, y1, ALTURA_SEGURA)   # se acerca por arriba
    brazo.pinza(False)                   # abre antes de bajar
    ir_a(brazo, x1, y1, z1)              # baja sobre la pieza
    brazo.pinza(True)                    # agarra
    time.sleep(0.3)

    ir_a(brazo, x1, y1, ALTURA_SEGURA)   # levanta
    ir_a(brazo, x2, y2, ALTURA_SEGURA)   # traslada en alto
    ir_a(brazo, x2, y2, z2)              # baja
    brazo.pinza(False)                   # suelta
    time.sleep(0.3)
    ir_a(brazo, x2, y2, ALTURA_SEGURA)   # se retira


if __name__ == "__main__":
    with Brazo() as brazo:
        brazo.velocidad(10)
        brazo.home()

        recoger_y_soltar(brazo, ORIGEN, DESTINO)

        brazo.home()
        print("Ciclo terminado.")
