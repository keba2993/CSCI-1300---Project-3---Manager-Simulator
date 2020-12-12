// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "Manager.h"
#include "Player.h"
#include "Game.h"
#include "Team.h"

using namespace std;

// IT IS IMPORTANT TO NOTE THAT MORE FUNCTIONS MAY BE ADDED AS NEEDED IN THE FUTURE.
// I AM HAVING A HARD TIME FULLY THINKING THROUGH EVERY ASPECT OF MY GAME TO FULLY WRITE OUT EVERY SINGLE FUNCTION
// TAKING BITS AND PIECES AT A TIME :)

class Simulation
{
    public:
        Simulation();       // default
        Simulation(Manager u, Player allP[], int allPSize, Game season[], int seasonSize, Team teams[], int teamsSize, int mB); // filled
        void managerSetUp();     // function to initiate set up of manager object
        void playerSelect(int pos, int number, int min, int max);      // process to selet players at given position
        void setBudget(int money);      // set the budget for the manager
        int getBudget() const;          // retrun budget of manager
        void displayGenderMenu() const;      // displays a menu for user to select gender
        void displayTeamNames() const;      // displays list of available teamNames
        void readTeamNames(string fileName);     // read in team neams from file
        void printAllPlayers(int pos);         // print out all for certain position
        void readAllPlayers(string fileName);       // read in all players from file
        Player getPlayerAt(int choice);       // returns the player at certain index of allPlayers array
        void printManagerInfo();          // printing all of the managers information
        void runSeason();               // initiate the start of a season
        void runTransferWindow();       // simulate the transfer window part of game*
        void runGame(int gameNum);             // simulate a game for the manager's team
        vector<Team> updateRankings();      // update the rankings for all teams
        void printLeaderBoard(vector<Team> teamsVector);        // print leaderboard to terminal
        void displayOtherGames(Game games[], int numGames);       // print out the scores of the other games
        void managerRetires(Manager u);             // retirement of manager - end of game*
        void fullResetAfterSeason();            // resetting all data members back to original before next season

    private:
        static const int playersSize = 85;
        static const int seasonS = 11;
        static const int arrTeamSize = 12;
        static const int arrTeamNSize = 30;
        Manager user;
        Player allPlayers[playersSize];
        Game arrSeason[seasonS];
        Team arrTeams [arrTeamSize];
        string arrTeamNames[arrTeamNSize];
        int managerBudget;
};

#endif


/*  in Driver class  ---- dont really understand why I would need this
 *      - players
 *      - manager
 *      - probability of getting to UCL
 *      - set Team
 *      - win probability - ranks and years of coaching considered
*/