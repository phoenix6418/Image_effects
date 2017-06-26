CFLAGS = -I. -Wall

pa5: main.o image.o
		g++ $(CFLAGS) main.o image.o -o pa5

main.o: main.cpp image.h
		g++ $(CFLAGS) -c main.cpp

image.o: image.cpp image.h
		g++ $(CFLAGS) -c image.cpp

clean:
		rm *.o pa5
