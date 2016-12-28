#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../node.h"

TEST(ArrayTest, createAndPush) {
    Array a = array_create();
    array_push(&a, (void*)"element1");
    array_push(&a, (void*)"element2");
    ASSERT_EQ(2, a.num);
    ASSERT_TRUE(a.values[1] == "element2");
}

TEST(LyricTest, create) { 
    Lyric *l = lyric_create("MC1", "バースだぜ！ Yeah! Yeah!");
    ASSERT_EQ(0, strcmp("MC1", l->mc_name));
    ASSERT_EQ(0, strcmp("バースだぜ！ Yeah! Yeah!", l->content));
}

TEST(RoundTest, create) {
    Round* r = round_create("MC1", array_create());
    ASSERT_EQ(0, strcmp("MC1", r->winner_name));
}

TEST(BattleTest, create) {
    Battle *b = battle_create("バトル１", "MC1", "MC2", "winner", "2016/12/24", array_create());
    ASSERT_EQ(0, strcmp("バトル１", b->name));
    ASSERT_EQ(0, strcmp("winner", b->winner_name));
    ASSERT_EQ(0, strcmp("MC1", b->mc1_name));
    ASSERT_EQ(0, strcmp("MC2", b->mc2_name));
    ASSERT_EQ(0, strcmp("2016/12/24", b->date));
}

TEST(BattleTest, battleToJson) {
    Array ls = array_create();
    array_push(&ls, lyric_create("MC1", "バースだぜ！ Yeah! Yeah!"));

    Array rs = array_create();
    array_push(&rs, round_create("MC1", ls));
    Battle *b = battle_create("バトル１", "MC1", "MC2", "winner", "2016/12/24", rs);

    std::string json_str = json_dumps(battle_to_json(b), 0);
    std::string expected = R"({"name": "バトル１", "mc1_name": "MC1", "mc2_name": "MC2", "winner_name": "winner", "date": "2016/12/24", "rounds": [{"winner_name": "MC1", "lyrics": [{"mc_name": "MC1", "content": "バースだぜ！ Yeah! Yeah!"}]}]})";
    ASSERT_EQ(expected, json_str);
}
