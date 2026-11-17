// test_hash.cpp — NO MODIFICAR
#include <cassert>
#include <string>
#include "hash.h"

int main() {
    TablaHash<std::string, int> th(7);

    // P1: inserción y búsqueda básica
    th.insertar("Alice", 95);
    th.insertar("Bob", 80);
    th.insertar("Carol", 88);
    assert(th.buscar("Alice").value() == 95);   // P1a
    assert(th.buscar("Bob").value() == 80);     // P1b
    assert(th.tamanio() == 3);                  // P1c

    // P2: actualización de valor existente
    th.insertar("Alice", 99);
    assert(th.buscar("Alice").value() == 99);   // P2: actualizado
    assert(th.tamanio() == 3);                  // P2: no aumentó

    // P3: clave inexistente
    assert(!th.buscar("Zara").has_value());     // P3

    // P4: eliminación
    assert(th.eliminar("Bob") == true);         // P4a
    assert(!th.buscar("Bob").has_value());      // P4b
    assert(th.eliminar("Bob") == false);        // P4c: ya no existe
    assert(th.tamanio() == 2);                  // P4d

    // P5: rehashing automático
    TablaHash<int, std::string> th2(7);
    for (int i = 0; i < 10; ++i)                // α > 0.75 → rehash
        th2.insertar(i, "v" + std::to_string(i));
    assert(th2.cubos() > 7);                    // P5a: rehash ocurrió
    assert(th2.buscar(5).value() == "v5");      // P5b: datos intactos
    assert(th2.factor_carga() < 0.76);          // P5c

    std::cout << "Todos los test pasaron!\n";
    return 0;
}