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

        Rabbit(int id, string name) {
            Id = id;
            Name = name;

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
}

/*=== Endpoint ===*/

int main() {
    const vector<Rabbit> allRabbits = LoadRabbitsFromFile(DATA_FILE_NAME);
    return 0;
}