#include <utils/hello.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define CONFIG_PATH "memoria.config"
#define MAX_CONEXIONES 10

t_log* logger;
t_config* config;

void* manejar_cliente(void* socket_cliente_ptr) {
    // Recuperar el socket que vino como argumento (y liberar la memoria del puntero)
    int socket_cliente = *(int*)socket_cliente_ptr;
    free(socket_cliente_ptr);

    // Buffer donde se guardará el mensaje recibido
    char buffer[100] = {0};

    // Recibir mensaje del cliente (por ejemplo: "KERNEL", "CPU-1", etc.)
    int bytes = recv(socket_cliente, buffer, sizeof(buffer), 0);

    // Si se recibió algo correctamente
    if (bytes > 0) {
        // Mostrar saludo por consola con la función saludar() (de utils)
        saludar(buffer);

        // También lo logueamos con commons
		printf("LLEGA");
        log_info(logger, "Recibido nuevo: %s", buffer);
    } else {
        log_warning(logger, "Cliente desconectado sin enviar mensaje.");
    }

    // Cerrar conexión con el cliente
    close(socket_cliente);
    return NULL;
}


int main() {
    logger = log_create("memoria.log", "MEMORIA", 1, LOG_LEVEL_INFO);
    config = config_create(CONFIG_PATH);

    if (!config) {
        log_error(logger, "No se pudo cargar memoria.config");
        return 1;
    }
    int puerto = config_get_int_value(config, "PUERTO_ESCUCHA");

    struct sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    direccion.sin_addr.s_addr = INADDR_ANY;

    int socket_servidor = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(socket_servidor, (void*)&direccion, sizeof(direccion)) < 0) {
    log_error(logger, "Fallo bind()");
    return EXIT_FAILURE;
	}
    if (listen(socket_servidor, 10) < 0) {
    log_error(logger, "Fallo listen()");
    return EXIT_FAILURE;
	}

    log_info(logger, "Servidor Memoria escuchando en puerto %d", puerto);
	
	printf("LLEGA2\n");

	while (1) {
		printf("LLEGA3\n");
    	struct sockaddr_in cliente;
    	socklen_t tam = sizeof(cliente);
    	int* socket_cliente = malloc(sizeof(int));
		printf("LLEGA4\n");
    	*socket_cliente = accept(socket_servidor, (void*)&cliente, &tam);
		printf("LLEGA5\n");

    	pthread_t hilo_cliente;
    	pthread_create(&hilo_cliente, NULL, manejar_cliente, socket_cliente);
    	pthread_detach(hilo_cliente);
	}


    config_destroy(config);
    log_destroy(logger);
    return 0;
}
