# SIS210 – Semana 12: Tablas Hash

**Universidad Nacional del Altiplano – Puno**
Escuela Profesional de Ingeniería de Sistemas
Curso: SIS210 Algoritmos y Estructuras de Datos (2026-II)
Docente: Dr. Aldo Hernán Zanabria Gálvez

Práctica en grupo sobre **tablas hash**: funciones hash, colisiones (encadenamiento separado) y rehashing.

## Integrantes y distribución del trabajo

| Integrante | Actividad |
|---|---|
| Angheli Luana Cuevas Yucra | Actividad 1 y 2 (cálculo manual y encadenamiento) |
| Stefany Marie Pampa Yucra | Actividad 3 (`hash.h` en C++17) |
| Merhi Estefany Quispe Zela | Actividad 4 (experimento Hash vs. búsqueda binaria) |

## Resumen de resultados (Actividades 1 y 2)

**Actividad 1A – Método de división (m = 13).** Las claves 17, 43, 30, 56, 82 y 95 dan todas el índice 4: hay colisión total, porque se diferencian entre sí por múltiplos de 13.

**Actividad 1B – djb2 (m = 31).**

| Cadena | h final | h mod 31 |
|---|---|---|
| `SIS` | 193469876 | 23 |
| `AVL` | 193450696 | 1 |

No colisionan.

**Actividad 2 – Encadenamiento separado (m = 7).** Claves insertadas al frente de la lista: 50, 700, 76, 85, 92, 73, 101, 146, 63, 21.

```
[0] → 21 → 63 → 700 → NULL
[1] → 92 → 85 → 50 → NULL
[2] → NULL
[3] → 101 → 73 → NULL
[4] → NULL
[5] → NULL
[6] → 146 → 76 → NULL
```

- Factor de carga: α = 10/7 ≈ 1.43 (supera 0.75, por lo que se necesita rehashing).
- Longitud máxima de lista: 3. Cubos vacíos: 3 (índices 2, 4 y 5).

## Cómo ejecutar

**Python 3.12** (Actividades 1B y 4):

```bash
python actividad1-2/verificacion_djb2.py
python actividad4/experimento_hash.py
```

**C++17** (Actividad 3):

```bash
cd actividad3
g++ -std=c++17 -Wall test_hash.cpp -o test_hash
./test_hash          # en Windows: test_hash.exe
```

Si todo está bien, debe imprimir `Todos los test pasaron!`.

## Forma de trabajo en Git

- Cada integrante trabaja en su propia rama: `actividad-1-2`, `actividad-3`, `actividad-4`.
- Los cambios llegan a `main` mediante Pull Request, revisado por otra integrante.
- Mensajes de commit claros, por ejemplo: `Act 3: implementa insertar y buscar`.

```bash
git checkout -b actividad-3
git add .
git commit -m "Act 3: implementa insertar y buscar"
git push -u origin actividad-3
```

## Entrega

Según la guía, se sube a la plataforma virtual: (1) la guía resuelta en PDF, (2) `hash.h` con la implementación y (3) `test_hash.cpp` compilado y corrido.

## Referencias

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to algorithms* (4.ª ed.). MIT Press.
- Zanabria Gálvez, A. H. (2026). *Guía teórica, Semana 12: Tablas hash* [Material de curso]. SIS210, UNAP.
