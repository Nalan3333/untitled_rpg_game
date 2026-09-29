#include "include/location.h"

#include "include/entity.h"

s_location g_forest;
s_location g_fortress;

void init_locations() {
    g_forest.difficulty = 1;
    // fill entities
    {
        g_forest.entities[0] = create_monster();
        g_forest.entities[1] = create_monster();
        g_forest.entities[2] = create_medic();
        g_forest.entities[3] = create_teacher();
        g_forest.entities[4] = create_monster();
        g_forest.entities[5] = create_medic();
        g_forest.entities[6] = create_monster();
        g_forest.entities[7] = create_monster();
        g_forest.entities[8] = create_teacher();
        g_forest.entities[9] = create_monster();
    }

    g_fortress.difficulty = 2;
    // fill entities
    {
        g_fortress.entities[0] = create_monster();
        g_fortress.entities[1] = create_monster();
        g_fortress.entities[2] = create_medic();
        g_fortress.entities[3] = create_monster();
        g_fortress.entities[4] = create_monster();
        g_fortress.entities[5] = create_monster();
        g_fortress.entities[6] = create_medic();
        g_fortress.entities[7] = create_teacher();
        g_fortress.entities[8] = create_monster();
        g_fortress.entities[9] = create_monster();
    }
}