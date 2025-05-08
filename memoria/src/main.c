#include <utils/hello.h>
#include <utils/configs.h>
#include "memoria-conexiones.h"

int main(int argc, char* argv[]) {
    int puerto_escucha;
    int tam_memoria;
    int tam_pagina;
    int entradas_por_tabla;
    int cantidad_niveles;
    int retardo_memoria;
    char* path_swapfile;
    int retardo_swap;
    char* log_level;
    char* dump_path;
    char* path_instrucciones;

    t_config* config_de_memoria;

    saludar("memoria");

    //Creo un nuevo config
    config_de_memoria = iniciar_config("memoria.config");

    //Dejo los valores leidos por el config en las variables
    puerto_escucha = config_get_int_value(config_de_memoria, "PUERTO_ESCUCHA");
    tam_memoria = config_get_int_value(config_de_memoria, "TAM_MEMORIA");
    tam_pagina = config_get_int_value(config_de_memoria, "TAM_PAGINA");
    entradas_por_tabla = config_get_int_value(config_de_memoria, "ENTRADAS_POR_TABLA");
    cantidad_niveles = config_get_int_value(config_de_memoria, "CANTIDAD_NIVELES");
    retardo_memoria = config_get_int_value(config_de_memoria, "RETARDO_MEMORIA");
    path_swapfile = config_get_string_value(config_de_memoria, "PATH_SWAPFILE");
    retardo_swap = config_get_int_value(config_de_memoria, "RETARDO_SWAP");
    log_level = config_get_string_value(config_de_memoria, "LOG_LEVEL");
    dump_path = config_get_string_value(config_de_memoria, "DUMP_PATH");
    path_instrucciones = config_get_string_value(config_de_memoria, "PATH_INSTRUCCIONES");

    //memoria_conectar_a_kernel();
    memoria_conectar_a_cpu();

    //Destruyo el config
    config_destroy(config_de_memoria);
    return 0;
}
