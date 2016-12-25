#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include "string.h"
#include "node.h"

#define MAX_ARRAY_ELEMENT 16
Array array_create() {
    Array a;
    a.num = 0;
    a.values = (void**) calloc(MAX_ARRAY_ELEMENT, sizeof(void*));
    return a;
}

void array_push(Array* array, void* value) {
    array->values[array->num] = value;
    array->num += 1;
}


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

Round* round_create(char* winner_name, Array lyrics) {
    Round* round    = calloc(1, sizeof(Round));
    round->winner_name = calloc(1, strlen(winner_name) + 1);
    strcpy(round->winner_name, winner_name);
    round->lyrics = lyrics;
    return round;
}
void round_dump (Round* r) {
    printf("winner_name:%s\n", r->winner_name);
    printf("lyrics:\n");
    for (int i = 0; i < r->lyrics.num; i++) {
        lyric_dump((Lyric*)(r->lyrics.values[i]));
    }
}

Battle* battle_create(char* name, char* mc1_name, char* mc2_name, char* winner_name, char* date, Array rounds) {
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
    for (int i = 0; i < b->rounds.num; i++) {
        round_dump((Round*)b->rounds.values[i]);
    }
}

json_t* lyrics_to_json (Array ls) {
    json_t* jarr = json_array();
    for (int i = 0; i < ls.num; i++) {
        Lyric* l = ls.values[i];
        json_t* jdata = json_object();
        json_object_set_new(jdata, "mc_name", json_string(l->mc_name));
        json_object_set_new(jdata, "content", json_string(l->content));
        json_array_append_new( jarr, jdata );
    }
    return jarr;
}

json_t* rounds_to_json (Array rs) {
    json_t* jarr = json_array();
    for (int i = 0; i < rs.num; i++) {
        Round* r = rs.values[i];
        json_t* jdata = json_object();
        json_object_set_new(jdata, "winner_name", json_string(r->winner_name));
        json_object_set_new(jdata, "lyrics", lyrics_to_json(r->lyrics));
        json_array_append_new( jarr, jdata );
    }
    return jarr;
}

json_t* battle_to_json (Battle* b) {
    json_t* jdata;
    jdata = json_object();

    json_object_set_new(jdata, "name", json_string(b->name));
    json_object_set_new(jdata, "mc1_name", json_string(b->mc1_name));
    json_object_set_new(jdata, "mc2_name", json_string(b->mc2_name));
    json_object_set_new(jdata, "winner_name", json_string(b->winner_name));
    json_object_set_new(jdata, "date", json_string(b->date));
    json_object_set_new(jdata, "rounds", rounds_to_json(b->rounds));

    return jdata;
}


//int
//main() {
//    Array ls = array_create();
//    array_push(&ls, lyric_create("hoge", "バースだぜ！ Yeah! Yeah!"));
//    array_push(&ls, lyric_create("piyo", "オレは東京生まれ　ヒップホップ育ち"));
//
//    Array rs = array_create();
//    array_push(&rs, round_create("hoge", ls));
//
//    Battle* b = calloc(1, sizeof(Battle));
//    b = battle_create("バトル１", "hoge", "piyo", "piyo", "2016/12/24", rs);
//
//    printf("%s", json_dumps(battle_to_json(b), 0));
//    return 0;
//}
