#include <iostream>

#include <ctime>
#include <cstdlib>

#include <ranges>
#include <vector>
#include <fstream>

#include "User.h"
#include "Rabbit.h"

using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */

#define GAME_VERSION    "0.1.2"

const bool DEBUG_LOG = false;
const bool SKIP_INTRO = false;

const string DATA_FILE_NAME = "./data/rabbits.txt";
const string AVERAGE_FILE_NAME = "./data/average.txt";

const int MODE_STANDARD_ROUNDS = 5;
const int MODE_STANDARD_RABBITS = 4;

const int DAY_SECONDS = 60 * 60 * 24;

/*=== Utility Functions ===*/

void _debugLog(string message) {
    if (DEBUG_LOG) {
        cout << message << endl;
    }
}

int GetCurrentDay() {
    return time(nullptr) / DAY_SECONDS;
}

/*=== Main Functions ===*/

vector<Rabbit> LoadRabbitsFromFile(string fileName) {
    _debugLog("Loading rabbits from file " + fileName);
    ifstream rabbitFile(fileName);

    if (!rabbitFile) {
        cout << "Failed to load rabbit data! Sorry, this means no game :(" << endl;
        exit(1);
    }

    vector<Rabbit> allRabbits;

    int rabbitId = 0;
    string rabbitName;

    while (getline(rabbitFile, rabbitName)) {
        Rabbit newRabbit(rabbitId, rabbitName);

        rabbitId += 1;
        allRabbits.push_back(newRabbit);
    }

    rabbitFile.close();
    return allRabbits;
}

/*=== Standard Game Mode ===*/

void StandardGame(User* user) {
    system("clear");
    vector<Rabbit> allRabbits = LoadRabbitsFromFile(DATA_FILE_NAME);

    cout << "\t\t=-*-= Standard Mode =-*-=" << endl;
    cout << "Welcome to the standard gamemode, " << user->GetName() << "!" << endl;

    cout << "\n" << "Are you ready to play? (y/n)" << endl;

    char startChoice;
    cin >> startChoice;

    if (startChoice != 'y') {
        exit(0);
    }

    system("clear");

    // Game start

    int currentRound = 0;
    int possiblePoints = 0;

    while (currentRound < MODE_STANDARD_ROUNDS) {
        int pointsToAdd = 0;
        vector<Rabbit> roundRabbits;

        cout << "\n\n\t-*- Round " << currentRound + 1 << " -*-" << endl << endl;

        for (int idx = 0; idx < MODE_STANDARD_RABBITS; idx++) {
            int rabbitIdx = rand() % allRabbits.size();
            Rabbit newRabbit = allRabbits.at(rabbitIdx);

            roundRabbits.push_back(newRabbit);
            allRabbits.erase(allRabbits.begin() + rabbitIdx);

            string rabbitGuess = "";

            cout << "Rabbit " << idx + 1 << ": " << newRabbit.GetCensored() << endl;
            cout << "Rabbit " << idx + 1 << " Guess: ";

            getline(cin, rabbitGuess);
            //cout << endl; 

            if (rabbitGuess == "") {
                getline(cin, rabbitGuess);
            }

            if (rabbitGuess == newRabbit.Name) {
                cout << "Correct!";
                pointsToAdd += newRabbit.GetValue();
            } else {
                cout << "Incorrect!";
            }

            possiblePoints += newRabbit.GetValue();

            string rabbitWord = "Rabbit";
            string descriptorWord = "a";

            if (newRabbit.Name == "Emily") {
                rabbitWord = "Bunny";
                descriptorWord = "an";
            }

            cout << " This is " + descriptorWord + " " << newRabbit.Name + " " + rabbitWord << endl;
            cout << endl;
            
        }

        user->AddPoints(pointsToAdd);

        cout << "You earned " + to_string(pointsToAdd) + " points that round!" << endl;
        cout << "You have earned a total of " + to_string(user->GetPoints()) + " points out of " + to_string(possiblePoints) + " possible." << endl;

        currentRound += 1;
    }
}

/*=== Bunny Wordle Game Mode ===*/

void WordleGame(User* user) {
    system("clear");
    vector<Rabbit> allRabbits = LoadRabbitsFromFile(AVERAGE_FILE_NAME);

    int currentDay = GetCurrentDay();

    cout << "\t\t=-*-= Bundle Mode (IN-DEV) =-*-=" << endl;
    cout << "Welcome to the Bunny Worlde gamemode, " << user->GetName() << "!" << endl;

    cout << "\nToday is Day " + to_string(currentDay) << endl;
}

/*=== Endpoint ===*/

int main() {
    srand(time(0));

    string userName;
    int gameMode;

    cout << "\t\t*=* Welcome to the Rabbit Game!!! *=*" << endl;
    
    cout << "\nYou are playing Version " << GAME_VERSION << endl;
    cout << "Please enter your name before we begin: ";

    getline(cin, userName);
    User user(userName);

    cout << "\n\t\t-*- What game mode would you like to play, " << user.GetName() << "? -*-" << endl;
    cout << "\n0. The Nothing Game (exit the program)" << endl;
    cout << "1. Standard (Guesssing Game)" << endl;
    //cout << "2. Bundle (Bunny Wordle)" << endl;

    cout << "\nI would like to play mode: ";
    cin >> gameMode;

    cout << endl << endl;

    switch (gameMode) {
        case 1:
            StandardGame(&user);
            break;
        case 2:
            WordleGame(&user);
            break;
        
        case 0:
        default:
            exit(0);
            break;
    }

    cout << "Thank you for playing!!! I loaf you <3" << endl;
    return 0;
}