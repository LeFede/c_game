#include "sock-lib.h"
#include <stdint.h>

#define BUFFER_SIZE 4096
#define SYMBOL 0XAABBCCDD

int main() {
  int sock;

  int8_t entero = 13;

  sock = conectar("localhost", 8000, 1);

  // * Compatibilidad en escritura:
  // entero = htonl(entero);
  write(sock, &entero, sizeof(int8_t));

  // * Compatibilidad en lectura:
  // read(sock, &entero, sizeof(int8_t));
  // entero = ntohl(entero);
  // fprintf(stderr, "debug rx=%d\n", entero);

  close(sock);
}