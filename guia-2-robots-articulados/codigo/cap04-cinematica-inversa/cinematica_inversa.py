"""Cinematica inversa de un brazo articulado de 2, 3 y 4 GDL.

Solucion cerrada, obtenida por geometria (teorema del coseno). Cada
funcion devuelve None cuando el punto pedido queda fuera del alcance:
la cinematica inversa puede no tener solucion, y el codigo debe decirlo
en vez de entregar un angulo invalido.

Solo requiere la libreria estandar de Python. Ejecutalo con:
    python cinematica_inversa.py
"""

import math

# Brazo de referencia del libro (milimetros)
D0 = 60.0   # altura de la base al eje del hombro
L1 = 100.0  # hombro -> codo
L2 = 90.0   # codo -> muneca
L3 = 60.0   # muneca -> punta de la herramienta


def ik_2gdl(x, y, l1=L1, l2=L2, codo_arriba=True):
    """Dos eslabones en un plano: alcanza el punto (x, y).

    Devuelve (theta1, theta2) en radianes, o None si el punto es
    inalcanzable. El codo tiene dos soluciones: arriba y abajo.
    """
    distancia = math.hypot(x, y)
    if distancia > l1 + l2 or distancia < abs(l1 - l2):
        return None  # fuera del anillo alcanzable

    # Teorema del coseno sobre el triangulo hombro-codo-muneca
    coseno = (distancia ** 2 - l1 ** 2 - l2 ** 2) / (2 * l1 * l2)
    coseno = max(-1.0, min(1.0, coseno))   # protege acos del error de redondeo
    theta2 = -math.acos(coseno) if codo_arriba else math.acos(coseno)

    # El hombro apunta al objetivo, corregido por lo que desvia el codo
    theta1 = math.atan2(y, x) - math.atan2(l2 * math.sin(theta2),
                                           l1 + l2 * math.cos(theta2))
    return theta1, theta2


def ik_3gdl(x, y, phi, l1=L1, l2=L2, l3=L3, codo_arriba=True):
    """Tres eslabones en un plano: alcanza (x, y) con orientacion phi.

    El tercer grado de libertad se gasta en fijar la orientacion de la
    herramienta, asi que el problema se reduce al de 2 GDL: se retrocede
    l3 desde el objetivo para encontrar la muneca.
    """
    xm = x - l3 * math.cos(phi)
    ym = y - l3 * math.sin(phi)

    solucion = ik_2gdl(xm, ym, l1, l2, codo_arriba)
    if solucion is None:
        return None

    theta1, theta2 = solucion
    theta3 = phi - theta1 - theta2   # lo que falte para cerrar la orientacion
    return theta1, theta2, theta3


def ik_4gdl(x, y, z, phi, codo_arriba=True):
    """Brazo completo: base giratoria mas cadena plana de 3 GDL.

    (x, y, z) en mm desde el centro de la base; phi en radianes, medido
    desde la horizontal. Devuelve los cuatro angulos o None.
    """
    theta0 = math.atan2(y, x)          # la base solo mira hacia el objetivo
    r = math.hypot(x, y)               # distancia al eje de la base
    altura = z - D0                    # alto medido desde el hombro

    solucion = ik_3gdl(r, altura, phi, codo_arriba=codo_arriba)
    if solucion is None:
        return None

    theta1, theta2, theta3 = solucion
    return theta0, theta1, theta2, theta3


def grados(angulos):
    """Convierte una tupla de radianes a grados, redondeada."""
    return tuple(round(math.degrees(a), 2) for a in angulos)


# ---------------------------------------------------------------
# Demostracion: la prueba de ida y vuelta
# ---------------------------------------------------------------
if __name__ == "__main__":
    import sys
    import os
    sys.path.append(os.path.join(os.path.dirname(__file__), "..",
                                 "cap03-cinematica-directa"))
    from cinematica_directa import brazo_4gdl

    objetivo = (142.52, 82.29, 63.86, math.radians(-60.0))
    print("Objetivo: x=%.2f  y=%.2f  z=%.2f  phi=%.1f deg"
          % (objetivo[0], objetivo[1], objetivo[2],
             math.degrees(objetivo[3])))

    for nombre, arriba in (("codo arriba", True), ("codo abajo", False)):
        angulos = ik_4gdl(*objetivo, codo_arriba=arriba)
        if angulos is None:
            print("%-12s -> fuera de alcance" % nombre)
            continue

        # Ida y vuelta: la cinematica directa debe devolver el objetivo
        x, y, z, phi = brazo_4gdl(*angulos)
        error = math.dist((x, y, z), objetivo[:3])
        print("%-12s -> angulos %s   error de cierre = %.4f mm"
              % (nombre, grados(angulos), error))

    # Un punto imposible: mas lejos que la suma de los eslabones
    print("\nPunto a 400 mm:", ik_4gdl(400.0, 0.0, 60.0, 0.0))

    # Barrido de alcance sobre el eje X, con la herramienta horizontal
    print("\nAlcance sobre el eje X (phi = 0, codo arriba):")
    for distancia in range(60, 281, 20):
        angulos = ik_4gdl(float(distancia), 0.0, D0, 0.0)
        estado = "ok  %s" % (grados(angulos),) if angulos else "inalcanzable"
        print("  x = %3d mm -> %s" % (distancia, estado))
