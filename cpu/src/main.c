#include <utils/hello.h>
#include <arpa/inet.h>
#include <unistd.h>

#define CONFIG_PATH "cpu.config"
#define MENSAJE_MAX_LEN 100

int crear_conexion(char* ip, int puerto);
void enviar_mensaje(int socket, char* mensaje);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <id_cpu>\n", argv[0]);
        return 1;
    }

    char* id_cpu = argv[1];
    t_log* logger = log_create("cpu.log", "CPU", 1, LOG_LEVEL_INFO);
    t_config* config = config_create(CONFIG_PATH);

    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    int puerto_dispatch = config_get_int_value(config, "PUERTO_KERNEL_DISPATCH");

    log_info(logger, "CPU %s conectando a Kernel en %s:%d...", id_cpu, ip_kernel, puerto_dispatch);

    int socket_kernel = crear_conexion(ip_kernel, puerto_dispatch);
    if (socket_kernel < 0) {
        log_error(logger, "Error al conectar al Kernel");
        return 2;
    }

    // Enviar saludo
    char mensaje[MENSAJE_MAX_LEN];
    snprintf(mensaje, MENSAJE_MAX_LEN, "CPU-%s", id_cpu);
    enviar_mensaje(socket_kernel, mensaje);

    log_info(logger, "Mensaje enviado a kernel: %s", mensaje);

    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    int puerto_memoria = config_get_int_value(config, "PUERTO_MEMORIA");

    log_info(logger, "CPU %s conectando a Memoria en %s:%d...", id_cpu, ip_memoria, puerto_memoria);

    int socket_memoria = crear_conexion(ip_memoria, puerto_memoria);
    if (socket_memoria == -1) {
        log_error(logger, "Error al conectar a Memoria");
    } else {
        char mensaje_memoria[100];
        snprintf(mensaje_memoria, sizeof(mensaje_memoria), "CPU-%s", id_cpu);
        enviar_mensaje(socket_memoria, mensaje_memoria);
        log_info(logger, "Mensaje enviado a Memoria: %s", mensaje_memoria);
        sleep(1); // para asegurar que el mensaje llegue antes de cerrar
        close(socket_memoria);
    }

    close(socket_kernel);
    config_destroy(config);
    log_destroy(logger);
    return 0;
}

int crear_conexion(char* ip, int puerto) {
    struct sockaddr_in direccion;
    int socket_cliente = socket(AF_INET, SOCK_STREAM, 0);

    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    direccion.sin_addr.s_addr = inet_addr(ip);

    if (connect(socket_cliente, (void*)&direccion, sizeof(direccion)) != 0) {
        return -1;
    }

    return socket_cliente;
}

void enviar_mensaje(int socket, char* mensaje) {
    send(socket, mensaje, strlen(mensaje) + 1, 0); // +1 para incluir el '\0'
}