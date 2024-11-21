#include <stdio.h>
#include "funciones.h"

int main() {
    char nombres_productos[NumProduct][30] = {0};
    float tiempos_por_unidad[NumProduct] = {0};
    int num_recursos[NumProduct] = {0};
    float recursos[NumProduct][MaxResources] = {0};
    char nombres_recursos[NumProduct][MaxResources][30] = {0};
    int cantidad_demandada[NumProduct] = {0};
    int cantidad_producida[NumProduct] = {0};
    int num_ingresados = 0;
    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                ingresarProducto(nombres_productos, tiempos_por_unidad, num_recursos, recursos, nombres_recursos, &num_ingresados);
                break;
            case 2:
                mostrarInventario(nombres_productos, tiempos_por_unidad, num_recursos, recursos, nombres_recursos, cantidad_demandada, cantidad_producida, num_ingresados);
                break;
            case 3:
                buscarProducto(nombres_productos, tiempos_por_unidad, num_recursos, recursos, nombres_recursos, cantidad_demandada, cantidad_producida, &num_ingresados);
                break;
            case 4:
                hacerPedido(nombres_productos, tiempos_por_unidad, num_recursos, recursos, nombres_recursos, cantidad_demandada, cantidad_producida, num_ingresados);
                break;
            case 5:
                printf("\nSaliendo del programa.\n");
                return 0;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
    } while (1);

    return 0;
}
