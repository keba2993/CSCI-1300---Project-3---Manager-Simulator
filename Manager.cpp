// CS1recordSize00 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project recordSize

#include "Manager.h"

Manager::Manager()      // default
{
    gender = "";
    name = "";
    teamName = "";
    
    for (int i = 0; i < teamSize; i++)
    {
        team[i] = Player();
    }
    numPlayers = 0;
    
    teamRank = 0;
    retiredAfter = 0;

    for (int j = 0; j < recordSize; j++)
    {
        arrRecord[j] = 0;
    }

    numTitles = 0;
    yourTeam = Team();
} 
Manager::Manager(string g, string n, Player t[], int tSize, string teamN, int rank, int retire, int r[], int rSize, int titles)     // filled
{
    gender = g;
    name = n;
    teamName = teamN;
    for (int i = 0; i < tSize; i++)
    {
        team[i] = t[i];
    }
    if (tSize <= teamSize)
    {
        numPlayers = tSize;
    }
    teamRank = rank;
    retiredAfter = retire;
    for (int j = 0; j < rSize; j++)
    {
        arrRecord[j] = r[j];
    }

    numTitles = titles;
    yourTeam = Team();
} 
string Manager::getGender() const       // return Manager gender
{
    return gender;
} 
void Manager::setGender(string g)       // change gender
{
    gender = g;
}
string Manager::getName() const         // return Manager name
{
    return name;
}
void Manager::setName(string n)         // change name
{
    name = n;
}
bool Manager::addPlayer(Player p)       // add player to team array
{
    if (numPlayers < teamSize)
    {
        for (int i = 0; i < teamSize; i++)      // checking if player is already in the team
        {
            if(p.getName() == team[i].getName())
            {
                return false;           // player was not added
            }
        }
        team[numPlayers] = p;           // adding player in available space
    }
    numPlayers++;                       // incrementing numPlayers
    return true;                        // returning that player was added
} 
Player Manager::getTeamPlayerAt(int pos)        // return player at certain array index
{
    return team[pos];
} 
void Manager::setTeamPlayerAt(Player p, int pos)        // put player at certain array index
{
    for (int i = 0; i < teamSize; i++)
    {
        if (p.getName() == team[i].getName() && p.getName() != "")
        {
            return;
        }
    }
    team[pos] = p;
} 
string Manager::getTeamName() const         // return teamName
{
    return teamName;
}
void Manager::setTeamName(string tName)     // change teamName
{
    teamName = tName;
    yourTeam.setTeamName(teamName);
    yourTeam.setTeamIndex(0);
    yourTeam.setPlayedAt(0,true);
} 
int Manager::getRank() const        // return the team rank
{
    return teamRank;
} 
void Manager::setRank(int rank)     // update team rank
{
    teamRank = rank;
    yourTeam.setTeamRank(rank);
} 
int Manager::getRetirement() const      // return num years before retirement
{
    return retiredAfter;
}
void Manager::setRetirement(int retire)     // set num years before retired
{
    retiredAfter = retire;
}
void Manager::increaseYear()        // add year to num years before retirement 
{
    retiredAfter++;
}
int Manager::getTitles() const      // return number of titles won
{
    return numTitles;
} 
void Manager::setTitles(int titles)     // set number of titles won 
{
    numTitles = titles;
}
void Manager::wonATitle()           // increase number of won titles
{
    numTitles++;
} 
int Manager::getLosses() const      // return number of losses for season
{
    return arrRecord[1];
}
int Manager::getTies() const        // return number of ties
{
    return arrRecord[2];
}
int Manager::getWins() const        // return number of wins
{
    return arrRecord[0];
}
void Manager::addToRecord(string result)        // update record sheet depending on game result
{
    if (result == "win")            // incrementing number of wins
    {
        arrRecord[0]++;
    }
    else if (result == "loss")      // incrementing a loss
    {
        arrRecord[1]++;             
    }       
    else if (result == "tie")       // incrementing for a tie
    {
        arrRecord[2]++;
    }
}
Team Manager::getManagersTeam() const               // return team object for the manager
{
    return yourTeam;
}
int Manager::calcScoreProb()                // calculate the probability of manager's team scoring
{
    int sumPace = 0, sumStrength = 0, sumShooting = 0, sumPassing = 0, sumDefending = 0, sumDribbling = 0;
    for (int i = 0; i < teamSize; i++)                  // looping through each player in Manager's team
    {
        for (int j = 0; j < 6; j++)                     // looping through each stat of each player
        {
            switch (j)                                              // checking which stat is currently being used
            {
                case 0: sumPace += team[i].getPace();               // adding to sum of respective stat
                    break;
                case 1: sumStrength += team[i].getStrength();
                    break;
                case 2: sumShooting += team[i].getShooting();
                    break;
                case 3: sumPassing += team[i].getPassing();
                    break;
                case 4: sumDefending += team[i].getDefending();
                    break;
                case 5: sumDribbling += team[i].getDribbling();
                    break;
                default:
                    break;
            }
        }
    }
    sumPace = sumPace / 11;                 // taking average of all stats individually - wieghted average for score probability
    sumPassing = sumPassing / 11;
    sumStrength = sumStrength / 11;
    sumShooting = sumShooting / 11;
    sumDefending = sumDefending / 11;
    sumDribbling = sumDribbling / 11;

    // calculating score probability based on player stats for Manager's team
    scoreProb = (int) ((sumPace * 0.05) + (sumStrength * 0.05) + (sumShooting * 0.35) + (sumPassing * 0.2) + (sumDefending * 0.34) + (sumDribbling * 0.01)) / 6;
    return scoreProb;
}