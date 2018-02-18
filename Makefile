OPENCV = `pkg-config opencv --cflags --libs`

LIBS = $(OPENCV)
CC = g++
CFLAGS = -c

all: rl


rl: Agent.o DrwaWorld.o elements.o main.o World.o
		$(CC) Agent.o DrwaWorld.o elements.o main.o World.o -o rl $(LIBS)

main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp $(LIBS)

DrwaWorld.o: DrwaWorld.cpp
		$(CC) $(CFLAGS) DrwaWorld.cpp $(LIBS)

elements.o: elements.cpp
		$(CC) $(CFLAGS) elements.cpp $(LIBS)

Agent.o: Agent.cpp
		$(CC) $(CFLAGS) Agent.cpp $(LIBS)

World.o: World.cpp
		$(CC) $(CFLAGS) World.cpp $(LIBS)

clean:
	 rm *o kmeans
