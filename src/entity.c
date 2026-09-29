#include "include/entity.h"

s_entity create_monster() {
    return (s_entity) {
        .type = ENTITY_MONSTER,
        .monster = {
            .hp = 5,
            .dmg = 1
        }
    };
}

s_entity create_player() {
    return (s_entity) {
        .type = ENTITY_PLAYER,
        .player = {
            .hp = 10,
            .dmg = 2,
            .coins = 5
        }
    };
}

s_entity create_medic() {
    return (s_entity) {
        .type = ENTITY_MEDIC,
        .medic = {
            .heal = 5
        }
    };
}

s_entity create_teacher() {
    return (s_entity) {
        .type = ENTITY_TEACHER,
        .teacher = {
            .dmg_up = 1
        }
    };
}

int take_damage(const s_entity* attacker, s_entity* victim) {
    if (victim->type == ENTITY_MONSTER && attacker->type == ENTITY_PLAYER) {
        victim->monster.hp -= attacker->player.dmg;
        if (victim->monster.hp <= 0) {
            return ENTITY_STATE_DEATH;
        }
    } else if (victim->type == ENTITY_PLAYER && attacker->type == ENTITY_MONSTER) {
        victim->player.hp -= attacker->monster.dmg;
        if (victim->player.hp <= 0) {
            return ENTITY_STATE_DEATH;
        }
    }
    return ENTITY_STATE_LIFE;
}

int teach_player(s_player* player, const s_teacher teacher) {
    if (player->coins >= 1) {
        player->dmg += teacher.dmg_up;
        player->coins -= 1;
    }
    return ENTITY_STATE_LIFE;
}

int heal_player(s_player* player, const s_medic medic) {
    if (player->coins >= 1) {
        player->hp += medic.heal;
        player->coins -= 1;
    }
    return ENTITY_STATE_LIFE;
}