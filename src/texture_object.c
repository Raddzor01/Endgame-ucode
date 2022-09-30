#include "../inc/texture_object.h"

void platform (t_render_object ***objects, SDL_Renderer *renderer, int x, int y, int h, int w, int i) {
    
    (* objects)[i]->ObjectTexture = IMG_LoadTexture(renderer, "./resource/background/Platform.png");
    (*objects)[i]->type_object = PLATFORM;

    (* objects)[i]->ObjectHitbox.x = x;
    (* objects)[i]->ObjectHitbox.y = y;

    (* objects)[i]->ObjectHitbox.h = h;
    (* objects)[i]->ObjectHitbox.w = w;

}

void spike (t_render_object ***objects, SDL_Renderer *renderer, int x, int y, int h, int w, int i) {
    (* objects)[i]->ObjectTexture = IMG_LoadTexture(renderer, "./resource/background/Spike.png");
    (*objects)[i]->type_object = SPIKE;

    (* objects)[i]->ObjectHitbox.x = x;
    (* objects)[i]->ObjectHitbox.y = y;

    (* objects)[i]->ObjectHitbox.h = h;
    (* objects)[i]->ObjectHitbox.w = w;
}

void door (t_render_object ***objects, SDL_Renderer *renderer, int x, int y, int h, int w, int i) {
    (* objects)[i]->ObjectTexture = IMG_LoadTexture(renderer, "./resource/background/Door.png");
    (*objects)[i]->type_object = DOOR;

    (* objects)[i]->ObjectHitbox.x = x;
    (* objects)[i]->ObjectHitbox.y = y;

    (* objects)[i]->ObjectHitbox.h = h;
    (* objects)[i]->ObjectHitbox.w = w;
}

void init_render_objects(t_render_object ***objects, SDL_Renderer *renderer, int key) {

    if (key == 1) {
        platform (objects, renderer, -30, 1010, 100, 300, 1);
        platform (objects, renderer, 230, 990, 100, 300, 2);
        platform (objects, renderer, 430, 970, 100, 300, 3);
        platform (objects, renderer, 630, 950, 100, 300, 4);
        platform (objects, renderer, 830, 930, 100, 300, 5);
        spike (objects, renderer, 1040, 870, 50, 200, 6);
        platform (objects, renderer, 1030, 910, 100, 300, 7);
        platform (objects, renderer, 1230, 890, 100, 300, 8);
        platform (objects, renderer, 1430, 870, 100, 300, 9);
        platform (objects, renderer, 1630, 850, 100, 300, 10);
        platform (objects, renderer, 1830, 830, 100, 300, 11);
        door (objects, renderer, 1750, 780, 80, 40, 12);
    } else if (key == 2) {
        spike (objects, renderer, 700, 970, 50, 200, 1);
        spike (objects, renderer, 250, 210, 50, 200, 2);
        spike (objects, renderer, 350, 210, 50, 200, 3);
        platform (objects, renderer, -30, 1010, 100, 300, 4);
        platform (objects, renderer, 230, 1010, 100, 300, 5);
        platform (objects, renderer, 490, 1010, 100, 300, 6);
        platform (objects, renderer, 750, 1010, 100, 300, 7);
        platform (objects, renderer, 1270, 850, 300, 200, 8);
        platform (objects, renderer, 1700, 750, 50, 200, 9);
        platform (objects, renderer, 1270, 600, 50, 200, 10);
        platform (objects, renderer, 1270, 400, 50, 200, 11);
        platform (objects, renderer, -30, 250, 100, 300, 12);
        platform (objects, renderer, 230, 250, 100, 300, 13);
        platform (objects, renderer, 490, 250, 100, 300, 14);
        platform (objects, renderer, 750, 250, 100, 300, 15);
        door (objects, renderer, 75, 175, 80, 40, 16);
    } else if (key == 3) {
        platform (objects, renderer, -30, 1010, 100, 300, 1);
        platform (objects, renderer, 230, 1010, 100, 300, 2);
        spike (objects, renderer, 670, 970, 50, 180, 3);
        platform (objects, renderer, 660, 1010, 100, 200, 4);
        platform (objects, renderer, 980, 1010, 100, 200, 5);
        spike (objects, renderer, 1300, 970, 50, 180, 6);
        platform (objects, renderer, 1290, 1010, 100, 200, 7);
        platform (objects, renderer, 1610, 1010, 100, 200, 8);
        platform (objects, renderer, 1810, 810, 50, 200, 9);
        platform (objects, renderer, 1290, 640, 100, 200, 10);
        platform (objects, renderer, 660, 640, 100, 200, 11);
        platform (objects, renderer, -30, 640, 100, 300, 12);
        spike (objects, renderer, 320, 600, 50, 200, 13);
        platform (objects, renderer, 230, 640, 100, 300, 14);
        door (objects, renderer, 75, 570, 80, 40, 15);
    }
    

}


void init_render_object(t_render_object **texture_object, SDL_Renderer *renderer, char *reference, int x, int y, int height, int weigth) {

    SDL_Surface *temp = IMG_Load(reference);
    (* texture_object)->ObjectTexture = SDL_CreateTextureFromSurface(renderer, temp);

    (* texture_object)->ObjectHitbox.x = x;
    (* texture_object)->ObjectHitbox.y = y;

    (* texture_object)->ObjectHitbox.w = weigth;
    (* texture_object)->ObjectHitbox.h = height;

    SDL_FreeSurface(temp);
    temp = NULL;

}

t_render_object **init_struct_render_objects (int size) {
    t_render_object **temp = (t_render_object **)malloc(sizeof(t_render_object *) * size);
    for (int i = 0; i < size; i++)
        *(temp + i) = (t_render_object *)malloc(sizeof(t_render_object));
    
    return temp;
}

void free_render_object (t_render_object **texture_object) {
    
    SDL_DestroyTexture((* texture_object)->ObjectTexture);
    (* texture_object)->ObjectTexture = NULL;

    free(*texture_object);
    *texture_object = NULL;

}

void render_texture(t_render_object *object, SDL_Renderer *renderer, int x, int y, SDL_Rect clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { x, y, object->ObjectHitbox.w, object->ObjectHitbox.h };
	if( clip.h == clip.w == clip.x == clip.y != 0 ) {
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	}
	SDL_RenderCopyEx( renderer, object->ObjectTexture, &clip, &renderQuad, angle, center, flip );
}

