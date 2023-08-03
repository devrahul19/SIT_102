#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <string>
#include <vector>

using std::vector;
using namespace std;

#define MIN -1600
#define MAX 1600
#define LEVEL_TIME 20000

// structure for game data
struct game_data
{
    player_data player;
    vector<powerups_data> powers;
    timer game_timer;
};

game_data new_game();
void update_game(game_data &game);
void draw_game(game_data &game);
void add_powerup(game_data &game);
void check_collision(game_data &game);
void apply_powerup(game_data &game, int index);
void remove_powerup(game_data &game, int index);
void draw_mini_map(const vector<powerups_data> &powers);
point_2d mini_map_coordinate(const powerups_data &power_up);
void draw_hud(game_data& game);
#endif