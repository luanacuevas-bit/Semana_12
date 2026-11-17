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
## Actividad 3 – Implementación de `hash.h`
Tabla hash genérica `TablaHash<K, V>` en C++17 con **encadenamiento separado** y **rehashing automático**. Los nodos se manejan con `std::unique_ptr`, sin `new` ni `delete` manuales.

### Archivos (carpeta `actividad3/`)

| Archivo | Descripción |
|---|---|
| `hash.h` | Implementación de la tabla hash |
| `test_hash.cpp` | Casos de prueba con `assert` (del docente, sin modificar) |

### Métodos implementados

| Método | Qué hace |
|---|---|
| `insertar(clave, valor)` | Si la clave existe, actualiza el valor; si no, inserta al frente del cubo e incrementa `_n`. Hace `rehash()` si α > 0.75. |
| `buscar(clave)` | Recorre la lista del cubo y devuelve `std::optional<V>` (`std::nullopt` si no existe). |
| `eliminar(clave)` | Desencadena el nodo con `unique_ptr` (sin `delete`) y decrementa `_n`. Devuelve `true` o `false`. |
| `rehash()` | Crea una tabla de tamaño `siguiente_primo(2 * m)` y re-enlaza los nodos sin copiarlos. |

### Notas de implementación y dificultades encontradas

- **`unique_ptr` no se copia, solo se mueve.** Insertar al frente se resolvió con `nuevo->sig = std::move(_tabla[idx])` y luego poniendo el nodo nuevo como cabeza.
- **Eliminar sin `delete`.** Se usó un puntero al `unique_ptr` que apunta al nodo actual (`auto* enlace = &_tabla[idx]`), así borrar la cabeza o un nodo intermedio es el mismo código.
- **Rehash.** Dentro de `rehash()` el índice se calcula con `% nuevo_m` y no con `_idx()`, que usaría el `m` viejo. Además, se guarda el siguiente nodo antes de re-enlazar para no perder la lista.
- **Actualizar vs. insertar.** `_n` solo aumenta cuando la clave es nueva (test P2).
- **`#include <iostream>`.** `test_hash.cpp` usa `std::cout` sin incluirlo; como no se puede modificar, se agregó en `hash.h`.

### Observaciones

- En el test P5 (m = 7), el rehash ocurre al insertar el 6.º elemento (α = 6/7 ≈ 0.86) y la tabla pasa a 17 cubos. Al final α = 10/17 ≈ 0.59, menor que 0.76.
- Usar tamaños primos reparte mejor las claves y reduce las colisiones.
- El rehash cuesta O(n), pero ocurre pocas veces, por lo que `insertar` mantiene un costo O(1) promedio.
- En el peor caso (todas las claves en un mismo cubo) las operaciones pasan a O(n).
- Limitaciones: la tabla solo crece (no se reduce al eliminar) y no tiene iteradores. Para una versión más completa se podrían agregar.
- Se verificó con `-Wall -Wextra` y con `-fsanitize=address,undefined`: sin fugas de memoria ni accesos inválidos.

### Cómo ejecutar

```bash
cd actividad3
g++ -std=c++17 -Wall test_hash.cpp -o test_hash
./test_hash          # en Windows: test_hash.exe
```

### Resultado

Pasan los 5 grupos de pruebas (P1–P5) y el programa imprime:

```
Todos los test pasaron!
```

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
ACTIVIDAD 4 

Comparé el tiempo de búsqueda en una tabla hash (dict de Python) contra una búsqueda binaria sobre una lista ordenada (bisect), que simula un BST. Cada tamaño se repitió 5 veces y se promedió.

Resultados:

n = 1 000: Hash 320.0 ns, BST 39 960.0 ns, ratio 124.88x

n = 5 000: Hash 320.0 ns, BST 880.0 ns, ratio 2.75x

n = 10 000: Hash 700.0 ns, BST 3 480.0 ns, ratio 4.97x

n = 50 000: Hash 1 420.0 ns, BST 4 260.0 ns, ratio 3.00x

n = 100 000: Hash 2 220.0 ns, BST 4 980.0 ns, ratio 2.24x

Conclusión: los resultados confirman la teoría, porque en todos los tamaños el hash fue más rápido que la búsqueda binaria, como se espera de O(1) frente a O(log n). No salió perfecto: en n = 1 000 la búsqueda binaria dio un valor muy alto (39 960 ns), probablemente un error de medición en una de las repeticiones, y el hash no se mantuvo constante, subió de 320 a 2 220 ns al aumentar n. Esto pasa porque se miden tiempos muy pequeños con pocas repeticiones, y factores como la computadora, los programas en segundo plano y la memoria caché afectan los resultados.

## Entrega

Según la guía, se sube a la plataforma virtual: (1) la guía resuelta en PDF, (2) `hash.h` con la implementación y (3) `test_hash.cpp` compilado y corrido.

## Referencias

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to algorithms* (4.ª ed.). MIT Press.
- Zanabria Gálvez, A. H. (2026). *Guía teórica, Semana 12: Tablas hash* [Material de curso]. SIS210, UNAP.
