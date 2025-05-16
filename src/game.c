
#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "font.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "world.h"
#include "heart.h"
#include "tracker.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    //Sprite *sprite;
    Level *level;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    GFC_Color mouseGFC_Color = gfc_color8(50,255,50,200
    );

    Entity *player;
    Entity* heart;
    Entity* tracker;

    SJson* save;



    GFC_Rect player_hb;
    GFC_Rect enemy_hb;

    int startx = 0, starty = 0;
    int level_selected = 3;
    
    /*program initializtion*/
    init_logger("gf2d.log",0);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        gfc_vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(4000);
    //font_init();
    entity_system_initialize(4000);
    SDL_ShowCursor(SDL_DISABLE);

    camera_set_size(gfc_vector2d(1200, 720));
    
    /*demo setup*/
    //sprite = gf2d_sprite_load_image("images/backgrounds/level_tileset.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);

    //heart = heart_new(160, 700, 0, 5, 2);

    //level stuff
    level = level_load("defs/levels/levels.map", level_selected);
    level_setup_camera(level);

   
    
    player = NULL;
    heart = NULL;
    tracker = NULL;
  
    // assassin = assassin_new(startx + 50, starty, player, 5, 5, 5);

    slog("press [escape] to quit");
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;

        entity_system_think();
        entity_system_update();
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            //gf2d_sprite_draw_image(sprite,gfc_vector2d(0,0));

       
            
        level_draw(level);
        entity_system_draw();



        //font_draw_text("Press Escape to quit \n isn't that neat", FS_small, GFC_COLOR_CYAN, gfc_vector2d(10, 10));


            //UI elements last
            /*gf2d_sprite_draw(
                mouse,
                gfc_vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseGFC_Color,
                (int)mf);*/

        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());


        if (keys[SDL_SCANCODE_0]) // Main Menu
        {
            entity_clear_all(NULL);
            level_selected = 3;
            slog("3 pressed");
            level = level_load("defs/levels/levels.map", level_selected);
            //entity_free(player);

        }
        if (keys[SDL_SCANCODE_1]) //new game
        {
            //entity_free(player);
            entity_clear_all(NULL);

            level_selected = 1;
            slog("1 pressed");
            level = level_load("defs/levels/levels.map", level_selected);
            level_setup_camera(level);

            startx = get_spawn_x("defs/levels/levels.map", level_selected);
            starty = get_spawn_y("defs/levels/levels.map", level_selected);

            heart = heart_new(160, 700, 0, 5, 2);
            player = player_load("defs/ents/player_default.def", startx, starty, level_selected,level,heart);
            tracker = tracker_new(startx, 65, 0, 1, 2);
            
        }
        if (keys[SDL_SCANCODE_2]) // continue
        {
           // entity_free(player);
            entity_clear_all(NULL);



            save = "defs/ents/player_save.def";
            level_selected = get_current_level(save);

            level = level_load("defs/levels/levels.map", level_selected);
            level_setup_camera(level);

            startx = get_spawn_x("defs/levels/levels.map", level_selected);
            starty = get_spawn_y("defs/levels/levels.map", level_selected);

            //save = sj_copy("defs/ents/player_default.def");
            //sj_save(save, "defs/ents/player_save.def");
            
            heart = heart_new(160, 700, 0, 5, 2);
            player = player_load(save, startx, starty, level_selected, level, heart);
            tracker = tracker_new(startx, 65, 0, 1, 2);


        }
        if (keys[SDL_SCANCODE_3]) // bestiary
        {
            entity_clear_all(NULL);
            level_selected = 4;
            slog("3 pressed");
            level = level_load("defs/levels/levels.map", level_selected);
            //entity_free(player);
            
        }
        if (keys[SDL_SCANCODE_L])// Death Screen
        {
            entity_clear_all(NULL);
            level_selected = 5;
            slog("3 pressed");
            level = level_load("defs/levels/levels.map", level_selected);
        }
        if (keys[SDL_SCANCODE_N] && player->position.x >2000)// Next Screen
        {
            int now;

            level_selected = 2;
            slog("2 pressed");
            level = level_load("defs/levels/levels.map", level_selected);
            tracker = tracker_new(startx, 65, 0, 1, 2);
            
           
            player->position.x = startx;
            //heart = heart_new(160, 700, 0, 4, 2);

            //heart->position.x = startx;

            
            
        }

    }
    entity_free(player);
    level_free(level);
    

    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
