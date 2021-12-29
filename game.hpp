#ifndef game_hpp
#define game_hpp

#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "player.hpp"
#include "enemy.hpp"
using namespace std;
class Game{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Player* player;
        
        vector<Enemy*> enemies;
        bool isRunning, showPlayer, isShooting;
        int mx,my,ecount=0;
        long secount=0;
    public:
        Game();
        ~Game();
        void start(const char* title,int x, int y, int w, int h, bool fs);
        void event();
        void display();
        void createEnemy();
        void end();
        bool running(){ return isRunning;};
};



#endif