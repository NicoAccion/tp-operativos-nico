#include <utils/hello.h>
#include <string.h>
#include <unistd.h>

#define CONFIG_PATH "io.config"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <nombre_dispositivo>\n", argv[0]);
        return 1;
    }

    char* nombre_io = argv[1];
    t_log* logger = log_create("io.log", "IO", 1, LOG_LEVEL_INFO);
    t_config* config = config_create(CONFIG_PATH);

    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    int puerto_kernel = config_get_int_value(config, "PUERTO_KERNEL");

    log_info(logger, "Dispositivo IO '%s' conectando al Kernel (%s:%d)...", nombre_io, ip_kernel, puerto_kernel);

    int socket_kernel = crear_conexion(ip_kernel, puerto_kernel);
    if (socket_kernel == -1) {
        log_error(logger, "No se pudo conectar al Kernel");
        return 2;
    }

    // Formatear el mensaje como "IO-Disco", "IO-Teclado", etc.
    char mensaje[100];
    snprintf(mensaje, sizeof(mensaje), "IO-%s", nombre_io);
    enviar_mensaje(socket_kernel, mensaje);

    log_info(logger, "Mensaje enviado al Kernel: %s", mensaje);

    close(socket_kernel);
    config_destroy(config);
    log_destroy(logger);
    return 0;
}
