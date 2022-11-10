typedef struct PlayerSave{

}PlayerSave;

typedef struct Item{

    char *id;
    char *name;
    struct Item *next;
}Item;

typedef struct Choice{

    char type;
    char *text;
    char *contentID;
}Choice;

typedef struct Panel{

    char *id;
    char *type;
    char *text;
    Choice **choices;
    struct Panel *next;
}Panel;

typedef struct GameData{

  char *title;
  char *creator;
  Panel *firstPanel;
  Item *firstItem;
  PlayerSave *save;
}GameData;

GameData *CreateGameData();
