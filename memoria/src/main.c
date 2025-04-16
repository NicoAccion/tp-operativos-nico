#include <utils/hello.h>

int main(int argc, char* argv[]) {
    saludar("memoria");
    return 0;
}

#include "server.h"

int main(void) {
	logger = log_create("log.log", "Memoria", 1, LOG_LEVEL_DEBUG);

	int memoria_fd = iniciar_memoria();
	log_info(logger, "Memoria lista para recibir");
	int kernel_fd = esperar_kernel(memoria_fd);

	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case -1:
			log_error(logger, "el kernel se desconecto. Terminando memoria");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

