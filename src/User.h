#ifndef USER_H
#define USER_H

#include <string>

using std::string;

class User {
    private:
        string Name;
        bool NameSwap = false;

        int Points = 0;
        //vector<RabbitRecordEntry> RabbitRecord;
    public:
        string GetName() const;

        int GetPoints() const;
        void AddPoints(int newPoints);

        User(string newName);
};

#endif