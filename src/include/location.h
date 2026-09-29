#pragma once
#include "entity.h"
typedef struct {
    int difficulty;
    s_entity entities[10];
} s_location;

extern s_location g_forest;
extern s_location g_fortress;

void init_locations();