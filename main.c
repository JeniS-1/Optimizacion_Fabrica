#include <stdio.h>
#include "funciones.h"

int main() {
    
    char productos[NumProduct][30];
    float tiempos[NumProduct], recursos[NumProduct];
    int cantidades_demandadas[NumProduct];
    float tiempos_disponibles[NumProduct], recursos_disponibles[NumProduct];
    int cantidades_producidas[NumProduct];
    int num_ingresados = 0, opcion, continuar;

    do {
        
        for (int i = 0; i < NumProduct; i++) {
            productos[i][0] = '\0';  
            tiempos[i] = 0;
            recursos[i] = 0;
            cantidades_demandadas[i] = 0;
            tiempos_disponibles[i] = 0;
            recursos_disponibles[i] = 0;
            cantidades_producidas[i] = 0;
        }
        num_ingresados = 0;

        printf("\nIngreso de Productos\n");
        for (int i = 0; i < NumProduct; i++) {
            printf("\nProducto %d de %d:\n", i + 1, NumProduct);
            ingresarProducto(productos[i], &tiempos[i], &recursos[i], &cantidades_demandadas[i],&tiempos_disponibles[i], &recursos_disponibles[i]);
            evaluarProduccionIndividual(productos[i], tiempos[i], recursos[i], cantidades_demandadas[i], tiempos_disponibles[i], recursos_disponibles[i], &cantidades_producidas[i]);
            num_ingresados++;
        }

        do {
            opcion = menu();
            switch (opcion) {
                case 1:
                    mostrarInventario(productos, tiempos, recursos, cantidades_producidas, num_ingresados);
                    break;
                case 2:
                    buscarProducto(productos, tiempos, recursos, cantidades_demandadas, tiempos_disponibles, recursos_disponibles, cantidades_producidas, &num_ingresados);
                    break;
                case 3: {
                    printf("\n¿Desea ingresar 5 productos nuevos? (1: Si, 0: No): ");
                    int reiniciar;
                    scanf("%d", &reiniciar);
                    getchar();
                    if (reiniciar) {
                        opcion = -1; 
                    } else {
                        printf("\nSaliendo del programa definitivamente.\n");
                        return 0;
                    }
                    break;
                }
                default:
                    printf("\nOpcion invalida.\n");
            }
        } while (opcion != -1); 
    } while (1);
}
