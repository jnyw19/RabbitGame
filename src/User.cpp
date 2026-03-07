#include <string>

#include "User.h"

User::User(string newName)
{
    Name = newName;

    // Birthday surprise

    if (Name == "Emily" || Name == "Ahria")
    {
        time_t now = time(nullptr);
        tm *local = localtime(&now);

        if (local->tm_mon == 2 && local->tm_mday == 9)
        {
            IsBirthday = true;
        }
    }
}

string User::GetName() const
{
    if (Name == "Emily")
    {
        if (rand() % 11 <= 2)
        {
            return IsBirthday ? "Birthday Bunnia" : "Ahria";
        }

        return IsBirthday ? "Birthday Bunnily" : Name;
    }
    else if (Name == "Ahria")
    {
        if (rand() % 11 <= 2)
        {
            return IsBirthday ? "Birthday Bunnily" : "Emily";
        }

        return IsBirthday ? "Birthday Bunnia" : Name;
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