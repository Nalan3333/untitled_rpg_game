#include <stdio.h>
#include <stdint.h>
#include "include/entity.h"
#include "include/location.h"

#define LOCATION_FOREST '1'
#define LOCATION_FORTRESS '2'

s_entity g_player;

int read_choice() {
    char buf[256];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return EOF;
    return buf[0];
}

int main(void) {
    printf("hi! This a untitled rpg game.\n Press any key to continue:");
    read_choice();

    init_locations();
    printf("You have two locations to choose from:\nForest - difficulty %i\nFortress - difficulty %i",
           g_forest.difficulty, g_fortress.difficulty);
    printf("\nPress the key %c for choose Forest and press the key %c for choose Fortress\n",
           LOCATION_FOREST, LOCATION_FORTRESS);
    int choose_location = read_choice();

    if (choose_location == EOF) {
        goto _error;
    }

    s_location* loc = NULL;
    if (choose_location == LOCATION_FOREST) {
        loc = &g_forest;
    } else if (choose_location == LOCATION_FORTRESS) {
        loc = &g_fortress;
    } else {
        goto _error;
    }

    g_player = create_player();
    printf("You have %d HP, %d DMG, %d coins.\n",
           g_player.player.hp, g_player.player.dmg, g_player.player.coins);

    for (int i = 0; i < 10; i++) {
        s_entity* entity = &loc->entities[i];

        if (entity->type == ENTITY_MONSTER) {
            while (entity->monster.hp > 0) {
                printf("A monster has appeared before you. Your action (1 - attack, 2 - check):");
                int c = read_choice();
                if (c == EOF) goto _error;

                if (c == '1') {
                    int result = take_damage(&g_player, entity);
                    if (result == ENTITY_STATE_DEATH) {
                        printf("You defeated the monster! You found 1 coin.\n");
                        g_player.player.coins += 1;
                        break;
                    }
                    result = take_damage(entity, &g_player);
                    if (result == ENTITY_STATE_DEATH) {
                        printf("You died! Game over.\n");
                        printf("press any key for continue:");
                        read_choice();
                        return -1;
                    }
                    printf("You attacked! Monster HP: %d, Your HP: %d\n",
                           entity->monster.hp, g_player.player.hp);
                } else if (c == '2') {
                    printf("Monster HP: %d, DMG: %d\n", entity->monster.hp, entity->monster.dmg);
                    printf("Your HP: %d, DMG: %d, Coins: %d\n",
                           g_player.player.hp, g_player.player.dmg, g_player.player.coins);

                    printf("While you were checking, the monster attacked!\n");
                    int result = take_damage(entity, &g_player);
                    if (result == ENTITY_STATE_DEATH) {
                        printf("You died! Game over.\n");
                        printf("press any key for continue:");
                        read_choice();
                        return -1;
                    }
                    printf("Monster attacks! Your HP: %d\n", g_player.player.hp);
                } else {
                    printf("Invalid action.\n");
                }
            }
        } else if (entity->type == ENTITY_MEDIC) {
            printf("You found a medic. Heal for 1 coin? (1 - yes, 2 - no): ");
            int c = read_choice();
            if (c == '1') {
                if (g_player.player.coins >= 1) {
                    heal_player(&g_player.player, entity->medic);
                    printf("You healed! HP: %d, Coins: %d\n",
                           g_player.player.hp, g_player.player.coins);
                } else {
                    printf("Not enough coins!\n");
                }
            }
        } else if (entity->type == ENTITY_TEACHER) {
            printf("You found a teacher. Learn for 1 coin? (1 - yes, 2 - no): ");
            int c = read_choice();
            if (c == '1') {
                if (g_player.player.coins >= 1) {
                    teach_player(&g_player.player, entity->teacher);
                    printf("You learned! DMG: %d, Coins: %d\n",
                           g_player.player.dmg, g_player.player.coins);
                } else {
                    printf("Not enough coins!\n");
                }
            }
        }
    }

    printf("You cleared the location! Final HP: %d, DMG: %d, Coins: %d\n",
           g_player.player.hp, g_player.player.dmg, g_player.player.coins);

    printf("\nThe author of this console project is Nalan3333.\n");
    printf("Link to source code: github.com/Nalan3333/untitled_rpg_game");
    printf("\npress any key for exit:");
    read_choice();
    return 0;

_error:
    printf("Oh, an error occurred. Please restart the program.");
    printf("press any key for continue:");
    read_choice();
    return -1;
}