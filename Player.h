// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Player
{
    public:
        Player();       // default
        Player(string pName, int price, int s[], int sSize, string tName, int position);     // filled
        string getName() const;         // return player name
        void setName(string pName);     // change player name
        double getPrice() const;        // return player price
        void setPrice(double price);        // change price of player
        string getTeamName() const;         // return team that player is on
        void setTeamName(string tName);     // change team player is on
        int getPace() const;            // return player stat: pace
        int getStrength() const;        // return player stat: strength
        int getShooting() const;        // return player stat: shooting
        int getPassing() const;         // return player stat: passing
        int getDefending() const;       // return player stat: defedning
        int getDribbling() const;       // return player stat: dribbling
        void setStats(string statLine);     // set stats for the player
        int getPosition() const;         // return position of player
        string getPosString() const;     // return string for the player position
        void setPosition(int position);  // change postion of player
        void split(string toBeSplit, char seperator, string array[], int arraySize);  // split up file elements

    private: 
        string playerName;
        int playerPrice;
        static const int arrStatsSize = 6;
        int stats[arrStatsSize];
        string teamName;
        int playerPosition;
        string positionString;
};

#endif


/* in Player class (data members)
 *      - name
 *      - array of stats
 *      - price
 *      - //injury Probability
 *      - //red card propbability
 *      - team name
 *      FUNCTIONS
 *      - get/set name
 *      - get/set stats
 *      - get/set price
 *      - calcis injured
 *      - calc is carded
 *      - get/set team name
*/