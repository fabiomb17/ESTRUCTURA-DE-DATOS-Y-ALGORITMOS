/*  ESTRUCTURA DE DATOS Y ALGORITMOS

    Grupo 12 compuesto por:

    FABIO MUÑOZ – 100069637
    MELODY MORILLO – 100067738
    EDISON MERCEDES – 100069673
    YERNISON NÚÑEZ – 100063221
    DAURY JOSE OGANDO – 100070480 
    
    Ejercicio 1 - Almacén Central de Componentes Electrónicos 

    Una empresa de ensamblaje de equipos computacionales gestiona un almacén donde guarda distintos componentes electrónicos (procesadores, memorias, discos, otros). 
    De cada componente se conoce el código, nombre, precio de costo y la cantidad en existencia. 
    Los productos nacionales tienen como atributo adicional la empresa productora, y los importados el país de procedencia y precio de compra en divisas. 

    a)	El sistema debe calcular el precio de venta: 
        •	Nacionales: precio de costo + 5%. 
        •	Importados: precio de costo + 5% + (27 × precio en USD). 
    b)	Registrar nuevos componentes. 
    c)	Modificar productos existentes. 
    d)	Mostrar un listado de productos nacionales con precio superior a un valor dado. 
    e)	Listar productos extranjeros por país de procedencia. 
    f)	Detectar productos con stock por debajo de su nivel mínimo. 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes para el programa
#define MAX_COMPONENTES 100
#define MAX_LONGITUD 50

// Variables globales para los arreglos unidimensionales
int codigos[MAX_COMPONENTES];
char nombres[MAX_COMPONENTES][MAX_LONGITUD];
float precios_costo[MAX_COMPONENTES];
int cantidades_existencia[MAX_COMPONENTES];
int tipos[MAX_COMPONENTES]; // 1 para nacional, 0 para importado
char empresas_paises[MAX_COMPONENTES][MAX_LONGITUD];
float precios_usd[MAX_COMPONENTES];

int num_componentes = 0; // Contador de componentes registrados

// Prototipos de funciones
void menu_principal();
void registrar_componente();
void modificar_componente();
void calcular_precio_venta();
void listar_nacionales_precio_superior();
void listar_importados_por_pais();
void detectar_stock_bajo();

int main() {
    printf("Sistema de Gestion de Almacen Grupo 12\n");
    printf("=======================================\n\n");
    
    menu_principal();
    
    return 0;
}

// Funcion para mostrar el menu principal
void menu_principal() {
    int opcion;
    
    do {
        printf("\nMenu Principal:\n");
        printf("1. Registrar nuevo producto\n");
        printf("2. Modificar producto existente\n");
        printf("3. Calcular precio de venta\n");
        printf("4. Listar productos nacionales\n");
        printf("5. Listar productos importados por pais\n");
        printf("6. Productos con bajo stock \n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                registrar_componente();
                break;
            case 2:
                modificar_componente();
                break;
            case 3:
                calcular_precio_venta();
                break;
            case 4:
                listar_nacionales_precio_superior();
                break;
            case 5:
                listar_importados_por_pais();
                break;
            case 6:
                detectar_stock_bajo();
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while(opcion != 0);
}

void registrar_componente() {
    if (num_componentes >= MAX_COMPONENTES) {
        printf("El inventario esta lleno. No se pueden agregar mas componentes.\n");
        return;
    }
    
    printf("\nRegistro de nuevo componente:\n");
    
    printf("Codigo: ");
    scanf("%d", &codigos[num_componentes]);
    
    printf("Nombre: ");
    scanf(" %[^\n]", nombres[num_componentes]);
    
    printf("Precio de costo: ");
    scanf("%f", &precios_costo[num_componentes]);
    
    printf("Cantidad en existencia: ");
    scanf("%d", &cantidades_existencia[num_componentes]);
    
    printf("Es nacional (1) o importado (0)? ");
    scanf("%d", &tipos[num_componentes]);
    
    if (tipos[num_componentes]) {
        printf("Empresa productora: ");
        scanf(" %[^\n]", empresas_paises[num_componentes]);
        precios_usd[num_componentes] = 0.0;
    } else {
        printf("Pais de procedencia: ");
        scanf(" %[^\n]", empresas_paises[num_componentes]);
        
        printf("Precio en dolares: ");
        scanf("%f", &precios_usd[num_componentes]);
    }
    
    num_componentes++;
    printf("Componente registrado exitosamente!\n");
}

void modificar_componente() {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para modificar.\n");
        return;
    }
    
    int codigo, encontrado = 0, indice;
    
    printf("\nIngrese el codigo del componente a modificar: ");
    scanf("%d", &codigo);
    
    // Buscar el componente por su código
    for (int i = 0; i < num_componentes; i++) {
        if (codigos[i] == codigo) {
            encontrado = 1;
            indice = i;
            break;
        }
    }
    
    if (!encontrado) {
        printf("No se encontro un componente con ese codigo.\n");
        return;
    }
    
    printf("\nModificando componente %d: %s\n", codigos[indice], nombres[indice]);
    
    printf("Nuevo nombre (actual: %s): ", nombres[indice]);
    scanf(" %[^\n]", nombres[indice]);
    
    printf("Nuevo precio de costo (actual: %.2f): ", precios_costo[indice]);
    scanf("%f", &precios_costo[indice]);
    
    printf("Nueva cantidad en existencia (actual: %d): ", cantidades_existencia[indice]);
    scanf("%d", &cantidades_existencia[indice]);
    
    if (tipos[indice]) {
        printf("Nueva empresa productora (actual: %s): ", empresas_paises[indice]);
        scanf(" %[^\n]", empresas_paises[indice]);
    } else {
        printf("Nuevo pais de procedencia (actual: %s): ", empresas_paises[indice]);
        scanf(" %[^\n]", empresas_paises[indice]);
        
        printf("Nuevo precio en dolares (actual: %.2f): ", precios_usd[indice]);
        scanf("%f", &precios_usd[indice]);
    }
    
    printf("Componente modificado exitosamente!\n");
}

void calcular_precio_venta() {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para calcular precios.\n");
        return;
    }
    
    printf("\nCalculo de precios de venta:\n");
    printf("============================\n");
    
    for (int i = 0; i < num_componentes; i++) {
        float precio_venta;
        
        if (tipos[i]) {
            precio_venta = precios_costo[i] * 1.05;
            printf("Componente nacional: %s\n", nombres[i]);
            printf("Empresa: %s\n", empresas_paises[i]);
        } else {
            precio_venta = precios_costo[i] * 1.05 + (27 * precios_usd[i]);
            printf("Componente importado: %s\n", nombres[i]);
            printf("Pais: %s\n", empresas_paises[i]);
        }
        
        printf("Precio de costo: %.2f\n", precios_costo[i]);
        printf("Precio de venta: %.2f\n\n", precio_venta);
    }
}

void listar_nacionales_precio_superior() {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para listar.\n");
        return;
    }
    
    float precio_minimo;
    int encontrados = 0;
    
    printf("\nIngrese el precio minimo para filtrar: ");
    scanf("%f", &precio_minimo);
    
    printf("\nProductos nacionales con precio superior a %.2f:\n", precio_minimo);
    printf("===============================================\n");
    
    for (int i = 0; i < num_componentes; i++) {
        if (tipos[i] && precios_costo[i] > precio_minimo) {
            printf("Codigo: %d\n", codigos[i]);
            printf("Nombre: %s\n", nombres[i]);
            printf("Precio: %.2f\n", precios_costo[i]);
            printf("Empresa: %s\n", empresas_paises[i]);
            printf("Cantidad: %d\n\n", cantidades_existencia[i]);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron productos nacionales con precio superior a %.2f\n", precio_minimo);
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

void listar_importados_por_pais() {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para listar.\n");
        return;
    }
    
    char pais[MAX_LONGITUD];
    int encontrados = 0;
    
    printf("\nIngrese el pais de procedencia para filtrar: ");
    scanf(" %[^\n]", pais);
    
    printf("\nProductos importados de %s:\n", pais);
    printf("==============================\n");
    
    for (int i = 0; i < num_componentes; i++) {
        if (!tipos[i] && strcmp(empresas_paises[i], pais) == 0) {
            printf("Codigo: %d\n", codigos[i]);
            printf("Nombre: %s\n", nombres[i]);
            printf("Precio: %.2f\n", precios_costo[i]);
            printf("Precio en USD: %.2f\n", precios_usd[i]);
            printf("Cantidad: %d\n\n", cantidades_existencia[i]);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron productos importados de %s\n", pais);
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

void detectar_stock_bajo() {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para verificar.\n");
        return;
    }
    
    int nivel_minimo, encontrados = 0;
    
    printf("\nIngrese el nivel minimo de stock para la alerta: ");
    scanf("%d", &nivel_minimo);
    
    printf("\nProductos con stock por debajo de %d:\n", nivel_minimo);
    printf("======================================\n");
    
    for (int i = 0; i < num_componentes; i++) {
        if (cantidades_existencia[i] < nivel_minimo) {
            printf("Codigo: %d\n", codigos[i]);
            printf("Nombre: %s\n", nombres[i]);
            printf("Tipo: %s\n", tipos[i] ? "Nacional" : "Importado");
            printf("Cantidad actual: %d\n", cantidades_existencia[i]);
            
            if (tipos[i]) {
                printf("Empresa: %s\n\n", empresas_paises[i]);
            } else {
                printf("Pais: %s\n\n", empresas_paises[i]);
            }
            
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No hay productos con stock por debajo de %d\n", nivel_minimo);
    } else {
        printf("Total de productos con stock bajo: %d\n", encontrados);
    }
}