#ifndef NODE_HEADER_H
#define NODE_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jansson.h>

typedef struct {
   int num;
   void** values;
} Array;

Array array_create();
void array_push(Array* array, void* value);

typedef struct {
    char* mc_name;
    char* content;
} Lyric;

Lyric* lyric_create(const char* mc_name, const char* content);
void lyric_dump (Lyric* l);
json_t* lyrics_to_json (Array lyrics);

typedef struct {
    char* winner_name;
    Array lyrics;
} Round;

Round* round_create(const char* winner_name, Array lyrics);
void round_dump (Round* r);
json_t* rounds_to_json (Array rounds);

typedef struct {
    char* name;
    char* mc1_name;
    char* mc2_name;
    char* winner_name;
    char* date;
    int num_rounds;
    Array rounds;
} Battle;

Battle* battle_create(const char* name,
                      const char* mc1_name,
                      const char* mc2_name,
                      const char* winner_name,
                      const char* date,
                      Array rounds);
void battle_dump (Battle* b);
json_t* battle_to_json (Battle* b);

#ifdef __cplusplus
}
#endif

#endif
