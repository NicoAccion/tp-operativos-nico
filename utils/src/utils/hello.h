#ifndef UTILS_HELLO_H_
#define UTILS_HELLO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>

/**
* @brief Imprime un saludo por consola
* @param quien Módulo desde donde se llama a la función
* @return No devuelve nada
*/
void saludar(char* quien);
int crear_conexion(char* ip, int puerto);
void enviar_mensaje(int socket, char* mensaje);
int iniciar_servidor(char* ip, int puerto);

#endif
