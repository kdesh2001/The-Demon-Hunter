#include<bits/stdc++.h>
#include "player.hpp"

Player::Player(int xg, int yg, int h, int w){
    destR.h=h; destR.w=w;
    destR.x=xg; destR.y=yg;
    x=xg; y=yg;
}
void Player::display(SDL_Renderer* renderer){
    SDL_Surface * playersurf = IMG_Load("images/player.png");
    playertex = SDL_CreateTextureFromSurface(renderer, playersurf);
    SDL_FreeSurface(playersurf);
    if(x<=375)
        SDL_RenderCopyEx(renderer, playertex,NULL, &destR,-20,NULL,SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(renderer, playertex,NULL, &destR,20,NULL,SDL_FLIP_HORIZONTAL);
}
void Player::move(int dir){
    if(destR.x + dir*10 >=0 && destR.x + dir*10 <=750){
        destR.x+=dir*10;
        x+=dir*10;
    }
    //display(renderer);
}
void Player::shoot(int x, int y, SDL_Renderer* renderer){
    SDL_Surface * shootsurf = IMG_Load("images/shoot.png");
    shoottex = SDL_CreateTextureFromSurface(renderer, shootsurf);
    SDL_FreeSurface(shootsurf);
     SDL_Rect destRsh;
     destRsh.h=60; destRsh.w=60;
     destRsh.x=x-30; destRsh.y=y-30;
    SDL_RenderCopy(renderer, shoottex,NULL, &destRsh);
    
}

bool Player::shooted(int xb, int yb, SDL_Renderer* renderer){
    int cx=x+64, cy=y+125;
    if(xb>cx-20 && xb<cx+20 && yb>cy-20 && yb<cy+20){
        health-=50;
        if(health<=0){
            
            return false;
        }
        
    }
    return true;

}

void Player::setScore(int s){
    score = s;
}

int Player::getScore(){
    return score;
}
int Player::getX(){
    return x;
}
int Player::getY(){
    return y;
}
int Player::getHealth(){
    return health;
}