#include<bits/stdc++.h>
#include "game.hpp"


SDL_Texture* bgtex;


Game::Game(){}
Game::~Game(){}
void Game::start(const char* title, int x, int y, int w, int h, bool fs){
    int fullscreen = 0;
    if(fs){
        fullscreen=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        window = SDL_CreateWindow(title, x, y, w, h, fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;

        SDL_Surface * bgsurf = IMG_Load("images/bg.jpeg");
        bgtex = SDL_CreateTextureFromSurface(renderer, bgsurf);
        SDL_FreeSurface(bgsurf);
        player = new Player(0,550,250,250);
        //enemy = new Enemy(200,200,121,121);
        showPlayer=true; isShooting=false;
    }
    else{
        isRunning = false;
    }
}
void Game::event(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning=false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            if(showPlayer){
                player->move(-1);
                player->display(renderer);
            }
            break;
        case SDLK_RIGHT:
            if(showPlayer){
                player->move(1);
                player->display(renderer);
            }
            break;
        case SDLK_DOWN:
            showPlayer=false;
            break;
    }
        
        break;
    case SDL_MOUSEBUTTONDOWN:
        isShooting=true;
        break;

    case SDL_MOUSEBUTTONUP:
        isShooting=false;
        break;

    default:
        break;
    }
    if(event.type==SDL_QUIT){
        isRunning=false;
    }
}
void Game::display(){
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, bgtex,NULL, NULL);
    if(showPlayer)
    player->display(renderer);
    secount++;
    secount=secount%901;
    //cout<<secount<<endl;
    if(secount==900 && ecount<5){
        secount=0;
        ecount++;
        createEnemy();
    }
    pair<int,int> bullet_pos;
    for(auto enemy:enemies){
        if(enemy->isAlive()){
            bullet_pos=enemy->showBullet(player->getX()+100,player->getY()+100,renderer);
            //use this to check collision with player
        }
    }
    
     if(isShooting){
         SDL_GetMouseState(&mx,&my);
         player->shoot(mx,my, renderer);
         
         for(auto enemy=enemies.begin();enemy!=enemies.end();enemy++){
            bool shooted = (*enemy)->shooted(mx,my);
            if(shooted){
                ecount--;
                enemies.erase(enemy--);
            }
         }
     }
    for(auto enemy: enemies){
        if(enemy->isAlive())
            enemy->display(renderer);
    }
        SDL_RenderPresent(renderer);
    
    
}

void Game::createEnemy(){
    int xe,ye;
    srand(time(0));
    xe=rand()%800 + 50;
    ye=rand()%250 + 50;
    Enemy * enemy =new Enemy(xe,ye,121,121);
    enemies.push_back(enemy);
}

void Game::end(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}