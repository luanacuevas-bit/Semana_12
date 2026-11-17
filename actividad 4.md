Tabla de Comparacion de Rendimiento

| n       | Hash (ns) | BST/binaria (ns) | Ratio BST/Hash | ¿Confirma O(1) vs O(log n)? |
|---------|-----------|-----------------------|-------------------|---------------------------------------------------------------------------|
| 1 000   | 320.0 ns  |  39960.0 ns           |   124.88x         |    Parcial: el hash gana, pero el valor de la búsqueda binaria es atípico |
| 5 000   | 320.0 ns  |  880.0 ns             |    2.75x          |     si                                                                    |
| 10 000  | 700.0 ns  |  3480.0 ns            |    4.97x          |     si                                                                    |
| 50 000  | 1420.0 ns |  4260.0 ns            |   3.00x           |     si                                                                    |
| 100 000 | 2220.0 ns |  4980.0 ns            |   2.24x           |     si                                                                    |


Conclusión: ¿Los resultados validan la complejidad teórica? Explique las posibles fuentes de variación:

Sí, los resultados confirman la teoría. En todos los tamaños el hash fue más rápido que la búsqueda binaria,
tal como se espera de O(1) frente a O(log n).
Pero no salió perfecto. En n = 1 000 la búsqueda binaria dio un tiempo 
muy alto (39 960 ns), seguramente un error de medición en una de las repeticiones. Además, 
el hash no se quedó constante, subió de 320 a 2 220 ns al aumentar n.
Esto pasa porque medimos tiempos muy pequeños y con pocas repeticiones (5), así que la
computadora, los programas en segundo plano y la memoria caché mueven los resultados.
