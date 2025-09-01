/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480 

    Ejercicio 2 - Control de stock mínimo de productos

    Un minimercado gestiona su inventario mediante una lista enlazada. 
    Cada producto tiene: código, nombre, y cantidad disponible en almacén. 

    Se debe: 

        a)	Insertar los productos con sus datos completos. 
        b)	Mostrar los productos cuyo stock sea menor a 5 unidades. 
        c)	Permitir actualizar el stock de un producto dado su código. 
        d)	Calcular el tiempo de ejecución de cada función y el tiempo total del programa.
*/
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Producto {
    int codigo;
    string nombre;
    int cantidad;
    Producto* siguiente;
};

class Inventario {
private:
    Producto* cabeza;

public:
    Inventario() : cabeza(nullptr) {}

    void insertarProducto(int codigo, string nombre, int cantidad) {
        auto inicio = high_resolution_clock::now();

        Producto* nuevo = new Producto{codigo, nombre, cantidad, nullptr};
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Producto* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo de ejecución al insertar producto " << nombre << ": " << duracion.count() << " microsegundos" << endl;
    }

    // Mostrar productos con stock por debajo de 5 (stock < 5)
    void mostrarStockBajo() {
        auto inicio = high_resolution_clock::now();

        cout << "\n--- Productos con stock por debajo de 5 unidades ---" << endl;
        Producto* actual = cabeza;
        while (actual) {
            if (actual->cantidad < 5) {
                cout << "Código: " << actual->codigo
                     << " | Nombre: " << actual->nombre
                     << " | Cantidad: " << actual->cantidad << endl;
            }
            actual = actual->siguiente;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo de ejecución para mostrar productos con stock bajo: " << duracion.count() << " microsegundos" << endl;
    }

    // Actualizar cantidad en stock de un producto segun su código
    void actualizarStock(int codigo, int nuevaCantidad) {
        auto inicio = high_resolution_clock::now();

        Producto* actual = cabeza;
        bool encontrado = false;

        while (actual) {
            if (actual->codigo == codigo) {
                actual->cantidad = nuevaCantidad;
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (encontrado) {
            cout << "Stock actualizado para el producto con código " << codigo << endl;
        } else {
            cout << "Producto con código " << codigo << " no encontrado." << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo de ejecución para actualizar stock: " << duracion.count() << " microsegundos" << endl;
    }

    void mostrarTodos() {
        cout << "\n--- Inventario completo ---" << endl;
        Producto* actual = cabeza;
        while (actual) {
            cout << "Código: " << actual->codigo
                 << " | Nombre: " << actual->nombre
                 << " | Cantidad: " << actual->cantidad << endl;
            actual = actual->siguiente;
        }
    }

    ~Inventario() {
        while (cabeza) {
            Producto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main() {
    auto inicioPrograma = high_resolution_clock::now();

    Inventario inventario;
    //Insertamos los productos
    inventario.insertarProducto(101, "Arroz", 10);
    inventario.insertarProducto(102, "Azúcar", 3);
    inventario.insertarProducto(103, "Aceite", 7);
    inventario.insertarProducto(104, "Leche", 2);
    inventario.insertarProducto(105, "Café", 12);

    inventario.mostrarTodos();
    inventario.mostrarStockBajo();
    inventario.actualizarStock(104, 8); 
    inventario.mostrarTodos();
    inventario.mostrarStockBajo();

    auto finPrograma = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finPrograma - inicioPrograma);
    cout << "\nTiempo total de ejecución del programa: " << duracionTotal.count() << " microsegundos" << endl;

    return 0;
}