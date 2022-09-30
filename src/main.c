#include "../inc/mainheader.h"

int main() {
    bool running = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Cursor* cursor;
    SDL_Surface* cursor_image;
    cursor_image = SDL_LoadBMP("./resource/buttons/custom_cursor.bmp");
    cursor = SDL_CreateColorCursor(cursor_image, 0, 0);
    SDL_SetCursor(cursor);

    window = SDL_CreateWindow("Endgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    menu(renderer, running);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );

    window = NULL;
    renderer = NULL;

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
