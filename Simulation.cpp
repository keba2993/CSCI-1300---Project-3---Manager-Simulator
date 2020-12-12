// CS1300 Fall 2020
// Author: Kevin Barone
// Recitation: 217 - Maria Stull
// Project 3

#include "Simulation.h"

// IT IS IMPORTANT TO NOTE THAT MORE FUNCTIONS MAY BE ADDED AS NEEDED IN THE FUTURE.
// I AM HAVING A HARD TIME FULLY THINKING THROUGH EVERY ASPECT OF MY GAME TO FULLY WRITE OUT EVERY SINGLE FUNCTION
// TAKING BITS AND PIECES AT A TIME :)

Simulation::Simulation()        // default
{
    user = Manager();
    for (int i = 0; i < seasonS; i++)
    {
        arrSeason[i] = Game();
    }
    for (int j = 0; j < arrTeamSize; j++)
    {
        arrTeams[j] = Team();
    }
    for (int k = 0; k <  playersSize; k++)
    {
        allPlayers[k] = Player();
    }
    managerBudget = 20000;
} 
Simulation::Simulation(Manager u, Player allP[], int allPSize, Game season[], int seasonSize, Team teams[], int teamsSize, int mB)      // filled
{
    user = u;
    for (int i = 0; i < seasonSize; i++)
    {
        arrSeason[i] = season[i];
    }
    for (int j = 0; j < teamsSize; j++)
    {
        arrTeams[j] = teams[j];
    }
    for (int k = 0; k < allPSize; k++)
    {
        allPlayers[k] = allP[k];
    }
    managerBudget = mB;
} 
void Simulation::managerSetUp()           // function to initiate set up of manager object
{
    // getting name, gender, and team name for user playing as manager object
    string uName = "", uGender = "";        // varaibles for gender and name
    int genderChoice = 0;                   // int for gender choice
    cout << "Welcome to the Soccer Manager Simulation! Before we get started, what is you name?" << endl;       // intro message asking for name
    getline(cin, uName);        // setting name to the user's manager object
    user.setName(uName);

    do
    {
        cout << endl << "Hello " << user.getName() << "! The next step is to select your gender (input the number):" << endl;     // asking for choice of gender
        displayGenderMenu();                // displaying gender choice ooptions
        getline(cin, uGender);                  // evaluating what choice is chosen and setting gender of manager object
        genderChoice = stoi(uGender);
        switch (genderChoice)
        {
            case 1: user.setGender("Male");
                break;
            case 2: user.setGender("Female");
                break;
            case 3: user.setGender("Other");
                break;
            default: cout << endl << "Invalid input." << endl;     // making sure a proper choice is chosen
                genderChoice = -1;
                break;
        }
    } while (genderChoice == -1);

    cout << endl << "Your gender choice: " << user.getGender() << endl << endl;

    string teamStr;         // hold string of team selection
    ifstream tNfile;        // file of team names
    int teamChoice = 0;     // int for choice form user
    int lineCount = 30;     // number of lines in file
    readTeamNames("teamNames.txt");     // reading names into array in simulation object
    displayTeamNames();         // displaying all team names in file
    cout << endl << "It is now time to choose what team you want to manage. Choose a number from the list above:" << endl;       // prompting user to choose 

    do
    {
        getline(cin, teamStr);              // capturing user input
        teamChoice = stoi(teamStr);         // converting to integer choice
        tNfile.open("teamNames.txt");       // opening file
        for (int i = 0; i < lineCount; i++)         // looping through all lines of file
        {
            getline(tNfile, teamStr);               // assigning line of file to string variable
            if (i == teamChoice  - 1)               // does it match the team that is chosen
            {
                user.setTeamName(teamStr);             // setting chosen team name to manager object
            }
        }

        if (user.getTeamName() == "")          // checking if there was a valid option chosen                 
        {
            cout << endl << "Invalid input. Please choose again:" << endl;      // error message and redisplaying of team names
            displayTeamNames();
            teamChoice = -1;
            tNfile.close();
        }
    } while (teamChoice == -1);         // looping till valid input is in

    cout << "You chose to manage " << user.getTeamName() << ". Great choice!" << endl << endl;

    // end of manager name, gender, team name set up

    // selecting goalkeeper (number = 2, pos = 1)
    readAllPlayers("players.txt");          // reading all players from file into array
    printAllPlayers(1);                     // printing all available goalkeepers
    cout << "You are almost ready to start the season! Last step is to pick your players!" << endl
        << "You have a budget of $" << getBudget() << ". Keep in mind that you must save enough money to buy 11 players!" << endl
        << "Let's start with a Goalkeeper! Choose a number to select that goalkeeper as your own:" << endl;
    playerSelect(1,1,75,85);        // initiating selection for goalkeeper

    // selecting four defenders (number = 4, pos = 2)
    cout << "Let's now look at the available defenders for your squad!" << endl << endl;
    printAllPlayers(2);             // printing all avaiable defenders
    cout << "Select a defender by number then hit enter. You will do this four seperate times. (<number> <enter> x4)" << endl;
    playerSelect(2,4,50,75);        // selection of defenders

    // selecting three midfielders (number = 3, pos = 3)
    cout << "It is now time to choose your midfielders! You know the drill!" << endl << endl;
    printAllPlayers(3);             // printing all available midfielders
    cout << "Select a midfielder by number then hit enter. You will do this three seperate times. (<number> <enter> x3)" << endl;
    playerSelect(3,3,25,50);        // selection of midfielders

    // selecting three forwards (number = 3, pos = 4)
    cout << "Last but obviously not least is the forwards! I hope you saved some money." << endl << endl;
    printAllPlayers(4);             // printing all forwards taht are available
    cout << "Select a forward by number then hit enter. You will do this three seperate times. (<number> <enter> x3)" << endl;
    playerSelect(4,3,0,25);         // selection of forwards

    printManagerInfo();             // printing manager info
}
void Simulation::playerSelect(int pos,int number, int min, int max)      // process to selet players at given position
{
    // player selection process
    
    string playerChoice = "";           // variables to aid this process
    int intPChoice = 0;
    bool playerAdded = true;

    while(number != 0)              // looping until no more players are to be chosen           
    {
        cout << "You have " << number << " more player(s) to choose for this position: " << endl;       // how many players the user has left
        getline(cin, playerChoice);
        intPChoice = stoi(playerChoice) - 1;
        if (allPlayers[intPChoice].getPrice() > getBudget())
        {
            cout << "This player is outside of your budget." << endl;
        }
        if (intPChoice >= min && intPChoice < max)                      // is the number a valid option for current position
        {
            playerAdded = user.addPlayer(getPlayerAt(intPChoice));      // adding player to user team
            if (playerAdded)                                            // checking if player was added
            {
                setBudget(getBudget() - getPlayerAt(intPChoice).getPrice());
                cout << endl << "You chose " << getPlayerAt(intPChoice).getName() << endl       // calculating new budget and printing chosen player
                    << "Your budget is now $" << getBudget() << endl << endl;
                number--;       // decrementing number of players to be chosen
            }
            else
            {
                cout << "Player is already on your team. Please choose a different number." << endl;    // error if player is already in user's team
            }
        }
        else
        {
            cout << endl << "Invalid input. Please retry." << endl;        // not valid option number chosen
        }
    }
}
void Simulation::setBudget(int money)      // set the budget for the manager
{
    managerBudget = money;
}
int Simulation::getBudget() const          // return budget of manager
{
    return managerBudget;
}
void Simulation::displayGenderMenu() const         // displays a menu for user to select gender
{
    cout << "1 - Male" << endl
        << "2 - Female" << endl
        << "3 - Other" << endl;
}
void Simulation::displayTeamNames() const       // displays list of available teamNames
{
    for (int i = 1; i < arrTeamNSize + 1; i++)
    {
        cout << i << " - " << arrTeamNames[i - 1] << endl;
    }
}
void Simulation::readTeamNames(string fileName)           // read in team names from file
{
    ifstream tNfile;
    string currentName;
    tNfile.open(fileName);
    for (int i = 0; i < arrTeamNSize; i++)          // looping until teamName array is full
    {
        getline(tNfile, currentName);               // retreiving line form file
        if (currentName != "")
        {
            arrTeamNames[i] = currentName;
        }
    }
}
void Simulation::printAllPlayers(int pos)         // print out all players
{
    for (int i = 0; i < playersSize; i++)
    {
        if (allPlayers[i].getPosition() == pos)     // making sure the postion matches the position being printed
        {
            if (allPlayers[i].getPrice() <= managerBudget)      // only players the manager can buy
            {
                cout << i + 1 << " - " << allPlayers[i].getName() << setw(12) << "Price: $" << allPlayers[i].getPrice() << endl
                    << setw(14) << "Postion: " << allPlayers[i].getPosString() << setw(14) << " Team Name: " << allPlayers[i].getTeamName() << endl
                    << setw(11) << "Pace: " << allPlayers[i].getPace() << setw(26) << " Strength: " << allPlayers[i].getStrength() << endl
                    << setw(15) << "Shooting: " << allPlayers[i].getShooting() << setw(21) << " Passing: " << allPlayers[i].getPassing() << endl
                    << setw(16) << "Defending: " << allPlayers[i].getDefending() << setw(22) << "Dribbling: " << allPlayers[i].getDribbling() << endl << endl;
            }
        }
    }
}
void Simulation::readAllPlayers(string fileName)       // read in all players from file
{
    ifstream playersFile;
    string playerLine;
    string arr[10];
    Player temp;
    playersFile.open(fileName);
    for (int i = 0; i <  playersSize; i++)          // looping trhough file until end of array
    {
        getline(playersFile, playerLine);
        temp.split(playerLine, ',', arr, 5);        // splitting the line into different player data members
        allPlayers[i] = temp;                       // adding player temp to array
    }
}
Player Simulation::getPlayerAt(int choice)       // returns the player at certain index of allPlayers array
{
    return allPlayers[choice];
}
void Simulation::printManagerInfo()           // printing all of the managers information
{
    cout << endl << "Here is your updated Manager Information:" << endl << endl;
    cout << user.getName() << " (" << user.getGender() << ")" << setw(16) << "Titles won: " << user.getTitles() << endl
        << "Team: " << user.getTeamName() << setw(10) << "Rank: " << user.getRank() << endl
        << "Team Record (W/L/T): " << user.getWins() << "/" << user.getLosses() << "/" << user.getTies() << endl
        << endl << "Players: " << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << user.getTeamPlayerAt(i).getName() << endl;
    }
}
void Simulation::runSeason()               // initiate the start of a season
{
    srand(time(NULL));
    cout << endl << "You are now ready to start the season. You will play 3 games against 3 different teams!" << endl // -> wanted to do full 11 games but can't figure out algorithm
        << "The leaderboard for the season (found in 'leaderboard.txt') will be updated after every game! Open it up now!" << endl
        << "This is where you will see not only your rank, wins, losses, ties, goals for, and goals against but also those of the the other teams!" << endl
        << "Feel free to reference this at anytime to stay up to date on the season rankings!" << endl;
    user.setRank(5);  // setting manager's team rank to 5

    arrTeams[0] = user.getManagersTeam();               // setting up arrTeams for the season
    for (int j = 1; j < arrTeamSize; j++)
    {
        bool teamExist = false;
        int teamNumber = rand() % arrTeamNSize;         // random team from array
        for (int i = 0; i < arrTeamSize; i++)           // looping through array of teams already picked
        {
            if (arrTeamNames[teamNumber] == arrTeams[i].getTeamName())      // checking if the team already has been picked
            {
                teamExist = true;
                j--;
            }
        } 
        if (!teamExist)                     // making sure the team is not already in array
        {  
            arrTeams[j].setTeamName(arrTeamNames[teamNumber]);      // setting team name into array
            arrTeams[j].setTeamIndex(j);                            // setting team index
            arrTeams[j].setPlayedAt(j, true);                       // making sure they can't play themselves

            if (j == 5)                            // setting the team's rank - Manager's team rank is always 5
            {
                arrTeams[j].setTeamRank(12);
            }
            else
            {
                arrTeams[j].setTeamRank(j);
            }   
        }                        
    }

    updateRankings();               // calling to update rankings

    int gameNumber = 1; 
    string start;
    while (gameNumber != 4)                     // running until three games are played
    {
        cout << endl << "Are you ready to run game #" << gameNumber << "? (Y/N)" << endl;       // asking if they want to initiate game
        cin >> start;
        if (start == "y" || start == "Y")
        {
            runGame(gameNumber);                // initiating game based on game number
            gameNumber++;                       // incrementing game number
        }
        else if (start == "n" || start == "N")                                                  // not initiating game
        {
            cout << endl << "You decided to let your players rest. Lets hope the weather is good next week!" << endl;
        }
        else
        {
            cout << endl << "Invalid input." << endl;          // invalid input
        }
    }
    
    setBudget(getBudget() + ((12 - user.getRank()) * 100));         // giving the user more budget based on the season rank

    // did manager rank 1?
    if (user.getRank() == 1)
    {
        cout << endl << "Congrajulations! You came 1st for the season! " << endl;       // add title to manager object
        user.wonATitle();
    }
    cout << endl << "The season has ended! Your final stats are:" << endl                       // printing out stats of user's team after all games
        << "Rank: " << arrTeams[0].getTeamRank() << " out of " << arrTeamSize << endl
        << "Number of wins: " << arrTeams[0].getWins() << endl
        << "Number of losses: " << arrTeams[0].getLosses() << endl
        << "Number of ties: " << arrTeams[0].getTies() << endl
        << "Goals for: " << arrTeams[0].getGoalsFor() << endl
        << "Goals against: " << arrTeams[0].getGoalsAgainst() << endl << endl;

    user.increaseYear();        // increasing years of retirement

    int postSeasonChoice = 0;
    while (postSeasonChoice == 0)
    {
        cout << "How would you like to continue: " << endl          // asking if user wants to retire or continue playing
            << "1 - enter transfer window" << endl
            << "2 - enter next season" << endl
            << "3 - retire" << endl;
        cin >> postSeasonChoice;

        switch (postSeasonChoice)
        {
            case 1: runTransferWindow();        // enter transfer window
                break;
            case 2: fullResetAfterSeason();     // reset season stats
                    runSeason();                // run next season
                break;
            case 3: managerRetires(user);           // run retirement function - need to make
                break;
            default: cout << endl << "Invalid input." << endl;      // error
                    postSeasonChoice = 0;
                break;
        }
    }

}
void Simulation::runTransferWindow()        // simulate the transfer window part of game
{
    int tWChoice = 0;
    do 
    {
        bool leave = false, added = false;                 // variables used in different transfer window options
        string continueBuy = "Y";
        Player hold = Player();
        int yourPlayerChoice = 0, newPlayerChoice = 0;
        int posOfPlayer = 0;
        int min = 0, max = 0;
        int buyChoice = 0, posHold = 0;
        int newTeamChoice = 0;
        string buyingA = "";
        cout << endl << "============  Transfer Window Options  ============" << endl       // transfer window menu
            << "1 - trade a player" << endl
            << "2 - buy a player" << endl
            << "3 - sell a player" << endl
            << "4 - change team name" << endl
            << "5 - view your budget" << endl
            << "6 - exit and start next season" << endl;
        cin >> tWChoice;
        leave = false;
        // must leave transfer window with 11 playersS
        // can not buy player if team has 11 already
        switch (tWChoice)
        {
            case 1: cout << endl << "You must trade a player from your team for an available player of the same position." << endl      // chose trade
                        << "First step is to choose which player of yours you wish to trade:" << endl << endl;
                    for (int i = 0; i < 11; i++)            // printing out manager's players
                    {
                        cout << i + 1 << " - " << user.getTeamPlayerAt(i).getName() << endl;
                    }
                    while (yourPlayerChoice == 0)           // looping until valid input
                    {
                        cout << endl << "Choose a player to trade (enter -1 to cancel):" << endl;       // choose player to sell from team
                        cin >> yourPlayerChoice;
                        if (yourPlayerChoice == -1)
                        {
                            leave = true;       // wants to cancel action
                            break;
                        }
                        else if (yourPlayerChoice > 0 && yourPlayerChoice <= 11)
                        {
                            cout << endl << "You removed " << user.getTeamPlayerAt(yourPlayerChoice - 1).getName() << " from your team." << endl;   // who got removed
                            setBudget(getBudget() + user.getTeamPlayerAt(yourPlayerChoice - 1).getPrice());     // adding money back to budget
                            posOfPlayer = user.getTeamPlayerAt(yourPlayerChoice - 1).getPosition();             // capturing player position
                            hold = user.getTeamPlayerAt(yourPlayerChoice - 1);                                  // holding player incase user cancels later
                            user.setTeamPlayerAt(Player(), yourPlayerChoice - 1);                               // setting player at index to empty object
                        }
                        else 
                        {
                            cout << endl << "Invalid input." << endl;
                            yourPlayerChoice = 0;
                        }
                    }

                    if (!leave)
                    {
                        switch (posOfPlayer)                    // assigning max and min ranges based on position of player sold
                        {
                            case 1: min = 75;
                                    max = 85;
                                break;
                            case 2: min = 50;
                                    max = 75;
                                break;
                            case 3: min = 25;
                                    max = 50;
                                break;
                            case 4: min = 0;
                                    max = 25;
                                break;
                        }

                        cout << endl << "Now you can decide which player to trade for (your budget will be updated appropriately):" << endl
                            << "Your current budget is $" << getBudget() << endl << endl;               // asking for them to choose their new player
                        printAllPlayers(posOfPlayer);
                        while (newPlayerChoice == 0)
                        {
                            cout << endl << "Choose a new player (enter - 1 to cancel):" << endl;
                            cin >> newPlayerChoice;
                            if (newPlayerChoice == -1)
                            {
                                setBudget(getBudget() - hold.getPrice());               // if user wants to cancel sold player is reset to team
                                user.setTeamPlayerAt(hold, yourPlayerChoice - 1);
                                leave = true;
                                break;
                            }
                            if (!leave)
                            {
                                if (allPlayers[newPlayerChoice - 1].getPrice() > getBudget())
                                {
                                    cout << "This player is outside of your budget." << endl;
                                    newPlayerChoice = 0;
                                }
                                else if (newPlayerChoice > min && newPlayerChoice <= max)                      // is the number a valid option for current position
                                {
                                    user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), yourPlayerChoice - 1);               // capturing player choice
                                    if (user.getTeamPlayerAt(yourPlayerChoice - 1).getName() == getPlayerAt(newPlayerChoice - 1).getName())     // checking if player is already in team                                           // checking if player was added
                                    {
                                        setBudget(getBudget() - getPlayerAt(newPlayerChoice - 1).getPrice());
                                        cout << endl << "You chose " << getPlayerAt(newPlayerChoice - 1).getName() << endl       // calculating new budget and printing chosen player
                                            << "Your budget is now $" << getBudget() << endl;
                                        user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), yourPlayerChoice - 1);       // setting player to team
                                    }
                                    else
                                    {
                                        cout << "Player is already on your team. Please choose a different number." << endl;    // error if player is already in user's team
                                        newPlayerChoice = 0;
                                    }
                                }
                                else
                                {
                                    cout << endl << "Invalid input. Please retry." << endl;        // not valid option number chosen
                                    newPlayerChoice = 0;
                                }
                            }
                        }
                    }
                break;
            case 2: buyChoice = 0;                                          // buying a player
                    continueBuy = "Y";
                    while (continueBuy == "y" || continueBuy == "Y")        // do they want to continue buying
                    {
                        added = false;
                        buyChoice = 0;
                        newPlayerChoice = 0;
                        cout << endl << "Which postion do you want to buy for? (-1 to cancel)" << endl;
                        bool availablePos[11];
                        for (int p = 0; p < 11; p++)                
                        {
                            availablePos[p] = false;
                        }
                        bool gBuy = false, dBuy = false, mBuy = false, fBuy = false;
                        for (int i = 0; i < 11; i++)                                    // figuring out what position has an available player slot
                        {
                            if (user.getTeamPlayerAt(i).getName() == "")        // empty player
                            {
                                availablePos[i] = true;
                            }
                            if (availablePos[i])        // where is the empty player
                            {
                                if (i == 0 && !gBuy)
                                {
                                    cout << "1 - goalkeeper" << endl;       // goalkeeper can be bought
                                    gBuy = true;
                                }
                                else if (i > 0 && i < 5 && !dBuy)
                                {
                                    cout << "2 - defender" << endl;         // defender can be bought
                                    dBuy = true;
                                }
                                else if (i > 4 && i < 8 && !mBuy)
                                {
                                    cout << "3 - midfielder" << endl;       // mid can be bought
                                    mBuy = true;
                                }
                                else if (i > 7 && i < 11 && !fBuy)
                                {
                                    cout << "4 - forward" << endl;          // forward can be bought
                                    fBuy = true;
                                }
                            }
                        }
                        
                        if (gBuy || dBuy || mBuy || fBuy)           // were there any positions available
                        {
                            while (buyChoice == 0)
                            {
                                cin >> buyChoice;           // which position do they want to buy for
                                switch (buyChoice)
                                {
                                    case -1: leave = true;          // if they want to cancel
                                            continueBuy = "n";
                                        break;
                                    case 1: if (gBuy)
                                            {
                                                min = 75;           // ranges for specific positions
                                                max = 85;
                                                buyingA = "g";
                                            }
                                            else
                                            {
                                                cout << "Invalid input." << endl;
                                                buyChoice = 0;
                                            }
                                        break;
                                    case 2: if (dBuy)
                                            {
                                            min = 50;
                                            max = 75;
                                            buyingA = "d";
                                            }
                                            else
                                            {
                                                cout << "Invalid input." << endl;
                                                buyChoice = 0;
                                            }
                                        break;
                                    case 3: if (mBuy)
                                            {
                                            min = 25;
                                            max = 50;
                                            buyingA = "m";
                                            }
                                            else
                                            {
                                                cout << "Invalid input." << endl;
                                                buyChoice = 0;
                                            }
                                        break;
                                    case 4: if (fBuy)
                                            {
                                            min = 0;
                                            max = 25;
                                            buyingA = "f";
                                            }
                                            else
                                            {
                                                cout << "Invalid input." << endl;
                                                buyChoice = 0;
                                            }
                                        break;
                                    default: cout << "Invalid input." << endl;
                                            buyChoice = 0;
                                        break;
                                }
                            }

                            if (!leave)
                            {
                                printAllPlayers(buyChoice);
                                while (newPlayerChoice == 0)
                                {
                                    cout << endl << "Choose a new player (enter - 1 to cancel):" << endl;
                                    cin >> newPlayerChoice;
                                    if (newPlayerChoice == -1)                  // did the user want to cancel buy
                                    {
                                        leave = true;
                                        break;
                                    }
                                    if (allPlayers[newPlayerChoice - 1].getPrice() > getBudget())
                                    {
                                        cout << "This player is outside of your budget." << endl;       // checking if player is within budget
                                        newPlayerChoice = 0;
                                    }
                                    else if (newPlayerChoice > min && newPlayerChoice <= max)            // is the number a valid option for current position
                                    {
                                        if (buyingA == "g")
                                        {
                                            user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), 0);      // setting player to goalkeeper position if buying 
                                        }
                                        else 
                                        {
                                            for (int b = 0; b < 11; b++)                // checking where to put new player based on position
                                            {                                           // and what type of player the user is buying
                                                if (availablePos[b] && !added)
                                                {
                                                    if (b > 0 && b < 5 && buyingA == "d")
                                                    {
                                                        user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), b);
                                                        posHold = b;
                                                        added = true;
                                                    }
                                                    else if (b > 4 && b < 8 && buyingA == "m")
                                                    {
                                                        user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), b);
                                                        posHold = b;
                                                        added = true;
                                                    }
                                                    else if (b > 7 && b < 11 && buyingA == "f")
                                                    {
                                                        user.setTeamPlayerAt(getPlayerAt(newPlayerChoice - 1), b);
                                                        posHold = b;
                                                        added = true;
                                                    }
                                                }
                                            }
                                        }
                                        
                                        if (user.getTeamPlayerAt(posHold).getName() == getPlayerAt(newPlayerChoice - 1).getName())  // was the player set to the team                                          // checking if player was added
                                        {
                                            setBudget(getBudget() - getPlayerAt(newPlayerChoice - 1).getPrice());
                                            cout << endl << "You chose " << getPlayerAt(newPlayerChoice - 1).getName() << endl       // calculating new budget and printing chosen player
                                                << "Your budget is now $" << getBudget() << endl;
                                        }
                                        else
                                        {
                                            cout << "Player is already on your team. Please choose a different number." << endl;    // error if player is already in user's team
                                            newPlayerChoice = 0;
                                        }
                                    }
                                    else
                                    {
                                        cout << endl << "Invalid input. Please retry." << endl;        // not valid option number chosen
                                        newPlayerChoice = 0;
                                    }
                                }

                                cout << endl << "Would you like to buy another player? (Y/N)" << endl;      // do they want to continue buying players
                                cin >> continueBuy;
                            }
                        }
                        else
                        {
                            cout << endl << "You have no available space in your team. Please sell or trade a player before buying a new one." << endl;     // already have full team
                            continueBuy = "n";
                        }
                    }
                // check which positions can be filled befoere displaying options of what position to buy for
                break;
            case 3: yourPlayerChoice = 0;                   // sell a player
                    cout << endl << "Choose which player of yours you wish to sell:" << endl;       // displaying players on manager's team
                        for (int i = 0; i < 11; i++)
                        {
                            cout << i + 1 << " - " << user.getTeamPlayerAt(i).getName() << endl;
                        }
                    while (yourPlayerChoice == 0)
                    {
                        cout << endl << "Choose a player to sell (enter -1 to cancel):" << endl;        // same deal as first part of trade
                        cin >> yourPlayerChoice;
                        if (yourPlayerChoice == -1)
                        {
                            leave = true;
                            break;
                        }
                        else if (yourPlayerChoice > 0 && yourPlayerChoice <= 11)
                        {
                            cout << endl << "You removed " << user.getTeamPlayerAt(yourPlayerChoice - 1).getName() << " from your team." << endl;       // removing player
                            setBudget(getBudget() + user.getTeamPlayerAt(yourPlayerChoice - 1).getPrice());
                            user.setTeamPlayerAt(Player(), yourPlayerChoice - 1);       // setting index where player was to empty player
                        }
                        else 
                        {
                            cout << endl << "Invalid input." << endl;
                            yourPlayerChoice = 0;
                        }
                    }
                break;
            case 4: do      // changing team name
                    {
                        cout << endl;
                        displayTeamNames();
                        cout << endl << "Choose your new team name (enter -1 to cancel):" << endl;      // asking what new team name they want
                        cin >> newTeamChoice;

                        if (newTeamChoice == -1)
                        {
                            leave = true;
                            break;
                        }
                        else if (newTeamChoice > 0 && newTeamChoice <= arrTeamNSize)
                        {
                            user.setTeamName(arrTeamNames[newTeamChoice - 1]);                  // setting new name to manager's team
                            cout << endl << "Your new team name is: " << user.getTeamName() << endl;
                        }
                        else
                        {
                            cout << endl << "Invalid input." << endl;
                            newTeamChoice = 0;
                        }
                    } while (newTeamChoice == 0);
                break;
            case 5: cout << endl << "Your current budget is $" << getBudget() << endl << endl;      // printing budget
                break;
            case 6: for (int i = 0; i < 11; i++)                // exiting transfer window
                    {
                        if (user.getTeamPlayerAt(i).getName() == "")
                        {
                            cout << endl << "You do not have a full squad. Please choose to buy a player." << endl;     // ensuring that team has 11 players
                            tWChoice = 0;
                            break;
                        }
                    }
                    if (tWChoice == 6)
                    {
                        fullResetAfterSeason();     // reset season data
                        runSeason();                // run next season
                    }
                break;
            default: cout << endl << "Invalid input." << endl;
                break;
        }
    } while (tWChoice != 6);

    /* 1.) display menu of options (trade, buy, sell, view budget)
     * 2.) print out respective player availability for option chosen
     * 3.) take in user choice of player
     * 4.) either add or remove or swap player with team member of manager
     * 5.) compute new budget if necessary
     * 6.) repeat until budget < any price of available player or user quits
    */
} 
void Simulation::runGame(int gameNum)                  // simulate a game for the manager's team
{
    srand(time(NULL));                      // random seed for numbers
    int yourScore = 0, oppScore = 0;
    int managerScoreProb = user.calcScoreProb() + (12 - user.getRank()) + (user.getRetirement() / 2);        // getting manager probability of scoring
    int oppScoreProb = 100 - (10 + (12 - arrTeams[gameNum].getTeamRank()));     // opposition probability of scoring
    // (100 -) -> used to make an upper range to differ from manager probability
    // (10 +) -> mimic the score probability that is based off of players (base level)
    // (12 -) -> lowest rank - actual (closer to rank 1 leads to more score probability)

    arrSeason[gameNum - 1].setYourName(user.getTeamName());     // setting up game object 
    string oppName = arrTeams[gameNum].getTeamName();           // capturing opposition name
    arrTeams[0].setPlayedAt(gameNum, true);                     // changing what teams play eachother
    arrTeams[gameNum].setPlayedAt(0,true);
    arrSeason[gameNum - 1].setOppName(oppName);

    cout << endl << "For game " << gameNum << " you will be playing " << arrSeason[gameNum - 1].getOppName() << " who is ranked #" << arrTeams[gameNum].getTeamRank() << endl;
    cout << "And the game is underway! Who will come out on top?" << endl << endl;
    for (int t = 0; t <= 90; t++)           // looping 90 times to simulate 90 minutes
    {
        if (t == 0 || arrSeason[gameNum - 1].getYourScore() < yourScore || arrSeason[gameNum - 1].getOppScore() < oppScore)     // checking if a game was scored in teh previous minute
        {
            if (arrSeason[gameNum - 1].getYourScore() < yourScore)          // checking if manager's team scored
            {
                // randomly choose a mid or forward to score from team array in manager object
                int randomPlayer = (rand() % (11 - 5 + 1)) + 4;
                // print out time of goal and who scored
                cout << "Your team scored! " << user.getTeamPlayerAt(randomPlayer).getName() 
                    << " put the ball in the back of the net after " << t << " minutes." << endl;
                arrSeason[gameNum - 1].setYourScore(yourScore);
                cout << "The score is now " << arrSeason[gameNum - 1].getYourScore() << " to " << arrSeason[gameNum - 1].getOppScore() << endl;

                if (yourScore > oppScore)               // comparing to opponent score to see who is winning
                {
                    cout << "Your team is winning!" << endl << endl; 
                }
                else if (yourScore < oppScore)
                {
                    cout << "Your team is falling behind!" << endl << endl;
                }
                else
                {
                    cout << "The game is tied! It's a close one." << endl << endl;
                }  
            }
            if (arrSeason[gameNum - 1].getOppScore() < oppScore)    // checking if the opponent scored
            {
                cout << "Dang! " << oppName << " scored an amazing goal after " << t << " minutes." << endl;        // printing that the other team scored and the time
                arrSeason[gameNum - 1].setOppScore(oppScore);
                cout << "The score is now " << arrSeason[gameNum - 1].getYourScore() << " to " << arrSeason[gameNum - 1].getOppScore() << endl;

                if (yourScore > oppScore)           // comparing to your score to update who is winning
                {
                    cout << "Your team is winning!" << endl << endl; 
                }
                else if (yourScore < oppScore)
                {
                    cout << "Your team is falling behind!" << endl << endl;
                }
                else
                {
                    cout << "The game is tied! It's a close one." << endl << endl;
                }  
            }
        } 

        // formulating the probability of each team scoring
        int chanceOfScore = rand() % 100 + 1;       // chance of goal occuring
        int actuallyCount = rand() % 4;             // only 25% of goals count to lower number of goals per game
        if (chanceOfScore > managerScoreProb && chanceOfScore < oppScoreProb)       // between the two ranges for manager goal and opponent goal
        {
            // do nothing
        }
        else if (chanceOfScore <= managerScoreProb)     // if the random number is in the manager score probability range
        {
            if (actuallyCount == 0)         // does it count based on other random number
            {
                yourScore++;
            }
        }
        else if (chanceOfScore >= oppScoreProb)     // does the opponent score (within its range)
        {
            if (actuallyCount == 0)         // does it count
            {
                oppScore++;
            }
        }
    }
    arrTeams[0].setGoalsFor(arrTeams[0].getGoalsFor() + yourScore);                 // updating goals for and goals against for both teams
    arrTeams[0].setGoalsAgainst(arrTeams[0].getGoalsAgainst() + oppScore);
    arrTeams[gameNum].setGoalsFor(arrTeams[gameNum].getGoalsFor() + oppScore);
    arrTeams[gameNum].setGoalsAgainst(arrTeams[gameNum].getGoalsAgainst() + yourScore);
    cout << "The game has ended! The final score is " << yourScore << " - " << oppScore << endl;        // printing final score

    if (yourScore > oppScore)                       // checking who won 
    {
        arrSeason[gameNum - 1].setResult("win");
        cout << "You won! Congrajulations!" << endl;
        arrTeams[gameNum].addLoss();                    // updating win loss or tie for both teams
        arrTeams[0].addWin();
    }
    else if (yourScore < oppScore)
    {
        arrSeason[gameNum - 1].setResult("loss");
        cout << "You lost. Better luck next game!" << endl;
        arrTeams[gameNum].addWin();
        arrTeams[0].addLoss();
    }
    else
    {
        arrSeason[gameNum - 1].setResult("tie");
        cout << "Wow it was a tie! Close game!" << endl;
        arrTeams[gameNum].addTie();
        arrTeams[0].addTie();
    }
    user.addToRecord(arrSeason[gameNum - 1].getResult());       // adding game to record for user

    int randomScores[arrTeamSize];
    for (int i = 1; i < arrTeamSize; i++)                   // simulating random number of goals for remaining teams
    {
        int randomGoals = (rand() % 7 - 2 + 1) + 2;
        if (i != gameNum)
        {
            randomScores[i] = randomGoals;
        }
    }

    Game otherGames[(arrTeamSize / 2) - 1];     // initiating an array of other games that are played (not user's team)
    int otherGameNumber = 0;
    bool alreadyPlaying[arrTeamSize];
    for (int a = 0; a < arrTeamSize; a++)       // setting each index to false 
    {
        alreadyPlaying[a] = false;
    }
    alreadyPlaying[0] = true;                   // except the user's team index and the index of the team the user played
    alreadyPlaying[gameNum] = true;
    int loops = gameNum;                        // variable used to change the index that is trying to be matched to a team
    for (int j = 1; j < arrTeamSize; j++)
    {
        if (!alreadyPlaying[j])             // checking if the team at j has played already
        {           
            if (j + loops < arrTeamSize)    // making sure the team to be matched with is within array
            {
                if (!alreadyPlaying[j + loops])     // checking if matched team has played already
                {
                    if (!arrTeams[j].getPlayedAt(arrTeams[j + loops].getTeamIndex()) && !arrTeams[j + loops].getPlayedAt(arrTeams[j].getTeamIndex()))   // checking if the two teams have played each other before
                    {
                        
                        arrTeams[j].setPlayedAt(arrTeams[j + loops].getTeamIndex(), true);      // setting that that two teams have now played each other / currently playing
                        arrTeams[j + loops].setPlayedAt(arrTeams[j].getTeamIndex(), true);
                        alreadyPlaying[j] = true;
                        alreadyPlaying[j + loops] = true;

                        arrTeams[j].setGoalsAgainst(arrTeams[j].getGoalsAgainst() + randomScores[j + loops]);           // setting their goals for a goals against respectively
                        arrTeams[j + loops].setGoalsAgainst(arrTeams[j + loops].getGoalsAgainst() + randomScores[j]);   // based on the randomly assigned number of goals
                        arrTeams[j].setGoalsFor(arrTeams[j].getGoalsFor() + randomScores[j]);
                        arrTeams[j + loops].setGoalsFor(arrTeams[j + loops].getGoalsFor() + randomScores[j + loops]);

                        if (randomScores[j] > randomScores[j + loops])      // checking which team had the higher number of goals
                        {
                            arrTeams[j].addWin();                   // adding win loss or tie depending on scores
                            arrTeams[j + loops].addLoss();
                        }
                        else if (randomScores[j] < randomScores[j + loops])
                        {
                            arrTeams[j].addLoss();
                            arrTeams[j + loops].addWin();
                        }
                        else
                        {
                            arrTeams[j].addTie();
                            arrTeams[j + loops].addTie();
                        }  

                        otherGames[otherGameNumber].setYourName(arrTeams[j].getTeamName());         // updating game info for array
                        otherGames[otherGameNumber].setOppName(arrTeams[j + loops].getTeamName());
                        otherGames[otherGameNumber].setYourScore(randomScores[j]);
                        otherGames[otherGameNumber].setOppScore(randomScores[j + loops]);
                        otherGameNumber++;      // incrementing to next game index
                    }
                }
            }
            else
            {
                if (loops == arrTeamSize)       // if the matched team is outside of array range we reset the loop
                {
                    loops = 1;                  // and change the incrementation between the teams being matched
                }
                else
                {
                    loops++;
                }
                j = 0;
            }
        }
    }
    updateRankings();           // update the leaderboard
    
    int postGameChoice = 0;
    do 
    {
        cout << endl << "============  Post Game Options  ============" << endl     // ask user what they want to do after game
            << "1 - view leaderboard" << endl
            << "2 - view other games for this week" << endl
            << "3 - view Manager Information" << endl
            << "4 - continue to next game" << endl;
        cin >> postGameChoice;
        switch (postGameChoice)
        {
            case 1: printLeaderBoard(updateRankings());         // print out leaderboard to terminal
                break;
            case 2: displayOtherGames(otherGames, (arrTeamSize / 2) - 1);   // view the other game scores for the week
                break;
            case 3: printManagerInfo();         // print their updated manager info
                break;
            case 4: // do nothing           // continue to next game
                break;
            default: cout << endl << "Invalid input." << endl;
                break;
        }
    } while (postGameChoice != 4);

    /* 1.) display opponent and start screen
     * 2.) loop through probabilities of teams scoring 90 times
     * 3.) probability is based on rank and average player stats
     * 4.) if a team scores display new score and continue through loop
     * 5.) at end display score, who won, and write updated record to file for both teams
     * 6.) simulate scores for other team's games and display them
     *      - asign random value from 0-5 for goals for each team (based on rank)
     *      - for 4 times - asign next available team to play the next team in sequence
     *      - if (team is already playing - go to next team) - once pair is made change the first team to next team in sequence
     *      - if index 9 is reached - reset it to 1
     * 7.) update leaderboard and records in file
    */
}
vector<Team> Simulation::updateRankings()           // update the rankings for all teams 
{
    ofstream leaderboard;                   // file to be written to 
    leaderboard.open("leaderboard.txt");    // opening leaderboard.txt
    vector<Team> rankedTeams;               // creating vector of teams
    Team temp = Team();                     // temp variable to hold a team
    int currentRank = 1;                    // rank being searched for
    for (int i = 0; i < arrTeamSize; i++)   // looping trhough all teams
    {
        if (arrTeams[i].getTeamRank() == currentRank)   // checking if team's rank matches search rank
        {
            rankedTeams.push_back(arrTeams[i]);     // if it does set it to vector (in ranking order from lowest to highest)
            currentRank++;                          // changing rank search
            i = -1;                         // resetting loop so that all teams are searched again
        }
    }

    // sorting algorithm to rank teams based on team elements
    for (int j = 0; j < arrTeamSize; j++)           // looping through all teams
    {
        for (int k = 0; k < arrTeamSize; k++)       // looping through all teams a second time
        {
            if (j != k)         // making sure the sam eteam isn't being checked against itself
            {
                if (rankedTeams[j].getWins() < rankedTeams[k].getWins())        // does the team have more wins 
                {
                    temp = rankedTeams[j];                  // if yes the teams switch places
                    rankedTeams[j] = rankedTeams[k];
                    rankedTeams[k] = temp;
                }
                else if (rankedTeams[j].getWins() == rankedTeams[k].getWins())      // if the teams have same wins check ties
                {
                    if (rankedTeams[j].getTies() < rankedTeams[k].getTies())        // which has more ties
                    {
                        temp = rankedTeams[j];                          // if new team has more ties they swap positions
                        rankedTeams[j] = rankedTeams[k];
                        rankedTeams[k] = temp;
                    }
                    else if (rankedTeams[j].getTies() == rankedTeams[k].getTies())      // if ties are also eqaul go to goals against
                    {
                        if (rankedTeams[j].getGoalsAgainst() > rankedTeams[k].getGoalsAgainst())        // whos has mroe goals against
                        {
                            temp = rankedTeams[j];              // if new team has less goals against they swap
                            rankedTeams[j] = rankedTeams[k];
                            rankedTeams[k] = temp;
                        }
                        else if (rankedTeams[j].getGoalsAgainst() == rankedTeams[k].getGoalsAgainst())      // if goals against are equal check goals for
                        {
                            if (rankedTeams[j].getGoalsFor() < rankedTeams[k].getGoalsFor())        // who has more goals for
                            {
                                temp = rankedTeams[j];              // swap if new team has more goals for
                                rankedTeams[j] = rankedTeams[k];
                                rankedTeams[k] = temp;
                            }
                        } 
                    }
                }
            }
        }
    }

    int rank = 1;
    leaderboard << "<Rank>" << setw(22) << "<team name>" << setw(15) << "<W/L/T>" << setw(16) << "<GA> - <GF>" << endl;       // printing out new rankings to leaderboard.txt
    for (int l = rankedTeams.size() - 1; l >= 0 ; l--)      // since the algorithm sets them from lowest to highest rank - start at end
    {
        leaderboard << setw(2) << rank << "." << setw(25) << rankedTeams[l].getTeamName() << setw(10)        // print rank, name, wins, losses, ties, GA, GF 
            << rankedTeams[l].getWins() << "/" 
            << rankedTeams[l].getLosses() << "/"
            << rankedTeams[l].getTies() << setw(10)
            << rankedTeams[l].getGoalsAgainst() << " - "
            << rankedTeams[l].getGoalsFor() << endl;
        for (int k = 0; k < arrTeamSize; k++)                   // loop through all teams again
        {
            if (arrTeams[k].getTeamName() == rankedTeams[l].getTeamName())      // if names match
            {
                arrTeams[k].setTeamRank(rank);      // set the rank to the rank of team in vector
                if (k == 0)
                {
                    user.setRank(rank);             // if it is user's team update the user's rank too
                }
            }
        }

        rank++;         // increment rank being printed
    }

    return rankedTeams;     // returns vector to be used in printing leaderboard to terminal

    /* 1.) take in vector of teams in ranking order
     * 2.) assing new rank values to each team
     * 3.) write to file that lists the teams in order form top to bottom
     * 4.) continue through simulation
    */
}
void Simulation::printLeaderBoard(vector<Team> teamsVector)        // print leaderboard to terminal
{
    int rank = 1;
    cout << endl << "<Rank>" << setw(22) << "<team name>" << setw(15) << "<W/L/T>" << setw(16) << "<GA> - <GF>" << endl;      // same process as printing to file but to terminal
    for (int i = teamsVector.size() - 1; i >= 0; i--)                   // no need ot update ranks of each team as that has already been done
    {
        cout << setw(2) << rank << "." << setw(25) << teamsVector[i].getTeamName() << setw(10)
            << teamsVector[i].getWins() << "/" 
            << teamsVector[i].getLosses() << "/"
            << teamsVector[i].getTies() << setw(10)
            << teamsVector[i].getGoalsAgainst() << " - "
            << teamsVector[i].getGoalsFor() << endl;

        rank++;
    }
}
void Simulation::displayOtherGames(Game games[], int numGames)       // print out the scores of the other games
{
    cout << endl;
    for (int g = 0; g < numGames; g++)              // loop through all played games for the week 
    {
        cout << games[g].getYourName() << " vs " << games[g].getOppName() << endl;                  // names of teams
        cout << "Score: " << games[g].getYourScore() << " - " << games[g].getOppScore() << endl;    // score of game

        if (games[g].getYourScore() > games[g].getOppScore())       // which team won?
        {    
            cout << games[g].getYourName() << " won." << endl << endl;          // printing that team 1 won
        }
        else if (games[g].getYourScore() < games[g].getOppScore())
        {
            cout << games[g].getOppName() << " won." << endl << endl;           // printing that team 2 won
        }
        else
        {
            cout << "The teams tied." << endl << endl;                          // saying that the teams tied if scores are equal
        }
    }
}
void Simulation::managerRetires(Manager u)             // retirement of manager - end of game
{
    cout << endl << "Congrats on your retirement after " << user.getRetirement() << " years of managing, " << user.getName() << endl;
    printManagerInfo();
}
void Simulation::fullResetAfterSeason()            // resetting all data members back to original before next season
{
    for (int i = 0; i < arrTeamSize; i++)
    {
        arrTeams[i] = Team();
    }
    for (int j = 0; j < seasonS; j++)
    {
        arrSeason[j] = Game();
    }
}