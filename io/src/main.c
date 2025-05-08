#include <utils/hello.h>
#include <utils/configs.h>
#include "io-conexiones.h"

int main(int argc, char* argv[]) {
    char* ip_kernel;
    int puerto_kernel;
    char* log_level;

    t_config* config_de_io;

    saludar("io");

    //Creo un nuevo config
    config_de_io = iniciar_config("io.config");

    //Dejo los valores leidos por el config en las variables
    ip_kernel = config_get_string_value(config_de_io, "IP_KERNEL");
    puerto_kernel = config_get_int_value(config_de_io, "PUERTO_KERNEL");
    log_level = config_get_string_value(config_de_io, "LOG_LEVEL");

    io_conectar_a_kernel();

    //Destruyo el config
    config_destroy(config_de_io);

    return 0;
}
