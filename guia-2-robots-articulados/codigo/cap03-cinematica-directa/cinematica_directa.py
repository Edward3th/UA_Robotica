"""Cinematica directa de un brazo articulado de 2, 3 y 4 GDL.

Dos caminos que deben dar el mismo resultado:
  1. Formulas geometricas directas (las que usaras al programar).
  2. Tabla de Denavit-Hartenberg (la que usaras al documentar).

Solo requiere la libreria estandar de Python. Ejecutalo con:
    python cinematica_directa.py
"""

import math

# ---------------------------------------------------------------
# Brazo de referencia del libro (milimetros)
# ---------------------------------------------------------------
D0 = 60.0   # altura de la base al eje del hombro
L1 = 100.0  # hombro -> codo
L2 = 90.0   # codo -> muneca
L3 = 60.0   # muneca -> punta de la herramienta


# ---------------------------------------------------------------
# 1. Camino geometrico
# ---------------------------------------------------------------
def cadena_plana(longitudes, angulos):
    """Extremo de una cadena de eslabones en un plano.

    longitudes: lista de largos, en mm.
    angulos: lista de angulos articulares, en radianes y relativos al
             eslabon anterior (el primero, respecto del eje horizontal).
    Devuelve (x, y, phi): posicion del extremo y orientacion acumulada.
    """
    x = y = phi = 0.0
    for largo, angulo in zip(longitudes, angulos):
        phi += angulo            # los angulos relativos se suman
        x += largo * math.cos(phi)
        y += largo * math.sin(phi)
    return x, y, phi


def brazo_4gdl(theta0, theta1, theta2, theta3):
    """Cinematica directa del brazo de 4 GDL: base + hombro + codo + muneca.

    Los cuatro angulos van en radianes. Devuelve (x, y, z, phi) en mm y
    radianes, con phi = inclinacion de la herramienta sobre la horizontal.
    """
    # El hombro, el codo y la muneca forman una cadena plana en el plano
    # vertical que la base orienta. r es la distancia al eje de la base.
    r, altura, phi = cadena_plana([L1, L2, L3], [theta1, theta2, theta3])
    x = r * math.cos(theta0)
    y = r * math.sin(theta0)
    z = D0 + altura
    return x, y, z, phi


# ---------------------------------------------------------------
# 2. Camino Denavit-Hartenberg
# ---------------------------------------------------------------
def matriz_dh(theta, d, a, alfa):
    """Matriz homogenea 4x4 de un eslabon, convencion DH estandar."""
    ct, st = math.cos(theta), math.sin(theta)
    ca, sa = math.cos(alfa), math.sin(alfa)
    return [
        [ct, -st * ca,  st * sa, a * ct],
        [st,  ct * ca, -ct * sa, a * st],
        [0.0,      sa,       ca,      d],
        [0.0,     0.0,      0.0,    1.0],
    ]


def multiplicar(A, B):
    """Producto de dos matrices 4x4."""
    return [[sum(A[i][k] * B[k][j] for k in range(4)) for j in range(4)]
            for i in range(4)]


def cinematica_directa_dh(tabla):
    """Compone la tabla DH completa. tabla: lista de (theta, d, a, alfa)."""
    T = [[1.0 if i == j else 0.0 for j in range(4)] for i in range(4)]
    for fila in tabla:
        T = multiplicar(T, matriz_dh(*fila))
    return T


def tabla_dh_brazo(theta0, theta1, theta2, theta3):
    """Tabla DH del brazo de referencia, ya evaluada en una postura."""
    return [
        (theta0, D0, 0.0, math.pi / 2),  # base: gira y levanta el hombro
        (theta1, 0.0,  L1, 0.0),         # hombro
        (theta2, 0.0,  L2, 0.0),         # codo
        (theta3, 0.0,  L3, 0.0),         # muneca
    ]


# ---------------------------------------------------------------
# Demostracion
# ---------------------------------------------------------------
if __name__ == "__main__":
    postura = [30.0, 60.0, -80.0, -40.0]           # grados
    t0, t1, t2, t3 = [math.radians(g) for g in postura]

    print("Postura (grados):", postura)

    # --- 2 GDL: solo hombro y codo, en el plano vertical ---
    r2, z2, phi2 = cadena_plana([L1, L2], [t1, t2])
    print("2 GDL  -> r = %7.2f mm   z = %7.2f mm   phi = %6.1f deg"
          % (r2, D0 + z2, math.degrees(phi2)))

    # --- 3 GDL: se agrega la muneca, aparece el control de orientacion ---
    r3, z3, phi3 = cadena_plana([L1, L2, L3], [t1, t2, t3])
    print("3 GDL  -> r = %7.2f mm   z = %7.2f mm   phi = %6.1f deg"
          % (r3, D0 + z3, math.degrees(phi3)))

    # --- 4 GDL: la base saca el brazo del plano ---
    x, y, z, phi = brazo_4gdl(t0, t1, t2, t3)
    print("4 GDL  -> x = %7.2f mm   y = %7.2f mm   z = %7.2f mm   phi = %6.1f deg"
          % (x, y, z, math.degrees(phi)))

    # --- El mismo resultado por Denavit-Hartenberg ---
    T = cinematica_directa_dh(tabla_dh_brazo(t0, t1, t2, t3))
    print("DH     -> x = %7.2f mm   y = %7.2f mm   z = %7.2f mm"
          % (T[0][3], T[1][3], T[2][3]))

    error = max(abs(T[0][3] - x), abs(T[1][3] - y), abs(T[2][3] - z))
    print("Diferencia maxima entre ambos caminos: %.2e mm" % error)
    assert error < 1e-9, "Los dos caminos deberian coincidir"
