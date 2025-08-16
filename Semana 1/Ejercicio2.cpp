/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480
    
    Ejercicio 2 - Registro de Calificaciones en Bootcamp 

    Una academia técnica gestiona las calificaciones de los estudiantes en 5 evaluaciones clave. Cada estudiante tiene: nombre, matrícula, calificaciones[], promedio y estado (aprobado/reprobado). 
    Se debe: 

    a)	Registrar las notas por estudiante. 
    b)	Calcular promedio automático. 
    c)	Mostrar los estudiantes aprobados con promedio ≥ 70. 
    d)	Ordenar estudiantes por promedio. 

    - Implementar usando un arreglo unidimensional de objetos Estudiante.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const int NUM_EVALUACIONES = 5;
const int NOTA_APROBACION = 70;

class Estudiante {
private:
    string nombre;
    string matricula;
    float calificaciones[NUM_EVALUACIONES];
    float promedio;
    bool aprobado;

public:
    // Constructor
    Estudiante() : promedio(0), aprobado(false) {}

    void setNombre(string n) { nombre = n; }
    void setMatricula(string m) { matricula = m; }
    void setCalificacion(int index, float calif) { 
        calificaciones[index] = calif; 
    }

    void calcularPromedio() {
        float suma = 0;
        for (int i = 0; i < NUM_EVALUACIONES; i++) {
            suma += calificaciones[i];
        }
        promedio = suma / NUM_EVALUACIONES;
        aprobado = (promedio >= NOTA_APROBACION);
    }

    string getNombre() const { return nombre; }
    string getMatricula() const { return matricula; }
    float getPromedio() const { return promedio; }
    bool estaAprobado() const { return aprobado; }
    float getCalificacion(int index) const { return calificaciones[index]; }

    // Método para mostrar información
    void mostrarInfo() const {
        cout << left << setw(15) << matricula 
             << setw(25) << nombre 
             << fixed << setprecision(2) << setw(10) << promedio 
             << (aprobado ? "Aprobado" : "Reprobado") << endl;
    }
};

// Prototipos de funciones
void mostrarMenu();
void registrarEstudiante(Estudiante estudiantes[], int &contador);
void calcularPromedios(Estudiante estudiantes[], int contador);
void mostrarAprobados(const Estudiante estudiantes[], int contador);
void ordenarPorPromedio(Estudiante estudiantes[], int contador);
void mostrarTodos(const Estudiante estudiantes[], int contador);
bool compararPromedios(const Estudiante &a, const Estudiante &b);

int main() {
    const int MAX_ESTUDIANTES = 50;
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int contadorEstudiantes = 0;

    cout << "Sistema de Registro de Calificaciones Grupo 12\n";
    cout << "=================================================\n\n";

    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                registrarEstudiante(estudiantes, contadorEstudiantes);
                break;
            case 2:
                calcularPromedios(estudiantes, contadorEstudiantes);
                break;
            case 3:
                mostrarAprobados(estudiantes, contadorEstudiantes);
                break;
            case 4:
                ordenarPorPromedio(estudiantes, contadorEstudiantes);
                break;
            case 5:
                mostrarTodos(estudiantes, contadorEstudiantes);
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
        }
    } while(opcion != 0);

    return 0;
}

void mostrarMenu() {
    cout << "\nMenu Principal:\n";
    cout << "1. Registrar nuevo estudiante\n";
    cout << "2. Calcular promedios\n";
    cout << "3. Mostrar estudiantes aprobados\n";
    cout << "4. Ordenar estudiantes por promedio\n";
    cout << "5. Mostrar todos los estudiantes\n";
    cout << "0. Salir\n";
}

void registrarEstudiante(Estudiante estudiantes[], int &contador) {
    const int MAX_ESTUDIANTES = 50;
    if (contador >= MAX_ESTUDIANTES) {
        cout << "Capacidad maxima alcanzada. No se pueden registrar mas estudiantes.\n";
        return;
    }

    cout << "\nRegistro de nuevo estudiante #" << contador + 1 << endl;

    string nombre, matricula;
    float calif;

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nombre);
    estudiantes[contador].setNombre(nombre);

    cout << "Matricula: ";
    getline(cin, matricula);
    estudiantes[contador].setMatricula(matricula);

    cout << "Ingrese las 5 calificaciones:\n";
    for (int i = 0; i < NUM_EVALUACIONES; i++) {
        cout << "Evaluacion " << i+1 << ": ";
        cin >> calif;
        
        while (calif < 0 || calif > 100) {
            cout << "Calificacion no valida. Debe ser entre 0 y 100. Intente nuevamente: ";
            cin >> calif;
        }
        estudiantes[contador].setCalificacion(i, calif);
    }

    contador++;
    cout << "Estudiante registrado exitosamente!\n";
}

void calcularPromedios(Estudiante estudiantes[], int contador) {
    if (contador == 0) {
        cout << "No hay estudiantes registrados para calcular promedios.\n";
        return;
    }

    for (int i = 0; i < contador; i++) {
        estudiantes[i].calcularPromedio();
    }

    cout << "Promedios calculados exitosamente!\n";
}

void mostrarAprobados(const Estudiante estudiantes[], int contador) {
    if (contador == 0) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\nEstudiantes Aprobados (Promedio >= " << NOTA_APROBACION << ")\n";
    cout << "========================================\n";
    cout << left << setw(15) << "Matricula" << setw(25) << "Nombre" << "Promedio\n";
    cout << "----------------------------------------\n";

    int aprobados = 0;
    for (int i = 0; i < contador; i++) {
        if (estudiantes[i].estaAprobado()) {
            cout << left << setw(15) << estudiantes[i].getMatricula() 
                 << setw(25) << estudiantes[i].getNombre() 
                 << fixed << setprecision(2) << estudiantes[i].getPromedio() << endl;
            aprobados++;
        }
    }

    if (aprobados == 0) {
        cout << "No hay estudiantes aprobados.\n";
    } else {
        cout << "Total aprobados: " << aprobados << endl;
    }
}

bool compararPromedios(const Estudiante &a, const Estudiante &b) {
    return a.getPromedio() > b.getPromedio(); 
}

void ordenarPorPromedio(Estudiante estudiantes[], int contador) {
    if (contador == 0) {
        cout << "No hay estudiantes registrados para ordenar.\n";
        return;
    }

    sort(estudiantes, estudiantes + contador, compararPromedios);
    cout << "Estudiantes ordenados por promedio (de mayor a menor) exitosamente!\n";
    mostrarTodos(estudiantes, contador);
}

void mostrarTodos(const Estudiante estudiantes[], int contador) {
    if (contador == 0) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\nListado Completo de Estudiantes\n";
    cout << "====================================================================\n";
    cout << left << setw(15) << "Matricula" << setw(25) << "Nombre" 
         << setw(10) << "Promedio" << "Estado\n";
    cout << "--------------------------------------------------------------------\n";

    for (int i = 0; i < contador; i++) {
        estudiantes[i].mostrarInfo();
    }
}