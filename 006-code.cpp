#include "splashkit.h"
#include "player.h"
#include "power_up.h"

bitmap powerup_bitmap(powerups power)
{   
     switch (power)
    {
    case FUEL:
        return bitmap_named("fuel");
    case DROPS:
        return bitmap_named("drops");
    case POWERS:
        return bitmap_named("power");
    case POTION:
        return bitmap_named("potion");
    case COIN:
        return bitmap_named("coin");
    }
}

powerups_data new_power_up(double x, double y)
{
    powerups_data result;
    result.kind = static_cast<powerups>(rnd(4));
    result.powerup_sprite = create_sprite(powerup_bitmap(result.kind));
    // intial position of power_up
    sprite_set_x(result.powerup_sprite, x);
    sprite_set_y(result.powerup_sprite, y);
    //
    sprite_set_dx(result.powerup_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.powerup_sprite, rnd() * 4 - 2);
    return result;
}
// THis is used to draw the sprite on screen
void draw_powerups(const powerups_data &power_up)
{
    draw_sprite(power_up.powerup_sprite);
}
// This is used to update the sprite on the basis of movement
void update_powerups(powerups_data &power_up)
{
    update_sprite(power_up.powerup_sprite);
}
