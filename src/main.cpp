#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const bool DEBUG_LOG = true;
const string DATA_FILE_NAME = "./data/rabbits.txt";

/*=== Utility Functions ===*/

void _debugLog(string message) {
    cout << message << endl;
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

        Rabbit(int newId, string newName) {
            Id = newId;
            Name = newName;

            CalculateValue();

            _debugLog("Creating new rabbit " + Name + ", id: " + to_string(Id));
            _debugLog("\tpoint value: " + to_string(Value));
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
        vector<RabbitRecordEntry> RabbitRecord;
    public:
        string GetName();

        User(string newName) {
            Name = newName;
        }
};

string User::GetName() {
    return Name; // TODO: When RNG is implemented, check if name is Emily or Ahria and swap
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

    return allRabbits;
}

/*=== Standard Game Mode ===*/

void StandardGame(User* user, const vector<Rabbit>* allRabbits) {
    // TODO: Blank the screen
    cout << "Hi i'm still " << user->GetName() << " btw" << endl;
}

/*=== Endpoint ===*/

int main() {
    vector<Rabbit> allRabbits = LoadRabbitsFromFile(DATA_FILE_NAME);

    string userName;
    int gameMode;

    cout << "\t\t*=* Welcome to the Rabbit Game!!! *=*" << endl;
    cout << "\nPlease enter your name before we begin: ";

    getline(cin, userName);
    User user(userName);

    cout << "\n\t\t-*- What game mode would you like to play, " << user.GetName() << "? -*-" << endl;
    cout << "\n0. The Nothing Game (exit the program)" << endl;
    cout << "1. Standard (Guess-And-Match)" << endl;

    cout << "\nI would like to play mode: ";
    cin >> gameMode;

    switch (gameMode) {
        case 1:
            StandardGame(&user, &allRabbits);
            break;
        
        case 0:
        default:
            exit(0);
            break;
    }

    return 0;
}