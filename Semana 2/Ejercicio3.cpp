/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480 

    Ejercicio 3 - Común para todos los equipos - Navegación de historial web con lista doble

    Un navegador web desea implementar su historial de navegación. Cada nodo en la lista doble representa una página visitada con: URL, fecha y hora de visita. 

    El sistema debe: 

        a)	Insertar cada nueva visita al final de la lista. 
        b)	Permitir al usuario desplazarse hacia adelante o atrás desde la página actual. 
        c)	Eliminar una URL específica del historial. 
        d)	Mostrar el historial completo en orden cronológico inverso (última a primera visita). 
        e)	Calcular el tiempo de ejecución de cada función y el tiempo total del programa.
*/
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Pagina {
    string url;
    string fechaHora;
    Pagina* anterior;
    Pagina* siguiente;
};

class Historial {
private:
    Pagina* cabeza;
    Pagina* cola;
    Pagina* actual;

public:
    Historial() : cabeza(nullptr), cola(nullptr), actual(nullptr) {}

    void insertarVisita(string url, string fechaHora) {
        auto inicio = high_resolution_clock::now();

        Pagina* nueva = new Pagina{url, fechaHora, cola, nullptr};
        if (!cabeza) {
            cabeza = cola = actual = nueva;
        } else {
            cola->siguiente = nueva;
            cola = nueva;
            actual = cola; // La página actual es la última visitada
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "Tiempo de ejecución de inserción de visita a " << url << ": " << duracion.count() << " microsegundos" << endl;
    }

    void irAtras() {
        auto inicio = high_resolution_clock::now();

        if (actual && actual->anterior) {
            actual = actual->anterior;
            cout << "\nRetrocediendo. Página actual: " << actual->url << endl;
        } else {
            cout << "\nNo hay más páginas hacia atrás." << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo al retroceder: " << duracion.count() << " microsegundos" << endl;
    }

    void irAdelante() {
        auto inicio = high_resolution_clock::now();

        if (actual && actual->siguiente) {
            actual = actual->siguiente;
            cout << "\nAvanzando. Página actual: " << actual->url << endl;
        } else {
            cout << "\nNo hay más páginas hacia adelante." << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo al avanzar: " << duracion.count() << " microsegundos" << endl;
    }

    void eliminarURL(string url) {
        auto inicio = high_resolution_clock::now();

        Pagina* temp = cabeza;
        while (temp) {
            if (temp->url == url) {
                if (temp->anterior) temp->anterior->siguiente = temp->siguiente;
                else cabeza = temp->siguiente;

                if (temp->siguiente) temp->siguiente->anterior = temp->anterior;
                else cola = temp->anterior;

                if (actual == temp) actual = temp->siguiente ? temp->siguiente : temp->anterior;

                delete temp;
                cout << "\nURL eliminada: " << url << endl;
                break;
            }
            temp = temp->siguiente;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo al eliminar URL: " << duracion.count() << " microsegundos" << endl;
    }

    void mostrarHistorial() {
        auto inicio = high_resolution_clock::now();

        cout << "\n--- Historial (Registro de visitas) ---" << endl;
        Pagina* temp = cola;
        while (temp) {
            cout << "URL Visitada: " << temp->url
                 << " | Fecha y hora: " << temp->fechaHora << endl;
            temp = temp->anterior;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio);
        cout << "\nTiempo de ejecución para mostrar historial de búsqueda: " << duracion.count() << " microsegundos" << endl;
    }

    ~Historial() {
        while (cabeza) {
            Pagina* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main() {
    auto inicioPrograma = high_resolution_clock::now();

    Historial historial;

    historial.insertarVisita("google.com", "2025-09-01 10:00");
    historial.insertarVisita("uapa.edu.do", "2025-09-01 10:05");
    historial.insertarVisita("youtube.com", "2025-09-01 10:10");
    historial.insertarVisita("github.com", "2025-09-01 10:15");

    historial.mostrarHistorial();

    historial.irAtras();
    historial.irAtras();
    historial.irAdelante();

    historial.eliminarURL("github.com");

    historial.mostrarHistorial();

    auto finPrograma = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finPrograma - inicioPrograma);
    cout << "\nTiempo total de ejecución del programa: " << duracionTotal.count() << " microsegundos" << endl;

    return 0;
}