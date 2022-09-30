#include "../inc/mainheader.h"

SDL_Rect NULL_rect = {0, 0, 0, 0};

bool field (SDL_Event event, SDL_Renderer *renderer, bool running, int key) {

    // int key = 3;

    int size = 0;

    if (key == 1) {
        size = 13;
    } else if (key == 2) {
        size = 17;
    } else if (key == 3) {
        size = 16;
    }

    bool finish;

    t_player *players = (t_player *)malloc(sizeof(t_player));
    t_time *fpsTimer = (t_time *)malloc(sizeof(t_time));
    t_time *capTimer = (t_time *)malloc(sizeof(t_time));
    t_render_object **map_objects = init_struct_render_objects(size);

    init_player(&players, renderer);
    init_render_objects(&map_objects, renderer, key);
    if (key == 1) {
        init_render_object(&map_objects[0], renderer, "./resource/background/Tutor_background.png", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    } else {
        init_render_object(&map_objects[0], renderer, "./resource/background/level_background.png", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    }
    SDL_Texture *move_player_left = IMG_LoadTexture(renderer, "./resource/characters/Ghost_left.png");
    SDL_Texture *move_player_right = IMG_LoadTexture(renderer, "./resource/characters/Ghost_right.png");
    Mix_Chunk *died = Mix_LoadWAV("./resource/music/died.ogg");
    Mix_Chunk *tuturu = Mix_LoadWAV("./resource/music/win.ogg");

    Mix_HaltMusic();

    SDL_RenderClear(renderer);
    start(&fpsTimer);

    while (running) {
        start(&capTimer);

        if (Mix_PlayingMusic() == 0)
            play_music();

        while(SDL_PollEvent( &event)) {
			if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
            handleEvent(event, &players);
        }

        finish = move(&players, map_objects, size, died, tuturu);

        SDL_RenderCopy(renderer, map_objects[0]->ObjectTexture, NULL, &map_objects[0]->ObjectHitbox);
        switch ((* players).sprite) {
            case MOVING_LEFT:
                SDL_RenderCopy(renderer, move_player_left, NULL, &players->player_pos);
                break;
            case MOVING_RIGHT:
                SDL_RenderCopy(renderer, move_player_right, NULL, &players->player_pos);
                break;
            case IDLE:
                SDL_RenderCopy(renderer, players->player_texture, NULL, &players->player_pos);
                break;
        }
        for (int i = 1; i < size; i++)
            SDL_RenderCopy(renderer, map_objects[i]->ObjectTexture, NULL, &map_objects[i]->ObjectHitbox);

        if(finish == true) {
            running = false;
        }

        SDL_RenderPresent(renderer);

        int frameTicks = getTicks(capTimer);
        if (frameTicks < SCREEN_TICK_PER_FRAME)
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);

    }

    // Mix_HaltMusic();

    free(fpsTimer);
    fpsTimer = NULL;
    free(capTimer);
    capTimer = NULL;
    free(players);
    players = NULL;
    Mix_FreeChunk(died);
    Mix_FreeChunk(tuturu);
    for (int i = 0; i < size; i++)
        free_render_object(&map_objects[i]);
    free(map_objects);
    map_objects = NULL;
    return running;
}
