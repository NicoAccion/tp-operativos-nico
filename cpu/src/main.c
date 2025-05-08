#include <utils/configs.h>
#include "cpu.h"

int main(int argc, char* argv[]) {
   char* ip_memoria;
   int puerto_memoria;
   char* ip_kernel;
   int puerto_kernel_dispatch;
   int puerto_kernel_interrupt;
   int entradas_tlb;
   char* reemplazo_tlb;
   int entradas_cache;
   char* reemplazo_cache;
   int retardo_cache;
   char* log_level;

   t_config* config_de_cpu;

   //Creo un nuevo config
   config_de_cpu = iniciar_config("cpu.config");

   //Dejo los valores leidos por el config en las variables
   ip_memoria = config_get_string_value(config_de_cpu, "IP_MEMORIA");
   puerto_memoria = config_get_int_value(config_de_cpu, "PUERTO_MEMORIA");
   ip_kernel = config_get_string_value(config_de_cpu, "IP_KERNEL");
   puerto_kernel_dispatch = config_get_int_value(config_de_cpu, "PUERTO_KERNEL_DISPATCH");
   puerto_kernel_interrupt = config_get_int_value(config_de_cpu, "PUERTO_KERNEL_INTERRUPT");
   entradas_tlb = config_get_int_value(config_de_cpu, "ENTRADAS_TLB");
   reemplazo_tlb = config_get_string_value(config_de_cpu, "REEMPLAZO_TLB");
   entradas_cache = config_get_int_value(config_de_cpu, "ENTRADAS_CACHE");
   reemplazo_cache = config_get_string_value(config_de_cpu, "REEMPLAZO_CACHE");
   retardo_cache = config_get_int_value(config_de_cpu, "RETARDO_CACHE");
   log_level = config_get_string_value(config_de_cpu, "LOG_LEVEL");

   cpu_conectar_a_kernel();

   //Destruyo el config
   config_destroy(config_de_cpu);
}
