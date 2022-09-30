#include "../inc/mainheader.h"

void handleEvent(SDL_Event event, t_player **players) {
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
        switch(event.key.keysym.sym) {
            case SDLK_w:
                if ((*players)->can_jump == false) {
                    (* players)->velocityY = PLAYER__JUMP_HIGH;
                    (* players)->can_jump = true;
                }
                break;
            case SDLK_a:
                (* players)->velocityX -= PLAYER_SPEED;
                (* players)->sprite = MOVING_LEFT;
                break;
            case SDLK_d:
                (* players)->velocityX += PLAYER_SPEED;
                (* players)->sprite = MOVING_RIGHT;
                break;
        }
    } else if ( event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch( event.key.keysym.sym ) {
            case SDLK_a:
                (* players)->velocityX += PLAYER_SPEED;
                (* players)->sprite = IDLE;
                break;
            case SDLK_d:
                (* players)->velocityX -= PLAYER_SPEED;
                (* players)->sprite = IDLE;
                break;
        }
    }
}

bool collision_check( SDL_Rect a , SDL_Rect b )
{
    int lefta , leftb;
    int righta , rightb;
    int topa , topb;
    int bottoma , bottomb;
 
    lefta = a.x;
    righta = a.x + a.w;
    topa = a.y;
    bottoma = a.y + a.h;
 
    leftb = b.x;
    rightb = b.x + b.w;
    topb = b.y;
    bottomb = b.y + b.h;
 
    if( righta <= leftb || lefta >= rightb || bottoma <= topb || topa >= bottomb )
    {
        return false;
    }
 
    return true;
}

void init_player(t_player **player, SDL_Renderer *renderer) {

    (* player)->player_pos.x = 200;
    (* player)->player_pos.y = 900;

    (* player)->player_pos.w = 55;
    (* player)->player_pos.h = 65;
    
    (* player)->can_jump = false;
    (* player)->player_texture = IMG_LoadTexture(renderer, "./resource/characters/Ghost.png");

    (* player)->sprite = IDLE;

}

int check_collisions_and_type_object(SDL_Rect a, t_render_object **objects, int size) {
    for (int i = 1; i < size; i++) {
        if(objects[i]->type_object == PLATFORM)
            if(collision_check(a, objects[i]->ObjectHitbox))
                return i;
    }
    return 0;
}

bool check_collisions_spike(SDL_Rect a, t_render_object **objects, int size) {
    for (int i = 1; i < size; i++) {
        if(objects[i]->type_object == SPIKE)
            if(collision_check(a, objects[i]->ObjectHitbox))
                return true;
    }
    return 0;
}

bool check_collisions_door(SDL_Rect a, t_render_object **objects, int size) {
    for (int i = 1; i < size; i++) {
        if(objects[i]->type_object == DOOR)
            if(collision_check(a, objects[i]->ObjectHitbox))
                return true;
    }
    return 0;
}

bool move(t_player **player, t_render_object **objects, int size, Mix_Chunk *died, Mix_Chunk *tuturu) {
    (* player)->player_pos.x += (* player)->velocityX;

    if ((* player)->player_pos.x < 0 || (* player)->player_pos.x + (* player)->player_pos.w > SCREEN_WIDTH || check_collisions_and_type_object((* player)->player_pos, objects, size)) {
        (* player)->player_pos.x -= (* player)->velocityX;
    }

    (* player)->player_pos.y += (* player)->velocityY;

    int temp = check_collisions_and_type_object((* player)->player_pos, objects, size);

    if (temp && (* player)->velocityY >= GRAVITY)
        (* player)->can_jump = true;

    if (temp) {
        if ((* player)->can_jump && (* player)->velocityY >= 0)
            (* player)->can_jump = false;
        if ((* player)->velocityY > 0) {
            if ((* player)->velocityX >= 0 && (* player)->can_jump) {
                (* player)->player_pos.y -= (* player)->velocityY - (objects[temp]->ObjectHitbox.h % (* player)->velocityY)  - (* player)->velocityX;
            } else {
                (* player)->player_pos.y -= (* player)->velocityY - (objects[temp]->ObjectHitbox.h % (* player)->velocityY) + 2;
            }
        } else if((* player)->velocityY == 0) {
            if ((* player)->velocityX >= 0 && (* player)->can_jump) {
                (* player)->player_pos.y -= (* player)->velocityY - objects[temp]->ObjectHitbox.h % (* player)->velocityX;
            } else {
                (* player)->player_pos.y -= (* player)->velocityY - objects[temp]->ObjectHitbox.h;
            }
        } else {
            (* player)->player_pos.y -= (* player)->velocityY;
        }
        (* player)->velocityY = 0;
    }

    (* player)->velocityY += GRAVITY;

    if ((* player)->player_pos.y > SCREEN_HEIGHT + 50) {
        (* player)->player_pos.y = 920;
        (* player)->player_pos.x = 200;
        Mix_PlayChannel(-1, died, 0);
        (* player)->death_count++;
    }

    if(check_collisions_spike((* player)->player_pos, objects, size)) {
        (* player)->player_pos.y = 920;
        (* player)->player_pos.x = 200;
        Mix_PlayChannel(-1, died, 0);
        (* player)->death_count++;
    }

    if(check_collisions_door((* player)->player_pos, objects, size)) {
        Mix_PlayChannel(-1, tuturu, 0);
        return true;
    }

    return false;

}

void render_player(t_player *player, SDL_Renderer *renderer, int x, int y, SDL_Rect clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, player->player_pos.w, player->player_pos.h };
	if((clip.h != 0) && (clip.w != 0) && (clip.x != 0) && (clip.y != 0 )) {
		renderQuad.w = clip.w;
		renderQuad.h = clip.h;
	    SDL_RenderCopyEx( renderer, player->player_texture, &clip, &renderQuad, angle, center, flip );
	} else {
        SDL_RenderCopyEx( renderer, player->player_texture, NULL, &renderQuad, angle, center, flip );
    }
}
