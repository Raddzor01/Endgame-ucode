#include "../inc/mainheader.h"

#define BACK_X 70
#define BACK_Y 50

void about(SDL_Event event, SDL_Renderer *renderer) {

    SDL_Texture *background = IMG_LoadTexture(renderer, "./resource/background/About_menu.png");
    SDL_Texture *back_button = IMG_LoadTexture(renderer, "./resource/buttons/EXIT.png");
    
    SDL_Rect back_button_rect = {BACK_X, BACK_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y};

    bool running = true;

    while (running) {

        while(SDL_PollEvent( &event)) {
			if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT
                    && event.button.x >= BACK_X
                    && event.button.x <= BACK_X + BUTTON_SIZE_X
                    && event.button.y >= BACK_Y
                    && event.button.y <= BACK_Y + BUTTON_SIZE_Y) {
                        SDL_Delay(250);
                        SDL_RenderPresent(renderer);
                        running = false;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.x >= BACK_X
                    && event.motion.x <= BACK_X + BUTTON_SIZE_X
                    && event.motion.y >= BACK_Y
                    && event.motion.y <= BACK_Y + BUTTON_SIZE_Y) {
                        SDL_SetTextureColorMod(back_button, 200, 200, 200);
                        break;
                    }
                    SDL_SetTextureColorMod(back_button, 255, 255, 255);
                    break;
            }

        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, back_button, NULL, &back_button_rect);
        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyTexture(background);
    background = NULL;
}
