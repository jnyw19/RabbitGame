#include "Rabbit.h"

const vector<char> WORD_VOWELS = {'a', 'e', 'i', 'o', 'u'};
const vector<char> CENSOR_BANNED = {' ', '-'};

Rabbit::Rabbit(int newId, string newName)
{
    Id = newId;
    Name = newName;

    CalculateValue();

    //_debugLog("Creating new rabbit " + Name + ", id: " + to_string(Id));
    //_debugLog("\tpoint value: " + to_string(Value));
    //_debugLog("\tcensor test: " + GetCensored());
};

int Rabbit::GetId() const
{
    return Id;
}

int Rabbit::GetValue() const
{
    return Value;
}

void Rabbit::CalculateValue()
{
    int newValue = 0;

    /* Point Scheme

    1 point per space, hyphen, apostrophe
    2 points per 3 alphanumeric characters

    */

    int numAlpha = 0;
    for (int idx = 0; idx < Name.length(); idx++)
    {
        char check = Name[idx];

        switch (check)
        {
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

string Rabbit::GetCensored() const
{
    string nameCopy = Name;

    int numCensored = 0;
    for (int idx = 0; idx < nameCopy.length(); idx++)
    {
        char nameChar = nameCopy[idx];

        if (count(CENSOR_BANNED.begin(), CENSOR_BANNED.end(), nameChar) >= 1)
        {
            continue;
        }

        for (int idy = 0; idy < WORD_VOWELS.size(); idy++)
        {
            char vowelChar = WORD_VOWELS.at(idy);

            if (nameChar == vowelChar)
            {
                numCensored += 1;
                nameCopy.replace(idx, 1, "-");
            }
        }

        if ((rand() % 11) <= 1)
        {
            numCensored += 1;
            nameCopy.replace(idx, 1, "-");
        }
    }

    // Failsafe for getting no other censorship
    if (numCensored == 0)
    {
        nameCopy.replace(0, 2, "-");
    }

    return nameCopy;
}

struct RabbitRecordEntry
{
    Rabbit RabbitData;
    bool CorrectGuess;
};