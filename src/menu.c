#include "../inc/mainheader.h"

bool menu (SDL_Renderer *renderer, bool running) {
   
   int size = 4;
    SDL_Event event;
    t_render_object **menu_objects = init_struct_render_objects(size);

    init_render_object(&menu_objects[0], renderer, "./resource/background/menu.png", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    init_render_object(&menu_objects[1], renderer, "./resource/buttons/PLAY.png", START_X, START_Y, BUTTON_SIZE_Y, BUTTON_SIZE_X);
    init_render_object(&menu_objects[2], renderer, "./resource/buttons/EXIT.png", EXIT_X, EXIT_Y, BUTTON_SIZE_Y, BUTTON_SIZE_X);
    init_render_object(&menu_objects[3], renderer, "./resource/buttons/ABOUT.png", ABOUT_X, ABOUT_Y, BUTTON_SIZE_Y, BUTTON_SIZE_X);

    Mix_Music **soundboard = init_soundboard();
    Mix_Chunk *click = Mix_LoadWAV("./resource/music/najatie.wav");
    Mix_PlayMusic(soundboard[0], -1);
    Mix_VolumeMusic(15);
    
    while(running) {

        while(SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, click, 0);
                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= START_X
                    && event.button.x <= START_X + BUTTON_SIZE_X
                    && event.button.y >= START_Y
                    && event.button.y <= START_Y + BUTTON_SIZE_Y) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        stages(renderer, running);
                        break;
                    } else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= ABOUT_X
                    && event.button.x <= ABOUT_X + BUTTON_SIZE_X
                    && event.button.y >= ABOUT_Y
                    && event.button.y <= ABOUT_Y + BUTTON_SIZE_Y) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        about(event, renderer);
                        break;
                    } else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= EXIT_X
                    && event.button.x <= EXIT_X + BUTTON_SIZE_X
                    && event.button.y >= EXIT_Y
                    && event.button.y <= EXIT_Y + BUTTON_SIZE_Y) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        running = false;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.x >= START_X
                    && event.motion.x <= START_X + BUTTON_SIZE_X
                    && event.motion.y >= START_Y
                    && event.motion.y <= START_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(menu_objects[1]->ObjectTexture, 200, 200, 200);
                        break;
                    } if (event.motion.x >= ABOUT_X
                    && event.motion.x <= ABOUT_X + BUTTON_SIZE_X
                    && event.motion.y >= ABOUT_Y
                    && event.motion.y <= ABOUT_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(menu_objects[3]->ObjectTexture, 200, 200, 200);
                        break;
                    } if (event.motion.x >= EXIT_X
                    && event.motion.x <= EXIT_X + BUTTON_SIZE_X
                    && event.motion.y >= EXIT_Y
                    && event.motion.y <= EXIT_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(menu_objects[2]->ObjectTexture, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(menu_objects[1]->ObjectTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(menu_objects[3]->ObjectTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(menu_objects[2]->ObjectTexture, 255, 255, 255);
                    break;
            }
        }

        for (int i = 0; i < 4; i++)
            SDL_RenderCopy(renderer, menu_objects[i]->ObjectTexture, NULL, &menu_objects[i]->ObjectHitbox);
        SDL_RenderPresent(renderer);

    }

    for (int i = 0; i < size; i++)
        free_render_object(&menu_objects[i]);
    free_soundboard(&soundboard);
    Mix_FreeChunk(click);
    free(menu_objects);
    menu_objects =NULL;
    return running;
}
