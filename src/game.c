
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
    Entity *monster;
    Entity* adv_skrimisher;
    Entity* skirmisher;
    Entity* assassin;
    Entity* shield_bot;
    Entity* boss;
    Entity* heart;
    
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
    
    //spawn player
    player = player_new(5, 5, 2, 0);

    //spawn mobs

    //spawn rams
    monster = monster_new(500, 70,  player, 5, 0, 3);
    monster = monster_new(500, 200, player, 5, 0, 3);
    monster = monster_new(500, 300, player, 5, 0, 3);
    monster = monster_new(500, 400, player, 5, 0, 3);
    monster = monster_new(500, 500, player, 5, 0, 3);
    monster = monster_new(500, 600, player, 5, 0, 3);

    //spawn skirmisher
    skirmisher = new_skirmisher(1000, 100, player, 20, 10, 40);
    skirmisher = new_skirmisher(1000, 200, player, 20, 10, 40);
    skirmisher = new_skirmisher(1000, 300, player, 20, 10, 40);
    skirmisher = new_skirmisher(1000, 400, player, 20, 10, 40);
    skirmisher = new_skirmisher(1000, 500, player, 20, 10, 40);


    //spawn adv.skirmisher
    adv_skrimisher = new_adv_skirmisher(1500, 100, player, 20, 10, 40);
    adv_skrimisher = new_adv_skirmisher(1500, 200, player, 20, 10, 40);
    adv_skrimisher = new_adv_skirmisher(1500, 300, player, 20, 10, 40);
    adv_skrimisher = new_adv_skirmisher(1500, 400, player, 20, 10, 40);
    adv_skrimisher = new_adv_skirmisher(1500, 500, player, 20, 10, 40);



    //spawn assassin
    assassin = assassin_new(700, 70,  player, 10, 5, 40);
    assassin = assassin_new(700, 200, player, 10, 5, 40);
    assassin = assassin_new(700, 300, player, 10, 5, 40);
    assassin = assassin_new(700, 400, player, 10, 5, 40);
    assassin = assassin_new(700, 500, player, 10, 5, 40);


    //spawn shield drone
    shield_bot = new_shield_bot(1400, 70, player, 5, 20, 10);
    shield_bot = new_shield_bot(1400, 200, player, 5, 20, 10);
    shield_bot = new_shield_bot(1400, 300, player, 5, 20, 10);
    shield_bot = new_shield_bot(1400, 400, player, 5, 20, 10);
    shield_bot = new_shield_bot(1400, 500, player, 5, 20, 10);


    //spawn boss
    boss = boss_new(2000, 400, player,50, 30, 100);

    heart = heart_new(160, 700, 0, 5, 2);

    //level stuff
    level = level_load("defs/levels/level_1.map");
    level_setup_camera(level);

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
    }
    entity_free(player);
    level_free(level);

    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
