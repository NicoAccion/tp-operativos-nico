#include <utils/hello.h>
#include <unistd.h>
#include <arpa/inet.h>

void saludar(char* quien) {
    printf("Hola desde %s!!\n", quien);
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

int iniciar_servidor(char* ip, int puerto) {
    int server_fd;
    struct sockaddr_in direccion;

    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    direccion.sin_addr.s_addr = inet_addr(ip);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(server_fd, (void*)&direccion, sizeof(direccion));
    listen(server_fd, 10);
    return server_fd;
}

void enviar_mensaje(int socket, char* mensaje) {
    send(socket, mensaje, strlen(mensaje) + 1, 0);
}