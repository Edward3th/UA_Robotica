# UA_Robótica

Material descargable de las guías de robótica de la **Universidad Autónoma de
Chile**: los libros en PDF, el código de Arduino y Python, los modelos 3D y las
plantillas de cálculo.

Todo es de descarga libre. Para bajar el repositorio completo usa el botón
verde **Code → Download ZIP**; no necesitas una cuenta de GitHub. También
puedes abrir cualquier archivo y descargarlo por separado.

## Guías

| # | Guía | De qué trata | Descarga |
|---|---|---|---|
| 1 | **Introducción a la Robótica** | Un robot futbolista controlado por Bluetooth: diseño CAD, impresión 3D, electrónica, Arduino y App Inventor | [PDF](guia-1-introduccion-a-la-robotica/Introduccion-a-la-Robotica.pdf) · [archivos](guia-1-introduccion-a-la-robotica/) |
| 2 | **Robots Articulados** | Brazos robóticos de 2, 3 y 4 grados de libertad: cinemática directa e inversa, actuadores y control por serial con Python y Arduino | [PDF](guia-2-robots-articulados/Robots-Articulados.pdf) · [archivos](guia-2-robots-articulados/) |

## Contenido

```
UA_Robotica/
├── guia-1-introduccion-a-la-robotica/
│   ├── Introduccion-a-la-Robotica.pdf
│   ├── codigo/          programas de Arduino (Capítulos 5 y 6)
│   └── chasis/          modelos STL del chasis del autor
└── guia-2-robots-articulados/
    ├── Robots-Articulados.pdf
    ├── codigo/          Python y Arduino (Capítulos 3 a 7)
    └── plantillas/      planilla de dimensionamiento y hoja de calibración
```

Cada carpeta de guía tiene su propio README con el detalle de cada archivo.

## Qué necesitas

- **Arduino IDE** y una placa **Arduino UNO** para los archivos `.ino`. Cada
  programa está dentro de una carpeta con su mismo nombre, porque el IDE así
  lo exige: ábrelo desde ahí, sin moverlo ni renombrarlo.
- **Python 3** para los archivos `.py` de la guía 2. Los de cinemática solo usan
  la biblioteca estándar; los que hablan con el brazo necesitan además
  `pyserial` (`pip install pyserial`).
- Un laminador, por ejemplo **Ultimaker Cura**, para imprimir los `.stl`.
- **LibreOffice Calc**, **Excel** o **Google Sheets** para la planilla `.ods`.

## Licencia

Los libros y todo el material de este repositorio se distribuyen bajo licencia
[Creative Commons Atribución-NoComercial-CompartirIgual 4.0 Internacional
(CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.es).
Puedes copiar, distribuir y adaptar este material citando la fuente, sin fines
comerciales y compartiendo las obras derivadas bajo la misma licencia. Detalle
en [LICENSE.md](LICENSE.md).

## Autor

**Eduardo Fuentes Fierro** — Ingeniero Civil Mecánico, Magíster en Ciencias de
la Ingeniería · Universidad Autónoma de Chile.
