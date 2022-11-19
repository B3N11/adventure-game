output: ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o ./obj/econio.o ./obj/ioHandle.o 
	gcc ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o ./obj/econio.o ./obj/ioHandle.o -o kalandjatek

debug: ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o ./obj/econio.o ./obj/ioHandle.o
	gcc ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o ./obj/econio.o ./obj/ioHandle.o -o kalandjatek -g

./obj/econio.o: ./lib/econio.c
	gcc ./lib/econio.c -o ./obj/econio.o

./obj/ioHandle.o: ./lib/ioHandle.c
	gcc ./lib/ioHandle.c -o ./obj/ioHandle.o -g

./obj/ext_string.o: ./lib/ext_string.c
		gcc ./lib/ext_string.c -c -o ./obj/ext_string.o -g

./obj/filehandler.o: ./lib/filehandler.c
	gcc ./lib/filehandler.c -c -o ./obj/filehandler.o -g

./obj/item.o: ./lib/item.c
	gcc ./lib/item.c -c -o ./obj/item.o -g

./obj/logger.o: ./lib/logger.c
	gcc ./lib/logger.c -c -o ./obj/logger.o -g

./obj/panel.o: ./lib/panel.c
	gcc ./lib/panel.c -c -o ./obj/panel.o -g

./obj/gameData.o: ./lib/gameData.c
	gcc ./lib/gameData.c -c -o ./obj/gameData.o -g

./obj/main.o: main.c
	gcc main.c -c -o ./obj/main.o -g

clean:
	rm ./obj/*.o kalandjatek 
