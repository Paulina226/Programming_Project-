#!bin/bash

all: ocabas

ocabas:  game.o object.o player.o command.o game_loop.o space.o screen.o game_reader.o graphic_engine.o
	gcc -o ocabas game.o space.o screen.o graphic_engine.o game_loop.o command.o object.o player.o game_reader.o


command.o: command.c command.h
	gcc -c command.c 

game_loop.o: game_loop.c graphic_engine.h
	gcc -c game_loop.c 

graphic_engine.o: graphic_engine.c graphic_engine.h screen.h
	gcc -c graphic_engine.c 

screen.o: screen.c screen.h
	gcc -c screen.c 

space.o: space.c space.h types.h object.h
	gcc -c space.c

object.o: object.c object.h types.h
	gcc -c object.c

player.o: player.c player.h types.h
	gcc -c player.c

game.o: game.c game.h gamereader.h player.h object.h
	gcc -c game.c 

game_reader.o: game_reader.c gamereader.h game.h space.h
	gcc -c game_reader.c

clean: 
	rm *.o

dist:
	tar -cvzf files.tgz *.c *.h
