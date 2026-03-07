#ifndef USER_H
#define USER_H

#include <ctime>
#include <string>

using std::string;

class User {
    private:
        string Name;

        int Points = 0;
        //vector<RabbitRecordEntry> RabbitRecord;
    public:
        bool IsBirthday = false;
        
        string GetName() const;

        int GetPoints() const;
        void AddPoints(int newPoints);

        User(string newName);
};

#endif