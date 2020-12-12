// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#include "Team.h"

Team::Team()      // default
{
    teamName = "";
    teamIndex = 0;
    teamRank = 0;
    goalsFor = 0;
    goalsAgainst = 0;
    wins = 0;
    losses = 0;
    ties = 0;
    for (int i = 0; i < pAlreadySize; i++)
    {
        playedAlready[i] = false;
    }
}
Team::Team(string name, int index, int rank, int goalsF, int goalsA, bool played[], int playedSize)       // filled
{
    teamName = name;
    teamIndex = index;
    teamRank = rank;
    goalsFor = goalsF;
    goalsAgainst = goalsA;
    for (int i = 0; i < playedSize; i++)
    {
        playedAlready[i] = played[i];
    }
    for (int j = playedSize; j < pAlreadySize; j++)
    {
        playedAlready[j] = 0;
    }
}
string Team::getTeamName() const          // return team neam
{
    return teamName;
}
void Team::setTeamName(string name)       // change the team name
{
    teamName = name;
}
int Team::getTeamRank() const             // return the team rank
{
    return teamRank;
}
void Team::setTeamRank(int rank)          // change the team rank
{
    teamRank = rank;
}
int Team::getGoalsFor() const             // return the goals for
{
    return goalsFor;
}
void Team::setGoalsFor(int goalsF)        // change goals for
{
    goalsFor = goalsF;
}
int Team::getGoalsAgainst() const         // return goals against
{
    return goalsAgainst;
}
void Team::setGoalsAgainst(int goalsA)        // change goals against
{
    goalsAgainst = goalsA;
}
int Team::getWins() const        // return wins
{
    return wins;
}
void Team::addWin()              // add win
{
    wins++;
}
int Team::getLosses() const      // return losses
{
    return losses;
}
void Team::addLoss()             // add loss
{
    losses++;
}
int Team::getTies() const        // return ties
{
    return ties;
}
void Team::addTie()              // add tie
{
    ties++;
}
int Team::getTeamIndex() const           // return the index of the team
{
    return teamIndex;
}
void Team::setTeamIndex(int index)       // set the index of the team
{
    teamIndex = index;
}
bool Team::getPlayedAt(int opp)         // return if a team was already played
{
    return playedAlready[opp];
}
void Team::setPlayedAt(int opp, bool played)   // change if played a certain team
{
    playedAlready[opp] = played;
}