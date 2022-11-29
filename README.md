# Kalandjáték 

#### Leírás 
Egy parancssorból futtatható program, ami a megfelelő formátummal rendelkező szövegfájlokból interaktív kalandjátékot állít elő.
Eredetileg egy házifeladatként készült el.

---

#### Telepítés/Buildelés
##### Általános
A forrásfájlok a **main.c, main.h, mainFix.c és a ./lib/ mappában** találhatóak. Csak ezekre a fájlokra lesz szükséged a telepítéshez.
A repo tartalmaz egy példajátékot a **./root/** mappában. Ha egyből ezt szeretnéd játszani, akkor a **mainFix.c** fájlt használd a **main.c** helyett.

##### Linux/Mac
Futtasd a `Makefile`-t, ami lebuildeli neked a programot és parancssorból már futtathatod is.
A program GCC 10.2.1-es verzióval lett tesztelve, így azzal, vagy későbbi verzióval mindenképp rendelkezz.

**Makefile használat:**
- `make`: lebuildeli a programot ***kalandjatek*** néven 
- `make clean`: töröl minden fájlt, ami a buildelés után maradt 
- `make cleanobj`: törli az object fájlokat, amik a buildelés után maradtak

Természetesen máshogy is buildelheted, ezt csak ajánlom.

##### Windows
Buildeld le valahogy...idk.

VSCode, CLion, CodeBlocks, valamelyik C kompatibilis IDE-vel buildeld le.
Ha nem akarsz a parancssoros paraméteres indítgatással hülyéskedni, akkor a buildelésnél ne a main.c-t, hanem a mainFix.c-t használd. Ez egyből a próba játékot használja.

---

#### Hogyan játszd? 
##### Játék fájlok
A program indításakor meg kell adni 2 fájlt paraméterként a parancssorban. (Ha a mainFix.c-vel lett buildelve, akkor nem.)
A repo tartalmaz egy példajátékot a **./root/** mappában, ebből a ***root.txt*** fájlt kell első paraméterként megadni, illetve egy általad választott mentési fájlt másodiknak. (A mentési fájlnak nem kell léteznie.)

A ***root.txt*** további fájl elérési utakat tartalmaz, ezek Linux-on lettek megírva, így elképzelhető, hogy Windows-on ezeket át kell írni. (Jellemzően a /-t \\-re.)

Ha kijátszottad a játékot vagy újrakezdenéd, csak töröld ki a mentési fájlt (mainFix.c esetén ez a **./root/save.txt**) és már játszhatod is újra.

##### Irányítás/Játékmenet 
A kijelző két részre van bontva vízszintesen. A felső mindig az aktuális történéseket írja ki, az alsó pedig a választási lehetőségeidet listázza.
Ha a *Press any key!* kijelzést látod, semmilyen gomb nem látja el eredeti funkcióját, csak tovább lép a játékban.

A játékban szinte mindig képes vagy menteni az **s gomb** megnyomásával, illetve kilépni a **q gomb**-al.
A döntéseid közül mindig a döntés előtt szereplő gombbal tudsz választani. Ha a játék véget ér, kilistázza a megszerzett tárgyaidat és bezárul.
