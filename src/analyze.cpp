#include <iostream>

#include <vector>
#include <fstream>

using namespace std;

const string DATA_FILE_NAME = "./data/rabbits.txt";
const string AVERAGE_FILE_NAME = "./data/average.txt";

int main() {
    ifstream dataFile(DATA_FILE_NAME);
    vector<string> rabbits;

    if (!dataFile) {
        cout << "Failed to load rabbit data file" << endl;
        exit(1);
    }

    string newLine;
    while (getline(dataFile, newLine)) {
        rabbits.push_back(newLine);
    }

    dataFile.close();
    int totalChars = 0;

    string longestName = rabbits[0];
    string shortestName = rabbits[0];

    for (int idx = 0; idx < rabbits.size(); idx++) {
        string name = rabbits[idx];
        totalChars += name.length();

        if (name.length() > longestName.length()) {
            longestName = name;
        } else if (name.length() < shortestName.length()) {
            shortestName = name;
        }
    }

    int averageSize = totalChars / rabbits.size();

    cout << "-=- Rabbit Stats -=-" << endl;
    cout << "* There are " + to_string(rabbits.size()) + " entries" << endl;
    cout << "* With an average length of " + to_string(averageSize) + " characters" << endl;
    cout << "* Longest: " + longestName << endl;
    cout << "* Shortest: " + shortestName << endl;

    cout << "\nWriting entries with length <=" + to_string(averageSize) + " to file..." << endl;

    ofstream averageFile(AVERAGE_FILE_NAME);

    if (!averageFile) {
        cout << "Error writing average file" << endl;
        exit(1);
    }

    for (int idx = 0; idx < rabbits.size(); idx++) {
        string name = rabbits[idx];

        if (name.length() <= averageSize) {
            averageFile << name;

            if (idx != rabbits.size() - 1) {
                averageFile << endl;
            }
        }
    }

    averageFile.close();

    return 0;
}