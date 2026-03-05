#include <iostream>

#include <ctime>
#include <cstdlib>

#include <ranges>
#include <vector>
#include <fstream>

using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */

const bool DEBUG_LOG = false;
const bool SKIP_INTRO = false;

const string DATA_FILE_NAME = "./data/rabbits.txt";

const vector<char> WORD_VOWELS = {'a', 'e', 'i', 'o', 'u'};
const vector<char> CENSOR_BANNED = {' ', '-'};

const int MODE_STANDARD_DELAY = 3;
const int MODE_STANDARD_ROUNDS = 5;
const int MODE_STANDARD_RABBITS = 4;

/*=== Utility Functions ===*/

void _debugLog(string message) {
    if (DEBUG_LOG) {
        cout << message << endl;
    }
}

/*=== Rabbit Class ===*/

class Rabbit {
    private:
        int Id;
        int Value;

        void CalculateValue();
    public:
        string Name;

        int GetId();
        int GetValue();

        string GetCensored(bool realCensor = false);

        Rabbit(int newId, string newName) {
            Id = newId;
            Name = newName;

            CalculateValue();

            _debugLog("Creating new rabbit " + Name + ", id: " + to_string(Id));
            _debugLog("\tpoint value: " + to_string(Value));
            _debugLog("\tcensor test: " + GetCensored());
        };
};

int Rabbit::GetId() {
    return Id;
}

int Rabbit::GetValue() {
    return Value;
}

void Rabbit::CalculateValue() {
    int newValue = 0;

    /* Point Scheme

    1 point per space, hyphen, apostrophe
    2 points per 3 alphanumeric characters
    
    */

    int numAlpha = 0;
    for (int idx = 0; idx < Name.length(); idx++) {
        char check = Name[idx];
        
        switch(check) {
            case ' ':
            case '-':
            case '\'':
                newValue += 1;
                break;
            default:
                numAlpha += 1;
                break;
        }
    }

    newValue += (numAlpha / 3);

    Value = newValue;
}

string Rabbit::GetCensored(bool realCensor) {
    string nameCopy = Name;

    for (int idx = 0; idx < nameCopy.length(); idx++) {
        char nameChar = nameCopy[idx];

        if (count(CENSOR_BANNED.begin(), CENSOR_BANNED.end(), nameChar) >= 1) {
            continue;
        }

        for (int idy = 0; idy < WORD_VOWELS.size(); idy++) {
            char vowelChar = WORD_VOWELS.at(idy);

            if (nameChar == vowelChar) {
                nameCopy.replace(idx, 1, "-");
            }
        }

        if ((rand() % 11) <= 1) {
            nameCopy.replace(idx, 1, "-");
        }
    }

    if (realCensor) {
        Value *= 2;
        Name = nameCopy;
    }

    return nameCopy;
}

struct RabbitRecordEntry {
    Rabbit RabbitData;
    bool CorrectGuess;
};

/*=== User Class  ===*/

class User {
    private:
        string Name;
        bool NameSwap = false;

        int Points = 0;
        //vector<RabbitRecordEntry> RabbitRecord;
    public:
        string GetName();

        int GetPoints();
        void AddPoints(int newPoints);

        User(string newName) {
            Name = newName;
        }
};

string User::GetName() {
    if (Name == "Emily") {
        if (rand() % 11 <= 2) {
            return "Ahria";
        }
    } else if (Name == "Ahria") {
        if (rand() % 11 <= 2) {
            return "Emily";
        }
    }

    return Name;
}

void User::AddPoints(int newPoints) {
    Points += newPoints;
}

int User::GetPoints() {
    return Points;
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
    
}

/*=== Endpoint ===*/

int main() {
    srand(time(0));

    string userName;
    int gameMode;

    cout << "\t\t*=* Welcome to the Rabbit Game!!! *=*" << endl;
    cout << "\nPlease enter your name before we begin: ";

    getline(cin, userName);
    User user(userName);

    cout << "\n\t\t-*- What game mode would you like to play, " << user.GetName() << "? -*-" << endl;
    cout << "\n0. The Nothing Game (exit the program)" << endl;
    cout << "1. Standard (Guesssing Game)" << endl;
    cout << "2. Bundle (Bunny Wordle)" << endl;

    cout << "\nI would like to play mode: ";
    cin >> gameMode;

    cout << endl << endl;

    switch (gameMode) {
        case 1:
            StandardGame(&user);
            break;
        
        case 0:
        default:
            exit(0);
            break;
    }

    cout << "Thank you for playing!!! I loaf you <3" << endl;
    return 0;
}