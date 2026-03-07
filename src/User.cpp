#include <string>

#include "User.h"

User::User(string newName)
{
    Name = newName;
}

string User::GetName() const
{
    if (Name == "Emily")
    {
        if (rand() % 11 <= 2)
        {
            return "Ahria";
        }
    }
    else if (Name == "Ahria")
    {
        if (rand() % 11 <= 2)
        {
            return "Emily";
        }
    }

    return Name;
}

void User::AddPoints(int newPoints)
{
    Points += newPoints;
}

int User::GetPoints() const
{
    return Points;
}