//
//  Game.hpp
//  ncurses_training
//
//  Created by Duba on 4/29/17.
//  Copyright © 2017 Duba. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

#include <stdio.h>
#include <iostream>
#include<ncurses.h>
#include <time.h>
class Game{
private:
    
        WINDOW *snakeworld;
        int position = 0;
        typedef struct Snake {
        int x = 10,y =10;
        }s;
        bool game = true;
        int tickrate;
        void initField();
        void randApple();
        int sizeSnake;
        int how2timer;
        int speed;
        bool apple = true;
        int apple_x;
        int apple_y;
    
    
    
public:
       
        void controlSnake();   //control
        void appleRand(WINDOW *win);
        enum direction { UP, DOWN, RIGHT, LEFT };
        void move_snakey(WINDOW *win,int direction,
                    s snakey[]);
        void eatApple(s snakey[]);
        void playGame();
        int field[50][25];
        void showSnake();
         void GameOver();
};

#endif /* Game_hpp */
