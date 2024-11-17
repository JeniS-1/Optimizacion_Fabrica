#include <stdio.h>
#include <string.h>
#include "funciones.h"


int menu() {
    int opcion;
    printf("\n1. Ver inventario\n");
    printf("2. Buscar producto (editar/eliminar)\n");
    printf("3. Salir\n");
    printf("Elija una opcion: ");
    scanf("%d", &opcion);
    getchar();
    return opcion;
}

void ingresarProducto(char *producto, float *tiempo, float *recurso, int *cantidad_demandada,
                      float *tiempo_disponible, float *recurso_disponible) {
    printf("\nIngrese el nombre del producto: ");
    fgets(producto, 30, stdin);
    producto[strcspn(producto, "\n")] = '\0';

    printf("Ingrese el tiempo necesario para fabricar una unidad: ");
    scanf("%f", tiempo);

    printf("Ingrese los recursos necesarios para fabricar una unidad: ");
    scanf("%f", recurso);

    printf("Ingrese la cantidad demandada del producto: ");
    scanf("%d", cantidad_demandada);

    printf("Ingrese el tiempo disponible para fabricar el producto: ");
    scanf("%f", tiempo_disponible);

    printf("Ingrese los recursos disponibles para fabricar el producto: ");
    scanf("%f", recurso_disponible);

    getchar(); 
}


void evaluarProduccionIndividual(const char *producto, float tiempo, float recurso, int cantidad_demandada,
                                 float tiempo_disponible, float recurso_disponible, int *cantidad_producida) {
    int max_por_tiempo = tiempo_disponible / tiempo;
    int max_por_recursos = recurso_disponible / recurso;
    *cantidad_producida = (max_por_tiempo < max_por_recursos) ? max_por_tiempo : max_por_recursos;

    printf("\nEvaluacion del producto: %s\n", producto);
    if (*cantidad_producida >= cantidad_demandada) {
        printf("Se cumple la demanda. Se produciran %d unidades.\n", cantidad_demandada);
        *cantidad_producida = cantidad_demandada;
    } else {
        printf("No se cumple la demanda. Solo se pueden producir %d unidades.\n", *cantidad_producida);
    }
}


void mostrarInventario(char productos[NumProduct][30], float *tiempos, float *recursos,
                       int *cantidades_producidas, int num_ingresados) {
    if (num_ingresados == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    printf("\n Inventario Disponible\n");
    for (int i = 0; i < num_ingresados; i++) {
        printf("\nProducto %d: %s\n", i + 1, productos[i]);
        printf("Cantidad producida: %d unidades\n", *(cantidades_producidas + i));
        printf("Tiempo utilizado por unidad: %.2f horas\n", *(tiempos + i));
        printf("Recursos utilizados por unidad: %.2f\n", *(recursos + i));
    }
}


void buscarProducto(char productos[NumProduct][30], float *tiempos, float *recursos,
                    int *cantidades_demandadas, float *tiempos_disponibles,
                    float *recursos_disponibles, int *cantidades_producidas, int *num_ingresados) {
    char producto_buscado[30];
    int encontrado = -1;

    printf("\nIngrese el nombre del producto a buscar: ");
    fgets(producto_buscado, 30, stdin);
    producto_buscado[strcspn(producto_buscado, "\n")] = '\0';

    
    for (int i = 0; i < *num_ingresados; i++) {
        if (strcmp(productos[i], producto_buscado) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("\nProducto encontrado: %s\n", productos[encontrado]);
        printf("Cantidad producida: %d unidades\n", *(cantidades_producidas + encontrado));
        printf("Tiempo utilizado por unidad: %.2f horas\n", *(tiempos + encontrado));
        printf("Recursos utilizados por unidad: %.2f\n", *(recursos + encontrado));

        printf("\n1. Editar\n2. Eliminar\nElija una opción: ");
        int opcion;
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            ingresarProducto(productos[encontrado], (tiempos + encontrado), (recursos + encontrado),
                 (cantidades_demandadas + encontrado), (tiempos_disponibles + encontrado),
                 (recursos_disponibles + encontrado));
            evaluarProduccionIndividual(productos[encontrado], *(tiempos + encontrado), *(recursos + encontrado),
              *(cantidades_demandadas + encontrado), *(tiempos_disponibles + encontrado),
              *(recursos_disponibles + encontrado), (cantidades_producidas + encontrado));
        } else if (opcion == 2) {
            for (int j = encontrado; j < *num_ingresados - 1; j++) {
                strcpy(productos[j], productos[j + 1]);
                *(tiempos + j) = *(tiempos + j + 1);
                *(recursos + j) = *(recursos + j + 1);
                *(cantidades_demandadas + j) = *(cantidades_demandadas + j + 1);
                *(tiempos_disponibles + j) = *(tiempos_disponibles + j + 1);
                *(recursos_disponibles + j) = *(recursos_disponibles + j + 1);
                *(cantidades_producidas + j) = *(cantidades_producidas + j + 1);
            }
            (*num_ingresados)--;
        }
    } else {
        printf("\nProducto no encontrado.\n");
    }
}

