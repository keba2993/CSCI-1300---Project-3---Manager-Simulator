// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Game
{
    public:
        Game();     // default
        Game(int yScore, int oScore, string result, string oppName, string yName);       // filled
        int getYourScore() const;       // return user's score
        void setYourScore(int yScore);      // set user's score
        int getOppScore() const;            // return opponent's score
        void setOppScore(int oScore);       // change opponent's score
        string getResult() const;       // return result of game (win/loss/tie)
        void setResult(string result);      // change the result of the game
        string getOppName() const;      // get opponent's team name
        void setOppName(string oppName);    // change opponent's team name
        string getYourName() const;      // get first team's team name
        void setYourName(string yName);    // change first team's team name

    private:
        int yourScore;
        int oppScore;
        string gameResult;
        string opponentName;
        string yourName;
};

#endif


/*  in game class (data members)
 *      - score
 *      - win/loss/tie
 *      - type (group stage, knockout, season)
 *      - opponent
 *      FUNCTIONS
 *      - get/set score
 *      - get/set outcome
 *      - get/set type
 *      - get/set opponent
*/