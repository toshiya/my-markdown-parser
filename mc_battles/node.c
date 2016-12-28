#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include "string.h"
#include "node.h"

#define MAX_PTR_SIZE (1 << 16)

static void** memory_pool = NULL;
static int num_pool_element = 0;

void* calloc_pool(size_t count, size_t size) {
    if (memory_pool == NULL) {
        memory_pool = (void**) calloc(MAX_PTR_SIZE, sizeof(void*));
    }
    if (num_pool_element == MAX_PTR_SIZE) {
       printf("Abort. Memory Pool is Overflowed\n");
       exit(1);
    }
    void* ptr = calloc(count, size);
    memory_pool[num_pool_element++] = ptr;
    return ptr;
}

void free_pool() {
    free(memory_pool);
    for (int i = 0; i < num_pool_element; i++) {
        free(memory_pool[i]);
    }
    num_pool_element = 0;
}

#define MAX_ARRAY_ELEMENT 16
Array array_create() {
    Array a;
    a.num = 0;
    a.values = (void**) calloc_pool(MAX_ARRAY_ELEMENT, sizeof(void*));
    return a;
}

void array_push(Array* array, void* value) {
    array->values[array->num] = value;
    array->num += 1;
}


Lyric* lyric_create(const char* mc_name, const char* content) {
    Lyric* lyric   = (Lyric*) calloc_pool(1, sizeof(Lyric));
    lyric->mc_name = (char*)  calloc_pool(1, strlen(mc_name) + 1);
    lyric->content = (char*)  calloc_pool(1, strlen(content) + 1);

    strcpy(lyric->mc_name, mc_name);
    strcpy(lyric->content, content);
    return lyric;
}

Round* round_create(const char* winner_name, Array lyrics) {
    Round* round       = (Round*) calloc_pool(1, sizeof(Round));
    round->winner_name = (char*) calloc_pool(1, strlen(winner_name) + 1);
    strcpy(round->winner_name, winner_name);
    round->lyrics = lyrics;
    return round;
}

Battle* battle_create(const char* name,
                      const char* mc1_name,
                      const char* mc2_name,
                      const char* winner_name,
                      const char* date, Array rounds) {
    Battle* battle      = (Battle*) calloc_pool(1, sizeof(Battle));
    battle->name        = (char*)   calloc_pool(1, strlen(name) + 1);
    battle->mc1_name    = (char*)   calloc_pool(1, strlen(mc1_name) + 1);
    battle->mc2_name    = (char*)   calloc_pool(1, strlen(mc2_name) + 1);
    battle->winner_name = (char*)   calloc_pool(1, strlen(winner_name) + 1);
    battle->date        = (char*)   calloc_pool(1, strlen(date) + 1);

    strcpy(battle->name, name);
    strcpy(battle->mc1_name, mc1_name);
    strcpy(battle->mc2_name, mc2_name);
    strcpy(battle->winner_name, winner_name);
    strcpy(battle->date, date);
    battle->rounds = rounds;

    return battle;
}

json_t* lyrics_to_json (Array ls) {
    json_t* jarr = json_array();
    for (int i = 0; i < ls.num; i++) {
        Lyric* l = (Lyric*) ls.values[i];
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
        Round* r = (Round*)rs.values[i];
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
