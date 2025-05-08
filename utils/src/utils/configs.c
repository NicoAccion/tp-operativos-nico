#include "configs.h"

t_config* iniciar_config (char* path){

    t_config* nuevo_config = config_create(path);

	if (nuevo_config == NULL) {

		abort();
	}

	return nuevo_config;
}