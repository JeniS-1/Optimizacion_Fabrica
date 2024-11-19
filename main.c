#include <stdio.h>
#include "funciones.h"

int main() {
    char nombres_productos[NumProduct][30] = {""};
    float tiempos_por_unidad[NumProduct] = {0};
    int num_recursos[NumProduct] = {0};
    float recursos[NumProduct][MaxResources] = {{0}};
    int cantidad_demandada[NumProduct] = {0};
    int cantidad_producida[NumProduct] = {0};
    int num_ingresados = 0;
    char nom_producto[NumProduct][20];

    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                ingresarProducto(nombres_productos, tiempos_por_unidad, num_recursos, recursos, num_ingresados, nom_producto);
                if (num_ingresados < NumProduct) {
                    num_ingresados++;
                }
                break;
            case 2:
                mostrarInventario(nombres_productos, tiempos_por_unidad, num_recursos, recursos, cantidad_demandada, cantidad_producida, num_ingresados);
                break;
            case 3:
                buscarProducto(nombres_productos, tiempos_por_unidad, num_recursos, recursos, cantidad_demandada, cantidad_producida, &num_ingresados);
                break;
            case 4:
                hacerPedido(nombres_productos, tiempos_por_unidad, num_recursos, recursos, cantidad_demandada, cantidad_producida, num_ingresados);
                break;
            case 5:
                printf("\n¿Desea ingresar más productos? (1: Sí, 0: No): ");
                int continuar;
                scanf("%d", &continuar);
                getchar();
                if (!continuar) {
                    printf("\nSaliendo del programa.\n");
                    return 0;
                }
                break;
            default:
                printf("\nOpción inválida.\n");
        }
    } while (1);

    return 0;
}

