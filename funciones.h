#define NumProduct 5

int menu();
void ingresarProducto(char *producto, float *tiempo, float *recurso, int *cantidad_demandada,float *tiempo_disponible, float *recurso_disponible);
void evaluarProduccionIndividual(const char *producto, float tiempo, float recurso, int cantidad_demandada,float tiempo_disponible, float recurso_disponible, int *cantidad_producida);
void mostrarInventario(char productos[NumProduct][30], float *tiempos, float *recursos,int *cantidades_producidas, int num_ingresados);
void buscarProducto(char productos[NumProduct][30], float *tiempos, float *recursos,int *cantidades_demandadas, float *tiempos_disponibles,float *recursos_disponibles, int *cantidades_producidas, int *num_ingresados);

