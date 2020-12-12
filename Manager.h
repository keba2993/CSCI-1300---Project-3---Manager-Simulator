// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include "Player.h"
#include "Team.h"

using namespace std;

class Manager
{
    public:
        Manager();      // default
        Manager(string g, string n, Player t[], int tSize, string teamN, int rank, int retire, int r[], int rSize, int titles); // filled
        string getGender() const;                   // return Manager gender
        void setGender(string g);                   // change gender
        string getName() const;                     // return Manager name
        void setName(string n);                     // change name
        bool addPlayer(Player p);                   // add player to team array
        Player getTeamPlayerAt(int pos);                // return player at certain array index
        void setTeamPlayerAt(Player p, int pos);        // put player at certain array index
        string getTeamName() const;                 // return teamName
        void setTeamName(string tName);             // change teamName
        int getRank() const;                        // return the team rank
        void setRank(int rank);                     // update team rank
        int getRetirement() const;                  // return num years before retirement
        void setRetirement(int retire);             // set num years before retired
        void increaseYear();                        // add year to num years before retirement
        int getTitles() const;                      // return number of titles won
        void setTitles(int titles);                 // set number of titles won
        void wonATitle();                           // increase number of won titles
        int getLosses() const;                      // return number of losses for season
        int getTies() const;                        // return number of ties
        int getWins() const;                        // return number of wins
        void addToRecord(string result);            // update record sheet depending on game result
        Team getManagersTeam() const;               // return team object for the manager
        int calcScoreProb();                // calculate the probability of manager's team scoring

    private:
        string gender;
        string name;
        static const int teamSize = 11;
        Player team[teamSize];
        Team yourTeam;
        int numPlayers;
        string teamName;
        int teamRank;
        int retiredAfter;
        static const int recordSize = 3;
        int arrRecord[recordSize];
        int numTitles;
        int scoreProb;
};

#endif

/*  CLASS IDEAS
 *  in Manager class (data members)
 *      - gender
 *      - team (player array)
 *      - team name
 *      - team rank
 *      - retiredAfter
 *      - array for record
 *      - titles (season and UCL)
 *      FUNCTIONS
 *      - set/get gender
 *      - set/get team name
 *      - add player to team
 *      - update record/ get record
 *      - set/get title
 *      - set/get rank
 *      - set/get retiredYear
 *      - year in review
 *  in Player class (data members)
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
 *  in game class (data members)
 *      - score
 *      - win/loss/tie
 *      - type (group stage, knockout, season)
 *      - opponent
 *      FUNCTIONS
 *      - get/set score
 *      - get/set outcome
 *      - get/set type
 *      - get/set opponent
 *  in transfer window class (maybe just a function)
 *      - available players
 *      - budget
 *      FUNCTIONS
 *      - print players
 *      - get/set budget
 *      - get/set available players
 *  in Driver class  ---- dont really understand why I would need this
 *      - players
 *      - manager
 *      - probability of getting to UCL
 *      - set Team
 *      - win probability - ranks and years of coaching considered
*/