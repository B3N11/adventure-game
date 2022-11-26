output: main.o ext_string.o filehandler.o game.o gameData.o item.o logger.o panel.o econio.o ioHandle.o 
	gcc main.o ext_string.o filehandler.o game.o gameData.o item.o logger.o panel.o econio.o ioHandle.o -o kalandjatek

debug: main.o ext_string.o filehandler.o game.o gameData.o item.o logger.o panel.o econio.o ioHandle.o
	gcc main.o ext_string.o filehandler.o game.o gameData.o item.o logger.o panel.o econio.o ioHandle.o -o kalandjatek -g

econio.o: ./lib/econio.c
	gcc ./lib/econio.c -c -o econio.o -g

ioHandle.o: ./lib/ioHandle.c
	gcc ./lib/ioHandle.c -c -o ioHandle.o -g

ext_string.o: ./lib/ext_string.c
		gcc ./lib/ext_string.c -c -o ext_string.o -g

filehandler.o: ./lib/filehandler.c
	gcc ./lib/filehandler.c -c -o filehandler.o -g

item.o: ./lib/item.c
	gcc ./lib/item.c -c -o item.o -g

logger.o: ./lib/logger.c
	gcc ./lib/logger.c -c -o logger.o -g

panel.o: ./lib/panel.c
	gcc ./lib/panel.c -c -o panel.o -g

game.o: ./lib/game.c
	gcc ./lib/game.c -c -o game.o -g

gameData.o: ./lib/gameData.c
	gcc ./lib/gameData.c -c -o gameData.o -g

main.o: main.c
	gcc main.c -c -o main.o -g

clean:
	rm *.o kalandjatek

cleanobj:
	rm *.o
