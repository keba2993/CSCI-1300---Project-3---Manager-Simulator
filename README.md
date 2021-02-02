# CSCI-1300---Project-3---Manager-Simulator

This is a big project that I craeted for my Introductory C++ course at the University of Colorado - Boulder.

I was tasked with creating a decsion based game that incorporated many aspects of C++ and coding such as loops, arrays, classes, objects, file reading and writing, and more.
I wanted to create a game the mimiced FIFA 21's Career mode where the player is essentially simulating being a professional soccer team manager. I did this by first having
the user pick his/her team name, select 11 players for said team, and then the user participated in a "season" made up of 3 games played against simulated opponent's.
The games' results were based off of some factors such as team rank, and tehn there was added randomness to keep each game different from the previous.

At the conclusion of very season the user could play another season, change team name, go into the transfer window, or retire.
Retiring prompted a display of the player's overall stats which included overall team record, and the number of season's won.
Entering the transfer window allowed the user to trade, sell and buy players for their team. THis was a fun part to incorporate.

One issue that would have been nice to fix was developing a scheduling algorithm that allowed for more games to be player per season. This was a challenge because I wanted to have
11 different teams that each played each other only once, but ran into a infinite loop as one team would always be tasked with playing a team they have already played.
