#include "store.h"
#include <fstream>
#include <sstream>

namespace stk
{

Store::Store()
{}

void Store::Add(std::string key, bool boolValue)
{
    Pair pair;
    pair.value = boolValue;
    pair.key = key;
    pair.type = PairType::Boolean;
    pairs.push_back(pair);
}

void Store::Add(std::string key, int intValue)
{
    Pair pair;
    pair.value = intValue;
    pair.key = key;
    pair.type = PairType::Integer;
    pairs.push_back(pair);
}

void Store::Add(std::string key, float floatValue)
{
    Pair pair;
    pair.value = floatValue;
    pair.key = key;
    pair.type = PairType::Float;
    pairs.push_back(pair);
}

void Store::Add(std::string key, const char* stringValue)
{
    Pair pair;
    pair.value = stringValue;
    pair.key = key;
    pair.type = PairType::String;
    pairs.push_back(pair);
}

void Store::Add(std::string key, const Store& store)
{
    Store newStore = store;
    newStore.name = key;
    stores.push_back(newStore);
}

std::string Store::PrintToFile(const std::string& fileName)
{
    std::stringstream output;

    for (Pair pair : pairs)
    {
        if (pair.type == PairType::Integer)
        {
            output << pair.key << " = " << std::to_string(std::get<int>(pair.value)) << "\n";
        }else if (pair.type == PairType::String)
        {
            output << pair.key << " = '" << std::get<std::string>(pair.value) << "'\n";
        }else if (pair.type == PairType::Float)
        {
            output << pair.key << " = " << std::to_string(std::get<float>(pair.value)) << "\n";
        }else if (pair.type == PairType::Boolean)
        {
            bool bol = std::get<bool>(pair.value);
            if (bol)
            {
                output << pair.key << " = " << "True" << "\n";
            }else
            {
                output << pair.key << " = " << "False" << "\n";
            }
        }
    }

    for (Store store : stores)
    {
        output << "\n";
        output << "[" << store.name << "]\n";
        output << store.PrintToFile(fileName);
    }

    std::string outputString = output.str();
    std::fstream outfile(fileName, std::ios::out);
    outfile << outputString;
    return outputString;
}

std::string Trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void Store::ReadFromFile(const std::string& fileName)
{
    std::ifstream infile(fileName);
    if (!infile.is_open())
    {
        std::cerr << "Could not open file for reading: " << fileName << std::endl;
        return;
    }

    Store* currentStore = this;     std::string line;

    while (std::getline(infile, line))
    {
        line = Trim(line); 

        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        if (line[0] == '[' && line.back() == ']')
        {
            std::string sectionName = line.substr(1, line.size() - 2);
            sectionName = Trim(sectionName);

            auto it = std::find_if(stores.begin(), stores.end(), [&sectionName](const Store& s)
            {
                return s.name == sectionName;
            });

            if (it == stores.end())
            {
                Store newStore;
                newStore.name = sectionName;
                stores.push_back(newStore);
                currentStore = &stores.back();             
            }
            else
            {
                currentStore = &(*it); 
            }

            continue;
        }

        // Split the line into key and value
        size_t equalPos = line.find('=');
        if (equalPos 
        }

        std::string key = Trim(line.substr(0, equalPos));
        std::string valueStr = Trim(line.substr(equalPos + 1));

        Pair pair;
        pair.key = key;

        // Check if it's a boolean
        if (valueStr == "True" || valueStr == "False")
        {
            pair.type = PairType::Boolean;
            pair.value = (valueStr == "True");
        }
        // Check if it's an integer
        else if (valueStr.find_first_not_of("0123456789-") == std::string::npos)
        {
            pair.type = PairType::Integer;
            pair.value = std::stoi(valueStr);
        }
        // Check if it's a float
        else if (valueStr.find_first_not_of("0123456789.-") == std::string::npos && valueStr.find('.') != std::string::npos)
        {
            pair.type = PairType::Float;
            pair.value = std::stof(valueStr);
        }
        else
        {
            // Remove single quotes around strings if they exist
            if (valueStr.size() > 1 && valueStr.front() == '\'' && valueStr.back() == '\'')
            {
                valueStr = valueStr.substr(1, valueStr.size() - 2);
            }
            pair.type = PairType::String;
            pair.value = valueStr;
        }

        currentStore->pairs.push_back(pair);
    }

    infile.close();
}

}
