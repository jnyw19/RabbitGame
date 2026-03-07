#ifndef RABBIT_H
#define RABBIT_H

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Rabbit {
    private:
        int Id;
        int Value;

        void CalculateValue();
    public:
        string Name;

        int GetId() const;
        int GetValue() const;

        string GetCensored() const;

        Rabbit(int newId, string newName);
};

#endif