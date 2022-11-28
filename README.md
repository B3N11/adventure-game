# Adventure Game

#### Description
A textfile based program that turns text files with the specified format
into a playable CLI adventure game. The program was originally created as a homework.

---

#### Install
##### Linux/Mac
Run the `Makefile` found in the repo. The **Makefile** requires the file structure to be as in the repo:
<img src="/home/brokkr/Pictures/fileStruct.png" width=120 />

The program was build using GCC 10.2.1, but is should work on later versions.

**Makefile usage:**
- `make`: builds the program with the output named *kalandjatek*
- `make clean`: removes the object files and the executable
- `make cleanobj`: removes only the object files


##### Windows
Use any kind of C compatible IDE (VSCode, CLion, CodeBlocks, etc.)


#### How to play
##### Game files
The program itself doesn't have a game in it, it just reads the given files and turns them into a playable format.
The repo contains an example story however (in Hungarian), in the **root** directory.
You can play that, or write your own. The gamefiles need to be in a specific format.

##### Controls
The game interface is split into two main windows. The top window describes what is happening and
the bottom window shows you the choices. At almost any time in the game, you can **quit** and **save**.
Both the options are unavailable when the ***Press any key!*** text is displayed in the bottom window.

Your options are always displayed in the bottom window and you can choose one of them by pressing the
key next to the option.
