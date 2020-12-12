// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Team
{
    public:
        Team();     // default
        Team(string name, int index, int rank, int goalsF, int goalsA, bool played[], int playedSize);      // filled
        string getTeamName() const;         // return team name 
        void setTeamName(string name);      // change the team name
        int getTeamRank() const;            // return the team rank
        void setTeamRank(int rank);         // change the team rank
        int getGoalsFor() const;            // return the goals for
        void setGoalsFor(int goalsF);       // change goals for
        int getGoalsAgainst() const;        // return goals against
        void setGoalsAgainst(int goalsA);       // change goals against
        int getWins() const;        // return wins
        void addWin();              // add win
        int getLosses() const;      // return losses
        void addLoss();             // add loss
        int getTies() const;        // return ties
        void addTie();              // add tie
        int getTeamIndex() const;           // return the index of the team
        void setTeamIndex(int index);       // set the index of the team
        bool getPlayedAt(int opp);        // return if a team was already played
        void setPlayedAt(int opp, bool played);  // change if played a certain team

    private:
        string teamName;
        int teamIndex;
        int teamRank;
        int goalsFor;
        int goalsAgainst;
        int wins;
        int losses;
        int ties;
        static const int pAlreadySize = 12;
        bool playedAlready[pAlreadySize];
};

#endif