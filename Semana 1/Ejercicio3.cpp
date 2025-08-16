/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480 
    
    Ejercicio 3 - Control de inventario multi-sucursal 

    Una empresa de distribución de productos desea llevar un control de su inventario en 6 almacenes diferentes. Cada almacén almacena hasta 15 productos. La matriz stock[6][15] indica la cantidad actual de cada producto por almacén. 
    El sistema debe: 

    a)	Registrar las existencias por producto y almacén. 
    b)	Detectar productos agotados por sucursal. 
    c)	Identificar el almacén con menor stock total. 
    d)	Emitir alertas por debajo de un umbral mínimo (configurable). 

    La clase Almacen contendrá los métodos necesarios para manipular la matriz de datos.
 */

#include <iostream>
#include <string>
#include <climits>
using namespace std;

const int NUM_ALMACENES = 6;
const int NUM_PRODUCTOS = 15;

class Almacen {
private:
    int stock[NUM_ALMACENES][NUM_PRODUCTOS];
    string nombresAlmacenes[NUM_ALMACENES] = {
        "Sucursal Central", "Sucursal Santo Domingo", "Sucursal Santiago", 
        "Sucursal Puerto Plata", "Sucursal Punta Cana", "Almacen Principal"
    };
    string nombresProductos[NUM_PRODUCTOS] = {
        "Laptop", "Teléfono", "Tablet", "Monitor", "Teclado", 
        "Mouse", "Impresora", "Router", "Disco Duro", "Memoria USB",
        "Cargador", "Audífonos", "Altavoz", "Webcam", "Micrófono"
    };

public:
    Almacen() {
        for(int i = 0; i < NUM_ALMACENES; i++) {
            for(int j = 0; j < NUM_PRODUCTOS; j++) {
                stock[i][j] = 0;
            }
        }
    }

    void registrarExistencias() {
        cout << "\nRegistro de Existencias:\n";
        for(int i = 0; i < NUM_ALMACENES; i++) {
            cout << "\n" << nombresAlmacenes[i] << ":\n";
            for(int j = 0; j < NUM_PRODUCTOS; j++) {
                cout << "  " << nombresProductos[j] << ": ";
                cin >> stock[i][j];
                while(stock[i][j] < 0) {
                    cout << "  Valor no válido. Ingrese cantidad >= 0: ";
                    cin >> stock[i][j];
                }
            }
        }
        cout << "Registro completado exitosamente!\n";
    }

    void mostrarProductosAgotados() {
        cout << "\nProductos Agotados por Sucursal:\n";
        for(int i = 0; i < NUM_ALMACENES; i++) {
            cout << "\n" << nombresAlmacenes[i] << ":\n";
            bool tieneAgotados = false;
            for(int j = 0; j < NUM_PRODUCTOS; j++) {
                if(stock[i][j] == 0) {
                    cout << "  - " << nombresProductos[j] << endl;
                    tieneAgotados = true;
                }
            }
            if(!tieneAgotados) {
                cout << "  No hay productos agotados\n";
            }
        }
    }

    void encontrarAlmacenMenorStock() {
        int totales[NUM_ALMACENES] = {0};
        int minStock = INT_MAX;
        int almacenMin = 0;

        for(int i = 0; i < NUM_ALMACENES; i++) {
            for(int j = 0; j < NUM_PRODUCTOS; j++) {
                totales[i] += stock[i][j];
            }
            if(totales[i] < minStock) {
                minStock = totales[i];
                almacenMin = i;
            }
        }

        cout << "\nAlmacén con menor stock total:\n";
        cout << nombresAlmacenes[almacenMin] << " (Total: " << minStock << " unidades)\n";
    }

    void alertasUmbral(int umbral) {
        cout << "\nAlertas de Stock (umbral < " << umbral << "):\n";
        for(int i = 0; i < NUM_ALMACENES; i++) {
            cout << "\n" << nombresAlmacenes[i] << ":\n";
            bool tieneAlertas = false;
            for(int j = 0; j < NUM_PRODUCTOS; j++) {
                if(stock[i][j] > 0 && stock[i][j] < umbral) {
                    cout << "  - " << nombresProductos[j] << ": " << stock[i][j] << " unidades\n";
                    tieneAlertas = true;
                }
            }
            if(!tieneAlertas) {
                cout << "  No hay productos bajo el umbral\n";
            }
        }
    }

    void mostrarMenu() {
        cout << "\nSistema de Control de Inventario Grupo 12\n";
        cout << "=============================================\n";
        cout << "1. Registrar existencias\n";
        cout << "2. Mostrar productos agotados\n";
        cout << "3. Encontrar almacén con menor stock\n";
        cout << "4. Generar alertas por umbral mínimo\n";
        cout << "5. Salir\n";
    }
};

int main() {
    Almacen sistema;
    int opcion, umbral;

    do {
        sistema.mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                sistema.registrarExistencias();
                break;
            case 2:
                sistema.mostrarProductosAgotados();
                break;
            case 3:
                sistema.encontrarAlmacenMenorStock();
                break;
            case 4:
                cout << "Ingrese el umbral mínimo para alertas: ";
                cin >> umbral;
                sistema.alertasUmbral(umbral);
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while(opcion != 5);

    return 0;
}
