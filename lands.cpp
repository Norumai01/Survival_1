#include "lands.h"

using namespace std;

Land* getRandomLand(){
    LandTypes selection = (LandTypes)(rand() % MAX_NUM_LANDS);
    
    switch(selection){
        case LAKE:
            return new Lake;
            break;
        case FOREST:
            return new Forest;
            break;
        case DESERT:
            return new Desert;
            break;
        case NETHER:
            return new Nether;
            break;
        case JUNGLE:
            return new Jungle;
            break;
        case VILLAGE_1:
            return new Village_1;
            break;
        case VILLAGE_2:
            return new Village_2;
            break;
        case VILLAGE_3:
            return new Village_3;
            break;
        default:
            return new Forest;
            break;
    }
    
}

// Lake
string Lake::getShortDescription(){
    return "lake";
}

string Lake::getLongDescription(){
    return "You arrive at a large lake filled with clear sparkling water.";
}

string Lake::visit(Player& p){
    string description = "You drink from the lake, replenishing your thirst for momentarily.";
    p.setThirst(p.getThirst() + 4);
    return description;
}

// Forest
string Forest::getShortDescription(){
    
    return "forest";
}

string Forest::getLongDescription(){
    return "You arrive in dense forest filled with trees and foliage.";
}

string Forest::visit(Player& p){
    string description;
    
    int chance = rand() % 100;
    
    // Chance to find berries
    if(chance > 75){
        description = "You foraged for berries in the forest and found some!";
        p.setHunger(p.getHunger() + 1);
    }
    
    if (chance > 50 && chance < 75 ) {
        description = "During your hunt, you were able to scavaged some meats to survival for the day.";
        p.setHunger(p.getHunger() + 3);
    } 
    
    // Chance to get mauled by a bear or double mauled by two bears
    if ( (chance < 15 && chance > 5) && (p.checkPet() == false) ){ 
        description = "You are attacked by a hungry bear in the woods!";
        p.setHealth(p.getHealth() - 1);
    }
    else if ( (chance < 5) && (p.checkPet() == false) ){    
        description = "You are attacked by two very large bears!";
        int newHealth = (int)p.getHealth() - 3;
        newHealth = newHealth < 0 ? 0 : newHealth;
        p.setHealth(newHealth);
    }
    // Safe from the bear since you have a pet.
    else if ( (chance < 15) && (p.checkPet() == true) ) {
        description = "The bears were hesitated to attack you, and you were left unstratched.";
    }
    // Nothing happened.
    else {
        description = "You forage for berries and went hunting but find nothing.";
    } 
    return description;
}

// Desert
string Desert::getShortDescription(){
    
    return "desert";
}

string Desert::getLongDescription(){
    return "You arrive in a extremely hot, dry desert";
}

string Desert::visit(Player& p){
    string description = "The heat of the desert makes you dehydrated.";
    
    p.setThirst(p.getThirst() - 3);

    return description;
}

// Nether
string Nether::getShortDescription(){
    
    return "nether portal";
}

string Nether::getLongDescription(){
    return "You found what looks to be a portal, decided to stay for a few hours to study it.";
}

string Nether::visit(Player& p){
    string description = "You saw no functionality from the portal and decided to leave.";
    
    int chance = rand() % 100;
    
    // Chances to get attack by creatures or even killed.
    if (chance < 20) {
        description = "Some unknown creature sneaked up behind and dragged you into the portal. You were able to escaped, with minor bruises.";
        p.setHealth(p.getHealth() - 2);
    }
    if (chance < 10 && chance > 3) {
        p.setHealth(0);
    } 

    return description;
}

// Jungle
string Jungle::getShortDescription(){
    
    return "jungle";
}

string Jungle::getLongDescription(){
    return "You found what seems to be a tropical rainforest. The moisture is very thick and it is warm.";
}

string Jungle::visit(Player& p){
    string description;
    p.setHealth(Player::DEFAULT_HEALTH);
    
    int chance = rand() % 100;
    
    
    if ( (chance < 20) && (p.checkPet() == false) ) {
        description = "While exploring, you found a injuried lone wolf. You healed the lone wolf and became the wolf new master. Afterward, you took shelter for the day.";
        p.havePet(1);
    }
    else {
        description = "You decided to take shelter for the day, due the warmness.";
    }

    return description;
}

// Village #1
string Village_1::getShortDescription(){
    
    return "Ruka Town (dangerous)";
}

string Village_1::getLongDescription(){
    return "You went inside a village. The civilians seems wary of your presense.";
}

string Village_1::visit(Player& p){
    string description = "You felt too dangerous to stay in the village, and so you decided to leave.";
    
    int chance = rand() % 100;
    // Chances the village may attack you or meet a nice lady.
    if (chance < 10) {
        description = "Going into the shady village, multiple civilians attacked you and threw you out of the village.";
        p.setHealth(p.getHealth() - 2);
        
        if (p.checkPet() == true) {
            description = "The village hesitated and decided not to attack you because you have a tamed wolf.";
        }
    }
    if (chance < 25 && chance < 10) {
        description = "A nice lady invited and fed you but asked you to leave after staying for dinner, as it is dangerous to stay.";
        p.setHunger(Player::DEFAULT_HUNGER);
        p.setThirst(Player::DEFAULT_THIRST);
    }
    
    return description;
}

// Village #2
string Village_2::getShortDescription(){
    
    return "Lelia City";
}

string Village_2::getLongDescription(){
    return "You went inside the city. The guards at the gate welcomes you. Everyone in city seems busy to pay any attention.";
}

string Village_2::visit(Player& p){
    string description = "You decided to stop by an Inn to rest and recover your health, eat, and filling your thirst for the day..";
    
    // Cleasen your hunger, thirst, health.
    p.setHealth(Player::DEFAULT_HEALTH);
    p.setHunger(Player::DEFAULT_HUNGER);
    p.setThirst(Player::DEFAULT_THIRST);
    
    return description;
}

// Village #3
string Village_3::getShortDescription(){
    
    return "LittleRoot Town";
}

string Village_3::getLongDescription(){
    return "You went inside a small village with only two cabins nearby.";
}

string Village_3::visit(Player& p){
    string description = "There appears to be no one at the village and the cabin were empty. You decided to take shelter for the day, restoring your hp.";
    
    int chance = rand() % 100;
    // Brendon gave you supplies of foods and waters.
    if (chance < 50) {
        description = "Brendon invited you for overnight stay. The next day, Brendon gave you supplies of foods and waters to survival a few more days. You left the village, and thanking Brendon.";
        p.setHealth(p.getHealth() + 5);
        p.setHunger(p.getHunger() + 10);
        p.setThirst(p.getThirst() + 10);
    }
    
    p.setHealth(Player::DEFAULT_HEALTH);
    
    return description;
}
