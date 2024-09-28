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
    void Add(std::string key, const char* stringValue);
    void Add(std::string key, const Store& store);

    template<typename T>
    T Get(const std::string& key)
    {
        // Check if the key contains a nested store delimiter
        size_t dotPos = key.find('.');
        if (dotPos != std::string::npos)
        {
            // Extract the store name and the sub-key
            std::string storeName = key.substr(0, dotPos);
            std::string subKey = key.substr(dotPos + 1);

            // Find the nested store by its name
            auto it = std::find_if(stores.begin(), stores.end(),
                [&storeName](const Store& store) { return store.name == storeName; });

            if (it != stores.end())
            {
                // Recursively call Get on the nested store with the sub-key
                return it->template Get<T>(subKey);
            }
        }
        else
        {
            // Search for the key in the current store's pairs
            Pair hackPair;
            hackPair.key = key;

            auto it = std::find(pairs.begin(), pairs.end(), hackPair);
            if (it != pairs.end())
            {
                // Return the value as the requested type
                return std::get<T>(it->value);
            }
        }

        // Return a default value if not found
        return T();
    }

    // Function to get a nested store by its name
    Store* GetStore(const std::string& storeName)
    {
        auto it = std::find_if(stores.begin(), stores.end(),
            [&storeName](const Store& store) { return store.name == storeName; });

        if (it != stores.end())
        {
            return &(*it);
        }

        return nullptr; // Return nullptr if the store is not found
    }

    std::string PrintToFile(const std::string& fileName);
    void ReadFromFile(const std::string& fileName);

    std::string name = "";
private:
    std::vector<Pair> pairs;
    std::vector<Store> stores;
};

}
