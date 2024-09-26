#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <variant>

namespace stk
{

enum PairType
{
    Integer, Float, String, Boolean
};

struct Pair
{
    std::string key;
 
    std::variant<bool, int, float, std::string> value;

    PairType type;

    bool operator==(const Pair& other) const
    {
        if (key == other.key)
        {
            return true;
        }
        return false;
    }
};

class Store
{
public:
    Store();

    void Add(std::string key, bool boolValue);
    void Add(std::string key, int intValue);
    void Add(std::string key, float floatValue);
    void Add(std::string key, std::string stringValue);

    template<typename T>
    T Get(std::string key)
    {
        Pair hackPair;
        hackPair.key = key;

        auto it = std::find(pairs.begin(), pairs.end(), hackPair);
        if (it != pairs.end()) {
            int pairIndex = std::distance(pairs.begin(), it);
            return std::get<T>(pairs[pairIndex].value);
        }

        return T();
    }

    void PrintToFile(const std::string& fileName);
    void ReadFromFile(const std::string& fileName);
private:
    std::vector<Pair> pairs;
};

}
