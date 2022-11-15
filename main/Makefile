output: ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o
	gcc ./obj/main.o ./obj/ext_string.o ./obj/filehandler.o ./obj/gameData.o ./obj/item.o ./obj/logger.o ./obj/panel.o -o kalandjatek

./obj/ext_string.o: ./lib/ext_string.c
		gcc ./lib/ext_string.c -c -o ./obj/ext_string.o

./obj/filehandler.o: ./lib/filehandler.c
	gcc ./lib/filehandler.c -c -o ./obj/filehandler.o

./obj/item.o: ./lib/item.c
	gcc ./lib/item.c -c -o ./obj/item.o

./obj/logger.o: ./lib/logger.c
	gcc ./lib/logger.c -c -o ./obj/logger.o

./obj/panel.o: ./lib/panel.c
	gcc ./lib/panel.c -c -o ./obj/panel.o

./obj/gameData.o: ./lib/gameData.c
	gcc ./lib/gameData.c -c -o ./obj/gameData.o

./obj/main.o: main.c
	gcc main.c -c -o ./obj/main.o

clean:
	rm ./obj/*.o kalandjatek 
