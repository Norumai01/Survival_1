#include <iostream>
#include <algorithm>
#include <ctime>
#include <time.h>
#include "lands.h"
#include "player.h"

using namespace std;

enum PlayerChoice {NORTH, SOUTH, EAST, WEST};

void clearTerminal(){
    for(int i = 0; i < 20; i++){
        cout << endl;
    }
}

bool getPlayerInput(PlayerChoice &playerChoice){
    // 0 = North, 1 = South, 2 = East, 3 = West
    string input;
    cout << "Which direction will you go?" << endl;
    cout << "Enter N, S, E, or W" << endl;
    cin >> input;
    
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if(input == "n"){
        playerChoice = NORTH;
    } else if(input == "s"){
        playerChoice = SOUTH;
    } else if(input == "e"){
        playerChoice = EAST;
    } else if(input == "w"){
        playerChoice = WEST;
    } else {
        cout << "Invalid input." << endl;
        return false;
    }
    
    return true;
}


int main(){
    
    srand(time(0));     // Randomizing random number generators in the code. 
    
    const int MAP_SIZE = 20;
    unsigned int DAY_COUNTER = 0;
    unsigned int nextY;
    unsigned int prevY;
    unsigned int nextX;
    unsigned int prevX;
    
    Player player(Player::DEFAULT_HEALTH, Player::DEFAULT_HUNGER, Player::DEFAULT_THIRST, MAP_SIZE/2, MAP_SIZE/2);
    
    //Build Map
    Land* map[MAP_SIZE][MAP_SIZE];
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j] = getRandomLand();
        }
    }
    
    cout << "You wake up in a " << map[player.getX()][player.getY()]->getShortDescription() << " with no memory of how you got there." << endl;
        
    while(player.isAlive()){
        
        player.newTurn();
        
        // Give description of surroundings
        unsigned int x = player.getX();
        unsigned int y = player.getY();
        
        // Days you have survived.
        cout << "You have survived " << DAY_COUNTER << " days" << endl;
        
        cout << map[x][y]->getLongDescription() << endl << endl;
        cout << map[x][y]->visit(player) << endl << endl;
        cout << "Location: " << player.getX() << "," << player.getY() << endl;
        
        cout << player.printStats() << endl << endl;
        
        
        // Setting boundary conditions for the surrounding.
        if (player.getY() == 19) {
            nextY = 0;
        }
        else {
            nextY = y + 1;
        }
        
        if (player.getY() == 0) {
            prevY = 19;
        }
        else {
            prevY = y - 1;
        }
        
        if (player.getX() == 19) {
            nextX = 0;
        }
        else {
            nextX = x + 1;
        }
        
        if (player.getX() == 0) {
            prevX = 19;
        }
        else {
            prevX = x - 1;
        }
        
        cout << "To the north you see a " << map[x][nextY]->getShortDescription() << endl;
        cout << "To the south you see a " << map[x][prevY]->getShortDescription() << endl;
        cout << "To the east you see a " << map[nextX][y]->getShortDescription() << endl;
        cout << "To the west you see a " << map[prevX][y]->getShortDescription() << endl;
        
        // Give the direction and let player choose where to move.
        PlayerChoice playerChoice;
        while(!getPlayerInput(playerChoice));
        
        switch(playerChoice){
            case NORTH:
                if (player.getY() == 19) {      //If player go above index 19, they will be put to index 0.
                    player.setY(0);
                }
                else {
                player.setY(player.getY() + 1); 
                }
                break;
            case SOUTH:
                if (player.getY() == 0) {       //If player go below index 0, they will be put to index 19. 
                    player.setY(19);
                } 
                else {
                player.setY(player.getY() - 1);
                }
                break;
            case EAST:
                if (player.getX() == 19) {
                    player.setX(0);
                } 
                else {
                player.setX(player.getX() + 1);    
                }
                break;
            case WEST:
                if (player.getY() == 0) {
                    player.setX(19);
                } 
                else {
                player.setX(player.getX() - 1);
                }
                break;
            default:
                cout << "Invalid input found: " << playerChoice << endl;
                break;
        }
    
    
    // Clearing up the bash terminal.
    clearTerminal();
    
    // Counter for adding User's days of survival.
    DAY_COUNTER++;
    }
    
    // Checks and Announces User's death.
    if (player.getHunger() == 1) {
        cout << "You have survived " << DAY_COUNTER << " days" << endl;
        cout << "User died of hunger." << endl;
    }
    if (player.getHealth() == 1) {
        cout << "You have survived " << DAY_COUNTER << " days" << endl;
        cout << "User's death." << endl;
    }
    if (player.getThirst() == 1) {
        cout << "You have survived " << DAY_COUNTER << " days" << endl;
        cout << "User died of thirst." << endl;
    }
    
    return 0;
}