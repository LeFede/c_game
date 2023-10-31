#include "sock-lib.h"
#include <stdint.h>

#define SYMBOL 0XAABBCCDD

int main() {
  int sock, sockdup;
  char msg[] = "hello world";
  int r;
  int8_t entero;

  sock = abrir_conexion(8000, 10, 1);
  if (sock == -1) 
  {
    fprintf(stderr, "fallo la creacion de la conexion");
    exit(-1);
  }


  while(1) {
    sockdup = aceptar_pedidos(sock, 1);

    // read(sockdup, &entero, sizeof(int32_t));
    read(sockdup, &entero, 4096);
    fprintf(stderr, "Se conecto un cliente y dijo: %d xd\n", entero);


    // r = write(sockdup, msg, strlen(msg));
    // if (r == -1) 
    // {
    //   fprintf(stderr, "fallo la escritur");
    //   exit(-2);
    // }
    close(sockdup);
  }

  close(sock);


  return 0;
}