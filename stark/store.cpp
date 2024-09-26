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

void Store::Add(std::string key, std::string stringValue)
{
    Pair pair;
    pair.value = stringValue;
    pair.key = key;
    pair.type = PairType::String;
    pairs.push_back(pair);
}

void Store::PrintToFile(const std::string& fileName)
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

    std::string outputString = output.str();
    std::fstream outfile(fileName, std::ios::out);
    outfile << outputString;
}

void Store::ReadFromFile(const std::string& fileName)
{
    std::ifstream infile(fileName);
    if (!infile.is_open())
    {
        std::cerr << "Could not open file for reading: " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        // Remove any leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Skip empty lines and comments (assuming comments start with #)
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // Find the position of the '=' sign
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos)
        {
            continue; // Ignore lines without '='
        }

        // Extract key and value
        std::string key = line.substr(0, equalPos);
        std::string valueStr = line.substr(equalPos + 1);

        // Remove any leading/trailing whitespace from key and value
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);

        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        // Determine the type of the value and store in the pairs vector
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
        // Otherwise, assume it's a string
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

        // Add to the pairs vector
        pairs.push_back(pair);
    }

    infile.close();
}


}
