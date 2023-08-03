#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"

game_data new_game()
{
    game_data object;
    object.player = new_player();
    object.game_timer = create_timer("TIMER");
    reset_timer("TIMER");
    start_timer(object.game_timer);
    return object;
}

// updates the game
void update_game(game_data &game)
{
    if (rnd() < 0.10)
    {
        add_powerup(game);
    }
    check_collision(game);
    // to update power ups

    for (int i = 0; i < game.powers.size(); i++)
    {
        update_powerups(game.powers[i]);
    }

    // to update player
    update_player(game.player);
}

// draws the game
void draw_game(game_data &game)
{
    draw_hud(game);
    draw_player(game.player);
    for (int i = 0; i < game.powers.size(); i++)
    {
        draw_powerups(game.powers[i]);
    }
}

// add the powerups
void add_powerup(game_data &game)
{
    for (int i = 0; i < 10; i++)
    {
        game.powers.push_back(new_power_up(rnd(MIN, MAX), rnd(MIN, MAX)));
    }
}

// check the collision of powerups with ship
void check_collision(game_data &game)
{
    for (int i = 0; i < game.powers.size(); i++)
    {
        if (sprite_collision(game.player.player_sprite, game.powers[i].powerup_sprite))
        {
            apply_powerup(game, i);
            remove_powerup(game, i);
            game.player.score++;
        }
    }
}

// after collision sound is played and score adds ups
void apply_powerup(game_data &game, int index)
{

    load_sound_effect("collide", "yes.wav");
    play_sound_effect("collide");
    reset_timer("TIMER");

    if (game.powers[index].kind == FUEL)
    {
        game.player.fuel += 0.25;
        if (game.player.fuel > 1)
        {
            game.player.fuel = 1;
        }
    }
}

// remove powerups  when collides
void remove_powerup(game_data &game, int index)
{
    game.powers[index] = game.powers[game.powers.size() - 1];
    game.powers.pop_back();
}

// draws mini map
void draw_mini_map(const vector<powerups_data> &powers)
{
    for (int i = 0; i < powers.size(); i++)
    {

        draw_pixel(color(COLOR_WHITE_SMOKE), mini_map_coordinate(powers[i]), option_to_screen());
    }
}

// function  for mini map coordinates
point_2d mini_map_coordinate(const powerups_data &power_up)
{

    double x = (sprite_x(power_up.powerup_sprite) + 1500) / 3000 * (100) + 1410;
    double y = (sprite_y(power_up.powerup_sprite) + 1500) / 3000 * (100) + 0;
    if (x < 1400 || y > 100)
    {
        return point_at(0, 0);
    }
    return point_at(x, y);
}

// drawing the Hud
void draw_hud(game_data &game)
{
    draw_bitmap(bitmap_named("back.jpg"), 0, 0, option_to_screen());

    draw_bitmap(bitmap_named("fuel"), 50, 30, option_to_screen());
    draw_bitmap(bitmap_named("empty"), 145, 65, option_to_screen());
    draw_bitmap(bitmap_named("full"), 145, 64, option_part_bmp(0, 0, bitmap_width("full") * game.player.fuel, bitmap_height("full"), option_to_screen()));

    // Draw score and location of the player on the HUD
    draw_text("SCORE: " + to_string(game.player.score), COLOR_WHITE, 100, 830, option_to_screen());

    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, 100, 850, option_to_screen());

    double percentage = (LEVEL_TIME - timer_ticks("TIMER"));
    if (percentage < 0)
    {
        percentage = 0;
    }
    draw_text("TIMER: " + to_string(timer_ticks("TIMER")), COLOR_WHITE, 100, 870, option_to_screen());
    // to draw minimap
    draw_rectangle(COLOR_WHITE, 1395, -5, 120, 120, option_to_screen());
    fill_rectangle(COLOR_BLACK, 1400, 0, 110, 110, option_to_screen());
    draw_text("MINI MAP", COLOR_WHITE_SMOKE, 1420, 120, option_to_screen());
    draw_mini_map(game.powers);
}
