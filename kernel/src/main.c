#include <utils/hello.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define CONFIG_PATH "kernel.config"

t_log* logger;
t_config* config;

void* escuchar_conexiones_cpu_io(void* arg) {
    int puerto = *(int*)arg;
    free(arg);

    int socket_servidor = iniciar_servidor("127.0.0.1", puerto);
    log_info(logger, "Servidor de Kernel escuchando en puerto %d", puerto);

    struct sockaddr_in cliente;
    socklen_t tam = sizeof(struct sockaddr_in);

    while (1) {
        int socket_cliente = accept(socket_servidor, (void*)&cliente, &tam);
        char buffer[100] = {0};
        recv(socket_cliente, buffer, sizeof(buffer), 0);
        saludar(buffer); // Muestra "Hola desde CPU-1!!" 
        log_info(logger, "Recibido nuevo: %s", buffer);
        close(socket_cliente);
    }
    return NULL;
}

int main() {
    logger = log_create("kernel.log", "KERNEL", 1, LOG_LEVEL_INFO);
    config = config_create(CONFIG_PATH);

    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    int puerto_memoria = config_get_int_value(config, "PUERTO_MEMORIA");

    log_info(logger, "Conectando a Memoria...");
    int socket_memoria = crear_conexion(ip_memoria, puerto_memoria);
    log_info(logger, "Resultado de crear_conexion(): %d", socket_memoria);

    if (socket_memoria == -1) {
        log_error(logger, "Error al conectar a Memoria");
        return EXIT_FAILURE;
    }
    enviar_mensaje(socket_memoria, "KERNEL");
    sleep(1);
    log_info(logger, "Mensaje enviado a Memoria");

    
    int* puerto_dispatch = malloc(sizeof(int));
    *puerto_dispatch = config_get_int_value(config, "PUERTO_ESCUCHA_DISPATCH");

    pthread_t hilo_escucha;
    pthread_create(&hilo_escucha, NULL, escuchar_conexiones_cpu_io, puerto_dispatch);
    pthread_detach(hilo_escucha);

    pause();
    return 0;
}
