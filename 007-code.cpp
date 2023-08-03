#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"

void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

int main()
{
    // Open a window with title "Lost in Space"
    open_window("Lost In Space", 1500, 900);
    // Call load_resources procedure
    load_resources();

    // Define variables
    game_data game;
    game = new_game();


    while (not quit_requested())
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(game.player);

        // Perform movement and update the camera
        update_game(game);
        
        // Redraw everything
        clear_screen(COLOR_BLACK);
        // Call draw player and power_ups
        draw_game(game);
         // Refresh screen with 60 Hertz
        refresh_screen(60);
    }
    return 0;
}