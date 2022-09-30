#include "../inc/mainheader.h"

#define BACK_X 90
#define BACK_Y 800

bool stages (SDL_Renderer *renderer, bool running) {
   
   int size = 4;
    SDL_Event event;
    t_render_object **stages_objects = init_struct_render_objects(size);

    init_render_object(&stages_objects[0], renderer, "./resource/background/Levels.png", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    init_render_object(&stages_objects[1], renderer, "./resource/background/st1_prev.jpg", LEVEL1_PREV_X, LEVEL1_PREV_Y, LEVEL_PREV_HEIGHT, LEVEL_PREV_WIDTH);
    init_render_object(&stages_objects[2], renderer, "./resource/background/st3_prev.jpg", LEVEL3_PREV_X, LEVEL3_PREV_Y, LEVEL_PREV_HEIGHT, LEVEL_PREV_WIDTH);
    init_render_object(&stages_objects[3], renderer, "./resource/background/st2_prev.jpg", LEVEL2_PREV_X, LEVEL2_PREV_Y, LEVEL_PREV_HEIGHT, LEVEL_PREV_WIDTH);
    SDL_Texture *back_button = IMG_LoadTexture(renderer, "./resource/buttons/EXIT.png");

    SDL_Rect back_button_rect = {BACK_X, BACK_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};

    Mix_Music **soundboard = init_soundboard();
    Mix_Chunk *click = Mix_LoadWAV("./resource/music/najatie.wav");

    while(running) {

        while(SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    Mix_PlayChannel(-1, click, 0);
                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= LEVEL1_PREV_X
                    && event.button.x <= LEVEL1_PREV_X + LEVEL_PREV_WIDTH
                    && event.button.y >= LEVEL1_PREV_Y
                    && event.button.y <= LEVEL1_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        field(event, renderer, running, 1);
                        break;
                    } else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= LEVEL3_PREV_X
                    && event.button.x <= LEVEL3_PREV_X + LEVEL_PREV_WIDTH
                    && event.button.y >= LEVEL3_PREV_Y
                    && event.button.y <= LEVEL3_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        field(event, renderer, running, 3);
                        break;
                    } else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= LEVEL2_PREV_X
                    && event.button.x <= LEVEL2_PREV_X + LEVEL_PREV_WIDTH
                    && event.button.y >= LEVEL2_PREV_Y
                    && event.button.y <= LEVEL2_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_Delay(250);
                        field(event, renderer, running, 2);
                        break;
                    } else if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= BACK_X
                    && event.button.x <= BACK_X + BUTTON_SIZE_X
                    && event.button.y >= BACK_Y
                    && event.button.y <= BACK_Y + BUTTON_SIZE_Y) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        running = false;
                        break;
                    }
                    Mix_PlayChannel(-1, click, 0);
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.x >= LEVEL1_PREV_X
                    && event.motion.x <= LEVEL1_PREV_X + LEVEL_PREV_WIDTH
                    && event.motion.y >= LEVEL1_PREV_Y
                    && event.motion.y <= LEVEL1_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_SetTextureColorMod(stages_objects[1]->ObjectTexture, 200, 200, 200);
                        break;
                    } if (event.motion.x >= LEVEL3_PREV_X
                    && event.motion.x <= LEVEL3_PREV_X + LEVEL_PREV_WIDTH
                    && event.motion.y >= LEVEL3_PREV_Y
                    && event.motion.y <=  LEVEL3_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_SetTextureColorMod(stages_objects[2]->ObjectTexture, 200, 200, 200);
                        break;
                    } if (event.motion.x >= LEVEL2_PREV_X
                    && event.motion.x <= LEVEL2_PREV_X + LEVEL_PREV_WIDTH
                    && event.motion.y >= LEVEL2_PREV_Y
                    && event.motion.y <= LEVEL2_PREV_Y + LEVEL_PREV_HEIGHT) {
                        SDL_SetTextureColorMod(stages_objects[3]->ObjectTexture, 200, 200, 200);
                        break;
                    } if (event.motion.x >= BACK_X
                    && event.motion.x <= BACK_X + BUTTON_SIZE_X
                    && event.motion.y >= BACK_Y
                    && event.motion.y <= BACK_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(back_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(stages_objects[1]->ObjectTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(stages_objects[3]->ObjectTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(stages_objects[2]->ObjectTexture, 255, 255, 255);
                    SDL_SetTextureColorMod(back_button, 255, 255, 255);
                    break;
            }
        }

        for (int i = 0; i < 4; i++)
            SDL_RenderCopy(renderer, stages_objects[i]->ObjectTexture, NULL, &stages_objects[i]->ObjectHitbox);
        SDL_RenderCopy(renderer, back_button, NULL, &back_button_rect);
        SDL_RenderPresent(renderer);

    }

    for (int i = 0; i < size; i++)
        free_render_object(&stages_objects[i]);
    free_soundboard(&soundboard);
    Mix_FreeChunk(click);
    free(stages_objects);
    stages_objects =NULL;
    return running;
}
