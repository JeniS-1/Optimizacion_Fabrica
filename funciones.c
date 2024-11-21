#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opcion;
    printf("\n MENU \n");
    printf("1. Ingresar productos\n");
    printf("2. Ver inventario\n");
    printf("3. Buscar producto (editar/eliminar)\n");
    printf("4. Hacer pedido\n");
    printf("5. Salir\n");
    printf("Elija una opcion: ");
    scanf("%d", &opcion);
    getchar();
    return opcion;
}

void ingresarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], char nombres_recursos[NumProduct][MaxResources][30], int *num_ingresados) {
    
    if (*num_ingresados >= NumProduct) {
        printf("\nNo puede ingresar mas productos. Inventario lleno.\n");
        return;
    }

    printf("\nIngrese el nombre del producto: ");
    fgets(nombres_productos[*num_ingresados], 30, stdin);
    nombres_productos[*num_ingresados][strcspn(nombres_productos[*num_ingresados], "\n")] = '\0';

    printf("Ingrese el tiempo necesario para fabricar una unidad (en horas): ");
    scanf("%f", &tiempos_por_unidad[*num_ingresados]);
    getchar();

    printf("¿Cuantos recursos utiliza este producto? (Maximo %d): ", MaxResources);
    scanf("%d", &num_recursos[*num_ingresados]);
    getchar();

    for (int i = 0; i < num_recursos[*num_ingresados]; i++) {
        printf("\nRecurso %d:\n", i + 1);
        printf("Nombre del recurso: ");
        fgets(nombres_recursos[*num_ingresados][i], 30, stdin);
        nombres_recursos[*num_ingresados][i][strcspn(nombres_recursos[*num_ingresados][i], "\n")] = '\0';

        printf("Cantidad necesaria por unidad: ");
        scanf("%f", &recursos[*num_ingresados][i]);
        getchar();
    }

    (*num_ingresados)++;
}

void mostrarInventario(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], char nombres_recursos[NumProduct][MaxResources][30], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados) {

    if (num_ingresados == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    printf("\n INVENTARIO \n");
    for (int i = 0; i < num_ingresados; i++) {
        printf("\nProducto %d: %s\n", i + 1, nombres_productos[i]);
        printf("Tiempo por unidad: %.2f horas\n", tiempos_por_unidad[i]);
        printf("Cantidad demandada: %d\n", cantidad_demandada[i]);
        printf("Cantidad producida: %d\n", cantidad_producida[i]);
        printf("Recursos necesarios:\n");
        for (int j = 0; j < num_recursos[i]; j++) {
            printf("- %s: %.2f por unidad\n", nombres_recursos[i][j], recursos[i][j]);
        }
    }
}

void buscarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], char nombres_recursos[NumProduct][MaxResources][30], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int *num_ingresados) {
    
    char nombre_buscado[30];
    printf("\nIngrese el nombre del producto a buscar: ");
    fgets(nombre_buscado, 30, stdin);
    nombre_buscado[strcspn(nombre_buscado, "\n")] = '\0';

    for (int i = 0; i < *num_ingresados; i++) {
        if (strcmp(nombres_productos[i], nombre_buscado) == 0) {
            printf("\nProducto encontrado: %s\n", nombres_productos[i]);
            printf("1. Editar\n2. Eliminar\nElija una opcion: ");
            int opcion;
            scanf("%d", &opcion);
            getchar();

            if (opcion == 1) {
                ingresarProducto(nombres_productos, tiempos_por_unidad, num_recursos, recursos, nombres_recursos, &i);
            } else if (opcion == 2) {
                for (int j = i; j < *num_ingresados - 1; j++) {
                    strcpy(nombres_productos[j], nombres_productos[j + 1]);
                    tiempos_por_unidad[j] = tiempos_por_unidad[j + 1];
                    num_recursos[j] = num_recursos[j + 1];
                    for (int k = 0; k < MaxResources; k++) {
                        recursos[j][k] = recursos[j + 1][k];
                        strcpy(nombres_recursos[j][k], nombres_recursos[j + 1][k]);
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

void hacerPedido(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], char nombres_recursos[NumProduct][MaxResources][30], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados) {
    
    char nombre_buscado[30];
    printf("\nIngrese el nombre del producto para realizar el pedido: ");
    fgets(nombre_buscado, 30, stdin);
    nombre_buscado[strcspn(nombre_buscado, "\n")] = '\0';

    for (int i = 0; i < num_ingresados; i++) {
        if (strcmp(nombres_productos[i], nombre_buscado) == 0) {
            int demanda;
            float tiempo_disponible, recursos_disponibles[MaxResources];

            printf("Ingrese la cantidad demandada: ");
            scanf("%d", &demanda);
            getchar();

            printf("Ingrese el tiempo disponible para cumplir la demanda (en horas): ");
            scanf("%f", &tiempo_disponible);
            getchar();

            for (int j = 0; j < num_recursos[i]; j++) {
                printf("Cantidad disponible de %s en la fabrica: ", nombres_recursos[i][j]);
                scanf("%f", &recursos_disponibles[j]);
                getchar();
            }

            int max_por_tiempo = tiempo_disponible / tiempos_por_unidad[i];
            int max_por_recursos = demanda;

            for (int j = 0; j < num_recursos[i]; j++) {
                int posible = recursos_disponibles[j] / recursos[i][j];
                if (posible < max_por_recursos) {
                    max_por_recursos = posible;
                }
            }

            int produccion_posible = (max_por_tiempo < max_por_recursos) ? max_por_tiempo : max_por_recursos;

            if (produccion_posible == 0) {
                if (max_por_tiempo == 0) {
                    printf("\nNo se puede producir ninguna unidad debido a la falta de tiempo.\n");
                } else {
                    printf("\nNo se puede producir ninguna unidad debido a la falta de recursos.\n");
                }
            } else if (produccion_posible < demanda) {
                if (max_por_tiempo < max_por_recursos) {
                    printf("\nNo es posible cumplir con la demanda completa debido al tiempo disponible.\n");
                } else {
                    printf("\nNo es posible cumplir con la demanda completa debido a la falta de recursos.\n");
                }
                printf("Se pueden producir %d unidades.\n", produccion_posible);
            } else {
                printf("\nEs posible cumplir con la demanda completa.\n");
            }

            cantidad_demandada[i] += demanda;
            cantidad_producida[i] += produccion_posible;

            return;
        }
    }
    printf("\nProducto no encontrado.\n");
}

