
#define NumProduct 5
#define MaxResources 3

int menu();
void ingresarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int num_ingresados, char nom_recurso[NumProduct][20]);
void mostrarInventario(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados);
void buscarProducto(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int *num_ingresados);
void hacerPedido(char nombres_productos[NumProduct][30], float tiempos_por_unidad[NumProduct], int num_recursos[NumProduct], float recursos[NumProduct][MaxResources], int cantidad_demandada[NumProduct], int cantidad_producida[NumProduct], int num_ingresados);

