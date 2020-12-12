// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#include "Player.h"

Player::Player()        // default
{
    playerName = "";
    playerPrice = 0;
    for (int i = 0; i < arrStatsSize; i++)
    {
        stats[i] = 0;
    }
    teamName = "";
    playerPosition = 0;
    positionString = "";
}
Player::Player(string pName, int price, int s[], int sSize, string tName, int position)      // filled
{
    playerName = pName;
    playerPrice = price;
    for (int i = 0; i < sSize; i++)
    {
        stats[i] = s[i];
    }
    teamName = tName;
    setPosition(position);
}
string Player::getName() const          // return player name
{
    return playerName;
}
void Player::setName(string pName)      // change player name
{
    playerName = pName;
}
double Player::getPrice() const         // return player price
{
    return playerPrice;
}
void Player::setPrice(double price)         // change price of player
{
    playerPrice = price;
}
string Player::getTeamName() const          // return team that player is on
{
    return teamName;
}
void Player::setTeamName(string tName)      // change team player is on
{
    teamName = tName;
}
int Player::getPace() const             // return player stat: pace
{
    return stats[0];
}
int Player::getStrength() const         // return player stat: strength
{
    return stats[1];
}
int Player::getShooting() const         // return player stat: shooting
{
    return stats[2];
}
int Player::getPassing() const          // return player stat: passing
{
    return stats[3];
}
int Player::getDefending() const        // return player stat: defedning
{
    return stats[4];
}
int Player::getDribbling() const        // return player stat: dribbling
{
    return stats[5];
}
void Player::setStats(string statLine)      // set stats for the player
{
    string piece;
    int i = 0;
    char seperator = ',';

    for (int j = 0; j < arrStatsSize; j++)                                 // loop throught the size of the array
    {
        while (statLine[i] != seperator && i < statLine.length())          // check to see if a seperator or end of string has been reached
        {
            piece += statLine[i];                                      // adding characters to other string variable - not seperators
            i++;
        }
        stats[j] = stoi(piece);                                  // setting stat index to the string between seperators

        i++;                                                            // moving past string index containing seperator
        piece = "";                                                     // resetting string piece to accept new part of original
    }

}
int Player::getPosition() const          // return position of player
{
    return playerPosition;
}
string Player::getPosString() const     // return string for the player position
{
    return positionString;
}
void Player::setPosition(int position)   // change postion of player
{
    playerPosition = position;
    switch (position)
    {
        case 1: positionString = "Goalkeeper";      // changing the position string based on position int
            break;
        case 2: positionString = "Defender"; 
            break;
        case 3: positionString = "Midefielder"; 
            break;
        case 4: positionString = "Forward"; 
            break;
        default:
            break;
    }
}

void Player::split(string toBeSplit, char seperator, string array[], int arraySize)      // split up file elemnts to be put into object
{
    string piece;
    int i = 0;

    for (int j = 0; j < arraySize; j++)                                 // loop throught the size of the array
    {
        while (toBeSplit[i] != seperator && i < toBeSplit.length())     // check to see if a seperator or end of string has been reached
        {
            piece += toBeSplit[i];                                      // adding characters to other string variable - not seperators
            i++;
        }
        array[j] = piece;                                               // setting array index to the string between seperators

        switch (j)
        {
            case 0: playerName = array[j];                              // setting first piece to name of player
                break;
            case 1: setPosition(stoi(array[j]));                    // setting 2nd piece to position
                break; 
            case 2: playerPrice = stoi(array[j]);                       // third to price of player
                break;
            case 3: teamName = array[j];                                // fourth to the team name
                break;
            case 4: piece = toBeSplit.substr(i - 2, toBeSplit.length() - (i - 2));        // calling set stats to add remaining pieces to stats array
                    setStats(piece);
                break;
            default: return;       // exiting once all pieces are done being assigned
                break;
        }
        i++;                                                            // moving past string index containing seperator
        piece = "";                                                     // resetting string piece to accept new part of original        
    }
}