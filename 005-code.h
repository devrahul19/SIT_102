#ifndef LOST_IN_SPACE_POWERUPS
#define LOST_IN_SPACE_POWERUPS

#include "splashkit.h"
#include "player.h"


using namespace std;
// #define POWERUPS_SPEED 100
// #define POWERUPS_ROTATION_SPEED 100

enum powerups
{
    FUEL,
    DROPS,
    POWERS,
    POTION,
    COIN
};
struct powerups_data
{
    sprite powerup_sprite;
    powerups kind;
};
bitmap powerup_bitmap(powerups power);
powerups_data new_power_up(double x, double y);
void draw_powerups(const powerups_data &power_up_to_draw);
void update_powerups(powerups_data &power_up_to_update);
#endif