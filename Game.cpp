//
//  Game.cpp
//  ncurses_training
//
//  Created by Duba on 4/29/17.
//  Copyright © 2017 Duba. All rights reserved.
//

#include "Game.hpp"
#include<iostream>
#include<ncurses.h>

using namespace std;
void Game::initField(){
    for(int x =0;x<50;x++){
        for(int y =0;y<25;y++){
                field[x][y] = 0;
        }
    }
    
    sizeSnake = 4;
     speed = 400;
    
}

void Game::controlSnake(){
    WINDOW *snakeys_world;
    apple = true;
    int offsetx, offsety, i, ch;
    
    initscr();
    noecho();
    cbreak();
    timeout(speed);
    keypad(stdscr, TRUE);
    
    printw("Press x to quit...");
    
    refresh();
    
    offsetx = (COLS - WORLD_WIDTH) / 2;
    offsety = (LINES - WORLD_HEIGHT) / 2;
    
    snakeys_world = newwin(WORLD_HEIGHT,
                           WORLD_WIDTH,
                           offsety,
                           offsetx);
    
    s snakey[300];
    
    int sbegx = (WORLD_WIDTH - sizeSnake) / 2;
    int sbegy = (WORLD_HEIGHT - 1) / 2;
    
    for (i = 0; i < sizeSnake; i++) {
        snakey[i].x = sbegx + i;
        snakey[i].y = sbegy;
    }

    int cur_dir = RIGHT;
    
    while ((ch = getch()) != 'x' && game) {
    
        move_snakey(snakeys_world, cur_dir, snakey);
      
        if(ch != ERR) {
            switch(ch) {
                case KEY_UP:
                    if (cur_dir == DOWN){
                        continue;
                    }
                    cur_dir = UP;
                    break;
                case KEY_DOWN:
                    if (cur_dir == UP){
                        continue;
                    }
                    cur_dir = DOWN;
                    break;
                case KEY_RIGHT:
                    if (cur_dir == LEFT){
                        continue;
                    }
                    cur_dir = RIGHT;
                    break;
                case KEY_LEFT:
                    if(cur_dir == RIGHT){
                        continue;
                    }
                    cur_dir = LEFT;
                    break;
                default:
                    break;
            }
            
        }
    }
    
    delwin(snakeys_world);
    
    endwin();
    
}
void Game::move_snakey(WINDOW *win, int direction, s snakey[300]){
    wclear(win);
    field[snakey[0].x][snakey[0].y] = 0;
    if (apple){
        appleRand(win);
      
    }

  
    for (int i = 0; i < sizeSnake -1; i++) {
        snakey[i] = snakey[i + 1];
        
        mvwaddch(win, snakey[i].y, snakey[i].x, 'O');
        
    }
    int x = snakey[sizeSnake-1].x;
    int y = snakey[sizeSnake-1].y;
    for(int x = 0; x< sizeSnake - 1;x++){
        field[snakey[x].x][snakey[x].y] = 1;
        
    }
    field[snakey[sizeSnake-1].x][snakey[sizeSnake-1].y] = 2;

    
    if (snakey[sizeSnake-1].x == apple_x && snakey[sizeSnake-1].y == apple_y){
        snakey[sizeSnake-1].x = x;
        snakey[sizeSnake-1].y = y;
        apple = true;
        sizeSnake++;
        appleRand(win);
        

        
    }

    switch (direction) {
        case UP:
            if(y - 1 == 0){
                y = WORLD_HEIGHT - 2;
            }
            else {
                y--;
            }
            break;
        case DOWN:
            if (y + 1 == WORLD_HEIGHT - 1 ) {
                y = 1;
            }
            else{
             y++;
            }
            break;
        case RIGHT:
            if(x + 1 == WORLD_WIDTH - 1) {
                x = 1;
            }
            else{
             x++;
            }
            break;
        case LEFT:
            if (x - 1 == 0)  {
                x = WORLD_WIDTH - 2;
            }
            else{
             x--;
            }
            break;
        default:
            break;
    }
   
    snakey[sizeSnake-1].x = x;
    snakey[sizeSnake-1].y = y;
        for(int x = 0; x< sizeSnake - 1;x++){
            if(field[snakey[x].x][snakey[x].y]  ==  field[snakey[sizeSnake-1].x][snakey[sizeSnake-1].y]){
                game = false;
            }
    
        }
 

    mvwaddch(win, y, x, 'O');
    
    mvwaddch(win, apple_y, apple_x, 'A');
    
    noecho();
    move(0,0);
    box(win, 0 , 0);
    how2timer++;
    wrefresh(win);
    
    
    
    
}

void Game::appleRand(WINDOW *win){
    srand(time(NULL));
    mvwaddch(win, apple_y, apple_x, 'O');

    apple_x =rand()%(48 - 3 +1)+3;
    apple_y =rand()%(18 - 3 + 1)+3;
       noecho();
    wrefresh(win);
    apple = false;
}
void Game::GameOver(){
    WINDOW *GameOver;

    initscr();
    noecho();
    cbreak();
    
    printw("GameOver");
    
    refresh();

    getch();
    endwin();
}
void Game::playGame(){
    Game ab;
    ab.initField();
    ab.controlSnake();
    ab.GameOver();
 
}
