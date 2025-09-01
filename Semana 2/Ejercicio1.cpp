/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480 

    Ejercicio 1 - Listado dinámico de tareas priorizadas

    Una aplicación de gestión de tareas desea mantener un listado de actividades pendientes ordenadas por prioridad. 
    Cada nodo representa una tarea con: nombre, nivel de prioridad (entero) y estado (pendiente o completada). 

    El sistema debe: 

        a)	Insertar las tareas en orden descendente según su prioridad. 
        b)	Mostrar todas las tareas que estén en estado "pendiente". 
        c)	Eliminar las tareas que se marquen como "completadas". 

    Calcular el tiempo de ejecución de cada función y el tiempo total del programa.
*/

#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Tarea {
    string nombre;
    int prioridad;
    string estado; // Tenemos dos estados posibles, que son (pendiente o completada)
    Tarea* siguiente;
};

class ListaTareas {
private:
    Tarea* cabeza;

public:
    ListaTareas() : cabeza(nullptr) {}

    void insertarTarea(string nombre, int prioridad, string estado) {
        auto inicio = high_resolution_clock::now();

        Tarea* nueva = new Tarea{nombre, prioridad, estado, nullptr};

        if (!cabeza || prioridad > cabeza->prioridad) {
            nueva->siguiente = cabeza;
            cabeza = nueva;
        } else {
            Tarea* actual = cabeza;
            while (actual->siguiente && actual->siguiente->prioridad >= prioridad) {
                actual = actual->siguiente;
            }
            nueva->siguiente = actual->siguiente;
            actual->siguiente = nueva;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo para insertar tarea #" << prioridad << ": " << duracion.count() << " microsegundos" << endl;
    }

    void mostrarTodas() {
        auto inicio = high_resolution_clock::now();

        Tarea* actual = cabeza;
        while (actual) {
            cout << "Tarea: " << actual->nombre
                 << " | Prioridad: " << actual->prioridad
                 << " | Estado: " << actual->estado << endl;
            actual = actual->siguiente;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo al mostrar todas las tareas: " << duracion.count() << " microsegundos" << endl;
    }

    void mostrarPendientes() {
        auto inicio = high_resolution_clock::now();

        Tarea* actual = cabeza;
        while (actual) {
            if (actual->estado == "pendiente") {
                cout << "Tarea: " << actual->nombre 
                     << " | Prioridad: " << actual->prioridad 
                     << " | Estado: " << actual->estado << endl;
            }
            actual = actual->siguiente;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo al mostrar tareas pendientes: " << duracion.count() << " microsegundos" << endl;
    }

    void eliminarCompletadas() {
        auto inicio = high_resolution_clock::now();

        while (cabeza && cabeza->estado == "completada") {
            Tarea* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }

        Tarea* actual = cabeza;
        while (actual && actual->siguiente) {
            if (actual->siguiente->estado == "completada") {
                Tarea* temp = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                delete temp;
            } else {
                actual = actual->siguiente;
            }
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo al eliminar tareas completadas: " << duracion.count() << " microsegundos" << endl;
    }

    ~ListaTareas() {
        while (cabeza) {
            Tarea* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main() {
    auto inicioPrograma = high_resolution_clock::now();

    ListaTareas lista;

    lista.insertarTarea("Comprar Purina del perro", 2, "pendiente");
    lista.insertarTarea("Estudiar C++, para que la Maestra Zoila No me queme", 5, "pendiente");
    lista.insertarTarea("Prepararme para el CTF Interuniversitario", 3, "completada");
    lista.insertarTarea("Pagar facturas luz", 4, "pendiente");
    lista.insertarTarea("Reclamar Factura de luz, que llegó altisima", 1, "completada");

    cout << "\n------- Todas las tareas --------" << endl;
    lista.mostrarTodas();

    cout << "\n------- Tareas Pendientes --------" << endl;
    lista.mostrarPendientes();

    cout << "\n------- Eliminar tareas completadas --------" << endl;
    lista.eliminarCompletadas();

    cout << "\n------- Tareas Pendientes --------" << endl;
    lista.mostrarTodas();

    auto finPrograma = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finPrograma - inicioPrograma);
    cout << "\nTiempo total de ejecucion del programa: " << duracionTotal.count() << " microsegundos" << endl;

    return 0;
}