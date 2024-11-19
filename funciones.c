#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opcion;
    printf("\n1. Ingresar productos\n");
    printf("2. Ver inventario\n");
    printf("3. Buscar producto (editar/eliminar)\n");
    printf("4. Hacer pedido\n");
    printf("5. Salir\n");
    printf("Elija una opción: ");
    scanf("%d", &opcion);
    getchar();
    return opcion;
}

void ingresarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int num_ingresados, char nom_recurso[NumProduct][20]) {
    if (num_ingresados >= NumProduct) {
        printf("\nEl inventario está lleno. No se pueden agregar más productos.\n");
        return;
    }

    printf("\nIngrese el nombre del producto: ");
    fgets(nombres_productos[num_ingresados], 30, stdin);
    nombres_productos[num_ingresados][strcspn(nombres_productos[num_ingresados], "\n")] = '\0';

    printf("Ingrese el tiempo necesario para producir una unidad (horas): ");
    scanf("%f", &tiempos_por_unidad[num_ingresados]);
    getchar();

    printf("¿Cuántos recursos utiliza este producto?");
    scanf("%d", &num_recursos[num_ingresados]);
    getchar();

    for (int i = 0; i < num_recursos[num_ingresados]; i++) {
        printf("Ingrese el nombre del recurso: ");
        fgets (nom_recurso[i], 20, stdin);
        nom_recurso[i][strlen(nom_recurso[i]) - 1] = '\0';
        printf("Ingrese la cantidad del %s %d: ",nom_recurso[i], i + 1);
        scanf("%f", &recursos[num_ingresados][i]);
        getchar();
    }
}

void mostrarInventario(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados) {
    if (num_ingresados == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    printf("\nInventario:\n");
    for (int i = 0; i < num_ingresados; i++) {
        printf("\nProducto %d: %s\n", i + 1, nombres_productos[i]);
        printf("Tiempo por unidad: %.2f horas\n", tiempos_por_unidad[i]);
        printf("Cantidad demandada: %d\n", cantidad_demandada[i]);
        printf("Cantidad producida: %d\n", cantidad_producida[i]);
        printf("Recursos necesarios:\n");
        for (int j = 0; j < num_recursos[i]; j++) {
            printf("- Recurso %d: %.2f unidades\n", j + 1, recursos[i][j]);
        }
    }
}

void buscarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int *num_ingresados) {
    char nombre_buscado[30];
    printf("\nIngrese el nombre del producto a buscar: ");
    fgets(nombre_buscado, 30, stdin);
    nombre_buscado[strcspn(nombre_buscado, "\n")] = '\0';

    for (int i = 0; i < *num_ingresados; i++) {
        if (strcmp(nombres_productos[i], nombre_buscado) == 0) {
            printf("\nProducto encontrado: %s\n", nombres_productos[i]);
            printf("1. Editar\n2. Eliminar\nElija una opción: ");
            int opcion;
            scanf("%d", &opcion);
            getchar();

            if (opcion == 1) {
                printf("\nEditar nombre del producto: ");
                fgets(nombres_productos[i], 30, stdin);
                nombres_productos[i][strcspn(nombres_productos[i], "\n")] = '\0';

                printf("Editar tiempo por unidad (horas): ");
                scanf("%f", &tiempos_por_unidad[i]);
                getchar();

                printf("Editar número de recursos: ");
                scanf("%d", &num_recursos[i]);
                getchar();

                for (int j = 0; j < num_recursos[i]; j++) {
                    printf("Editar cantidad del recurso %d: ", j + 1);
                    scanf("%f", &recursos[i][j]);
                    getchar();
                }
            } else if (opcion == 2) {
                for (int j = i; j < *num_ingresados - 1; j++) {
                    strcpy(nombres_productos[j], nombres_productos[j + 1]);
                    tiempos_por_unidad[j] = tiempos_por_unidad[j + 1];
                    num_recursos[j] = num_recursos[j + 1];
                    for (int k = 0; k < MaxResources; k++) {
                        recursos[j][k] = recursos[j + 1][k];
                    }
                    cantidad_demandada[j] = cantidad_demandada[j + 1];
                    cantidad_producida[j] = cantidad_producida[j + 1];
                }
                (*num_ingresados)--;
                printf("\nProducto eliminado.\n");
            }
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

void hacerPedido(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados) {
    char nombre_buscado[30];
    printf("\nIngrese el nombre del producto para realizar el pedido: ");
    fgets(nombre_buscado, 30, stdin);
    nombre_buscado[strcspn(nombre_buscado, "\n")] = '\0';

    for (int i = 0; i < num_ingresados; i++) {
        if (strcmp(nombres_productos[i], nombre_buscado) == 0) {
            int cantidad_solicitada;
            float tiempo_disponible;

            printf("Ingrese la cantidad solicitada: ");
            scanf("%d", &cantidad_solicitada);
            getchar();

            printf("Ingrese el tiempo disponible (horas): ");
            scanf("%f", &tiempo_disponible);
            getchar();

            int producible_por_tiempo = tiempo_disponible / tiempos_por_unidad[i];
            int producible_por_recursos = cantidad_solicitada;

            for (int j = 0; j < num_recursos[i]; j++) {
                float disponible;
                printf("Ingrese la cantidad disponible del recurso %d: ", j + 1);
                scanf("%f", &disponible);
                getchar();
                int posible_por_recurso = disponible / recursos[i][j];
                if (posible_por_recurso < producible_por_recursos) {
                    producible_por_recursos = posible_por_recurso;
                }
            }

            int produccion_total = producible_por_tiempo < producible_por_recursos ? producible_por_tiempo : producible_por_recursos;

            if (produccion_total >= cantidad_solicitada) {
                printf("\nPedido completado. Se han producido %d unidades.\n", cantidad_solicitada);
                cantidad_producida[i] += cantidad_solicitada;
            } else {
                printf("\nNo se pudo cumplir completamente el pedido. Se han producido %d unidades.\n", produccion_total);
                cantidad_producida[i] += produccion_total;
            }

            cantidad_demandada[i] += cantidad_solicitada;
            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}
