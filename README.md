gcc -Wall server.c sock-lib.c -o server && ./server
gcc -Wall client.c sock-lib.c -o client && ./client
gcc -Wall main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./a.out
