#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct {
    char* mc_name;
    char* content;
} Lyric;
Lyric* lyric_create(char* mc_name, char* content) {
    Lyric* lyric   = calloc(1, sizeof(Lyric));
    lyric->mc_name = calloc(1, strlen(mc_name) + 1);
    lyric->content = calloc(1, strlen(content) + 1);

    strcpy(lyric->mc_name, mc_name);
    strcpy(lyric->content, content);
    return lyric;
}
void lyric_dump (Lyric* l) {
    printf("mc_name:%s\n", l->mc_name);
    printf("content:%s\n", l->content);
}

typedef struct {
    char* mc1_name;
    char* mc2_name;
    Lyric **lyrics;
    int num_lyrics;
} Round;
Round* round_create(char* mc1_name, char* mc2_name, int num_lyrics, Lyric** lyrics) {
    Round* round    = calloc(1, sizeof(Round));
    round->mc1_name = calloc(1, strlen(mc1_name) + 1);
    round->mc2_name = calloc(1, strlen(mc2_name) + 1);
    strcpy(round->mc1_name, mc1_name);
    strcpy(round->mc2_name, mc2_name);
    round->num_lyrics = num_lyrics;
    round->lyrics = lyrics;
    return round;
}
void round_dump (Round* r) {
    printf("mc1_name:%s\n", r->mc1_name);
    printf("mc2_name:%s\n", r->mc2_name);
    printf("lyrics:\n");
    for (int i = 0; i < r->num_lyrics; i++) {
        lyric_dump(r->lyrics[i]);
    }
}

typedef struct {
    char* name;
    char* mc1_name;
    char* mc2_name;
    char* winner_name;
    char* date;
    int num_rounds;
    Round **rounds;
} Battle;
Battle* battle_create(char* name, char* mc1_name, char* mc2_name, char* winner_name, char* date, int num_rounds, Round** rounds) {
    Battle* battle = calloc(1, sizeof(Battle));
    battle->name = calloc(1, strlen(name) + 1);
    battle->mc1_name = calloc(1, strlen(mc1_name) + 1);
    battle->mc2_name = calloc(1, strlen(mc2_name) + 1);
    battle->winner_name = calloc(1, strlen(winner_name) + 1);
    battle->date = calloc(1, strlen(date) + 1);

    strcpy(battle->name, name);
    strcpy(battle->mc1_name, mc1_name);
    strcpy(battle->mc2_name, mc2_name);
    strcpy(battle->winner_name, winner_name);
    strcpy(battle->date, date);
    battle->num_rounds = num_rounds;
    battle->rounds = rounds;

    return battle;
}
void battle_dump (Battle* b) {
    printf("name:%s\n", b->name);
    printf("mc1_name:%s\n", b->mc1_name);
    printf("mc2_name:%s\n", b->mc2_name);
    printf("winner_name:%s\n", b->winner_name);
    printf("date:%s\n", b->date);
    printf("Rounds:\n");
    for (int i = 0; i < b->num_rounds; i++) {
        round_dump(b->rounds[i]);
    }
}

int
main() {
    Lyric** ls = calloc(2, sizeof(Lyric*));
    ls[0] = lyric_create("hoge", "バースだぜ！ Yeah! Yeah!");
    ls[1] = lyric_create("piyo", "オレは東京生まれ　ヒップホップ育ち");

    Round** rs = calloc(1, sizeof(Round*));
    rs[0] = round_create("hoge", "piyo", 2, ls);

    Battle* b = calloc(1, sizeof(Battle));
    b = battle_create("バトル１", "hoge", "piyo", "piyo", "2016/12/24", 1, rs);

    battle_dump(b);
    return 0;
}
