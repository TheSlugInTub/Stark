#include <iostream>
#include <stark.h>

int main(int argc, char** argv)
{
    stk::Store store;
    store.Add("myAge", 20);
    std::string name = "Quandle dingle";
    store.Add("meStandinOnBenis", true);
    store.Add("myName", name);
    store.Add("LightSpeed", 23.10595f);

    store.PrintToFile("quandle.stk");

    stk::Store newStore;
    newStore.ReadFromFile("quandle.stk");
    std::string newName = newStore.Get<std::string>("myName");
    std::cout << "Read from file: " << newName << std::endl;

    return 0;
}
