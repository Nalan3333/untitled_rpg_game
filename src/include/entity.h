#pragma once

#define ENTITY_MEDIC 0
#define ENTITY_MONSTER 1
#define ENTITY_TEACHER 2
#define ENTITY_PLAYER 3

#define ENTITY_STATE_LIFE 10
#define ENTITY_STATE_DEATH 11

typedef struct {
    int dmg_up;
} s_teacher;

typedef struct {
    int hp;
    int dmg;
} s_monster;

typedef struct {
    int heal;
} s_medic;

typedef struct {
    int hp;
    int dmg;
    int coins;
} s_player;

typedef struct {
    union {
        s_monster monster;
        s_medic medic;
        s_teacher teacher;
        s_player player;
    };
    int type;
} s_entity;

s_entity create_monster();
s_entity create_player();
s_entity create_medic();
s_entity create_teacher();

int take_damage(const s_entity* attacker, s_entity* victim);
int teach_player(s_player* player, s_teacher teacher);
int heal_player(s_player* player, s_medic medic);