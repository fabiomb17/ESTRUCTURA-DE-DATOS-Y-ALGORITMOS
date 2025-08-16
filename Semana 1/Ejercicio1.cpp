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

// Constantes
#define MAX_COMPONENTES 100
#define MAX_LONGITUD 50

// Definicion de la estructura
typedef struct {
    int codigo;
    char nombre[MAX_LONGITUD];
    float precio_costo;
    int cantidad_existencia;
    int es_nacional; // 1 para nacional, 0 para importado
    union {
        char empresa_productora[MAX_LONGITUD]; // Para productos nacionales
        struct {
            char pais_procedencia[MAX_LONGITUD];
            float precio_usd; // Precio en dolares para importados
        } datos_importado;
    } info_adicional;
} Componente;

// Prototipos
void menu_principal(Componente inventario[], int *num_componentes);
void registrar_componente(Componente inventario[], int *num_componentes);
void modificar_componente(Componente inventario[], int num_componentes);
void calcular_precio_venta(Componente inventario[], int num_componentes);
void listar_nacionales_precio_superior(Componente inventario[], int num_componentes);
void listar_importados_por_pais(Componente inventario[], int num_componentes);
void detectar_stock_bajo(Componente inventario[], int num_componentes);

int main() {
    Componente inventario[MAX_COMPONENTES];
    int num_componentes = 0;
    
    printf("Sistema de Gestion de Almacen Grupo 12\n");
    printf("=======================================\n\n");
    
    menu_principal(inventario, &num_componentes);
    
    return 0;
}

// Funcion para mostrar el menu principal
void menu_principal(Componente inventario[], int *num_componentes) {
    int opcion;
    
    do {
        printf("\nMenu Principal:\n");
        printf("1. Registrar componente\n");
        printf("2. Modificar producto existente\n");
        printf("3. Calcular precio de venta\n");
        printf("4. Listar productos nacionales\n");
        printf("5. Listar productos importados por pais\n");
        printf("6. Productos con bajo stock\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                registrar_componente(inventario, num_componentes);
                break;
            case 2:
                modificar_componente(inventario, *num_componentes);
                break;
            case 3:
                calcular_precio_venta(inventario, *num_componentes);
                break;
            case 4:
                listar_nacionales_precio_superior(inventario, *num_componentes);
                break;
            case 5:
                listar_importados_por_pais(inventario, *num_componentes);
                break;
            case 6:
                detectar_stock_bajo(inventario, *num_componentes);
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while(opcion != 0);
}

// Funcion para registrar un nuevo componente en el inventario
void registrar_componente(Componente inventario[], int *num_componentes) {
    if (*num_componentes >= MAX_COMPONENTES) {
        printf("El inventario esta lleno. No se pueden agregar mas componentes.\n");
        return;
    }
    
    Componente nuevo;
    
    printf("\nRegistro de nuevo componente:\n");
    
    printf("Codigo: ");
    scanf("%d", &nuevo.codigo);
    
    printf("Nombre: ");
    scanf(" %[^\n]", nuevo.nombre); // Leer cadena con espacios
    
    printf("Precio de costo: ");
    scanf("%f", &nuevo.precio_costo);
    
    printf("Cantidad en existencia: ");
    scanf("%d", &nuevo.cantidad_existencia);
    
    printf("Es nacional (1) o importado (0)? ");
    scanf("%d", &nuevo.es_nacional);
    
    if (nuevo.es_nacional) {
        printf("Empresa productora: ");
        scanf(" %[^\n]", nuevo.info_adicional.empresa_productora);
    } else {
        printf("Pais de procedencia: ");
        scanf(" %[^\n]", nuevo.info_adicional.datos_importado.pais_procedencia);
        
        printf("Precio en dolares: ");
        scanf("%f", &nuevo.info_adicional.datos_importado.precio_usd);
    }
    
    inventario[*num_componentes] = nuevo;
    (*num_componentes)++;
    
    printf("Componente registrado exitosamente!\n");
}

// Función para modificar un componente existente
void modificar_componente(Componente inventario[], int num_componentes) {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para modificar.\n");
        return;
    }
    
    int codigo, encontrado = 0, indice;
    
    printf("\nIngrese el codigo del componente a modificar: ");
    scanf("%d", &codigo);
    
    // Buscar el componente por su código
    for (int i = 0; i < num_componentes; i++) {
        if (inventario[i].codigo == codigo) {
            encontrado = 1;
            indice = i;
            break;
        }
    }
    
    if (!encontrado) {
        printf("No se encontro un componente con ese codigo.\n");
        return;
    }
    
    printf("\nModificando componente %d: %s\n", inventario[indice].codigo, inventario[indice].nombre);
    
    printf("Nuevo nombre (actual: %s): ", inventario[indice].nombre);
    scanf(" %[^\n]", inventario[indice].nombre);
    
    printf("Nuevo precio de costo (actual: %.2f): ", inventario[indice].precio_costo);
    scanf("%f", &inventario[indice].precio_costo);
    
    printf("Nueva cantidad en existencia (actual: %d): ", inventario[indice].cantidad_existencia);
    scanf("%d", &inventario[indice].cantidad_existencia);
    
    if (inventario[indice].es_nacional) {
        printf("Nueva empresa productora (actual: %s): ", inventario[indice].info_adicional.empresa_productora);
        scanf(" %[^\n]", inventario[indice].info_adicional.empresa_productora);
    } else {
        printf("Nuevo pais de procedencia (actual: %s): ", inventario[indice].info_adicional.datos_importado.pais_procedencia);
        scanf(" %[^\n]", inventario[indice].info_adicional.datos_importado.pais_procedencia);
        
        printf("Nuevo precio en dolares (actual: %.2f): ", inventario[indice].info_adicional.datos_importado.precio_usd);
        scanf("%f", &inventario[indice].info_adicional.datos_importado.precio_usd);
    }
    
    printf("Componente modificado exitosamente!\n");
}

// Funcion para calcular el precio de venta de los componentes
void calcular_precio_venta(Componente inventario[], int num_componentes) {
    if (num_componentes == 0) {
        printf("No hay componentes registrados para calcular precios.\n");
        return;
    }
    
    printf("\nCalculo de precios de venta:\n");
    printf("============================\n");
    
    for (int i = 0; i < num_componentes; i++) {
        float precio_venta;
        
        if (inventario[i].es_nacional) {
            // Nacional es igual al precio de costo + 5%
            precio_venta = inventario[i].precio_costo * 1.05;
            printf("Componente nacional: %s\n", inventario[i].nombre);
            printf("Empresa: %s\n", inventario[i].info_adicional.empresa_productora);
        } else {
            // Importado es igual al precio de costo + 5% + (27 × precio en dolares)
            precio_venta = inventario[i].precio_costo * 1.05 + (27 * inventario[i].info_adicional.datos_importado.precio_usd);
            printf("Componente importado: %s\n", inventario[i].nombre);
            printf("Pais: %s\n", inventario[i].info_adicional.datos_importado.pais_procedencia);
        }
        
        printf("Precio de costo: %.2f\n", inventario[i].precio_costo);
        printf("Precio de venta: %.2f\n\n", precio_venta);
    }
}

// Funcion para listar productos nacionales con precio superior a un valor dado
void listar_nacionales_precio_superior(Componente inventario[], int num_componentes) {
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
        if (inventario[i].es_nacional && inventario[i].precio_costo > precio_minimo) {
            printf("Codigo: %d\n", inventario[i].codigo);
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Precio: %.2f\n", inventario[i].precio_costo);
            printf("Empresa: %s\n", inventario[i].info_adicional.empresa_productora);
            printf("Cantidad: %d\n\n", inventario[i].cantidad_existencia);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron productos nacionales con precio superior a %.2f\n", precio_minimo);
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

// Funcion para listar productos importados por pais de procedencia
void listar_importados_por_pais(Componente inventario[], int num_componentes) {
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
        if (!inventario[i].es_nacional && 
            strcmp(inventario[i].info_adicional.datos_importado.pais_procedencia, pais) == 0) {
            printf("Codigo: %d\n", inventario[i].codigo);
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Precio: %.2f\n", inventario[i].precio_costo);
            printf("Precio en USD: %.2f\n", inventario[i].info_adicional.datos_importado.precio_usd);
            printf("Cantidad: %d\n\n", inventario[i].cantidad_existencia);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron productos importados de %s\n", pais);
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

// Funcin para detectar productos con stock por debajo del nivel minimo
void detectar_stock_bajo(Componente inventario[], int num_componentes) {
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
        if (inventario[i].cantidad_existencia < nivel_minimo) {
            printf("Codigo: %d\n", inventario[i].codigo);
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Tipo: %s\n", inventario[i].es_nacional ? "Nacional" : "Importado");
            printf("Cantidad actual: %d\n", inventario[i].cantidad_existencia);
            
            if (inventario[i].es_nacional) {
                printf("Empresa: %s\n\n", inventario[i].info_adicional.empresa_productora);
            } else {
                printf("Pais: %s\n\n", inventario[i].info_adicional.datos_importado.pais_procedencia);
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