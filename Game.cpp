// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#include "Game.h"

Game::Game()      // default
{
    yourScore = 0;
    oppScore = 0;
    gameResult = "tie";
    opponentName = "";
    yourName = "";
}
Game::Game(int yScore, int oScore, string result, string oppName, string yName)        // filled
{
    yourScore = yScore;
    oppScore = oScore;
    gameResult = result;
    opponentName = oppName;
    yourName = yName;
}
int Game::getYourScore() const        // return user's score
{
    return yourScore;
}
void Game::setYourScore(int yScore)       // set user's score
{
    yourScore = yScore;
}
int Game::getOppScore() const             // return opponent's score
{
    return oppScore;
}
void Game::setOppScore(int oScore)        // change opponent's score
{
    oppScore = oScore;
}
string Game::getResult() const        // return result of game (win/loss/tie)
{
    return gameResult;
}
void Game::setResult(string result)       // change the result of the game
{
    gameResult = result;
}
string Game::getOppName() const       // get opponent's team name
{
    return opponentName;
}
void Game::setOppName(string oppName)     // change opponent's team name
{
    opponentName = oppName;
}
string Game::getYourName() const       // get first team's team name
{
    return yourName;
}
void Game::setYourName(string yName)     // change first team's team name
{
    yourName = yName;
}