output: main.o components.o instantiate.o 
	g++ bin/*.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o bin/output
	# g++ main.o -o main
	# make clean

main.o: src/main.c
	mkdir bin && gcc -c src/main.c -o bin/main.o

components.o: src/components.c
	gcc -c src/components.c -o bin/components.o

instantiate.o: src/instantiate.c
	gcc -c src/instantiate.c -o bin/instantiate.o

clean:
	rm -rf bin
	rm bin/*.o bin/output

run:
	./bin/output