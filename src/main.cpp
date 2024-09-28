#include <iostream>
#include "../stark/stark.h"

int main(int argc, char** argv)
{
    stk::Store store;
    store.Add("myAge", 20);
    store.Add("meStandinOnBenis", true);
    store.Add("myName", "Quandle dingle");
    store.Add("LightSpeed", 23.10595f);

    stk::Store childStore;
    childStore.Add("string", "bruh");
    childStore.Add("INTEGER", 251);

    stk::Store nextChildStore;
    nextChildStore.Add("newstring", "OH CMON");
    nextChildStore.Add("SpeedOfSound", 251.1312f);

    store.Add("child", childStore);
    store.Add("nextChild", nextChildStore);

    store.PrintToFile("quandle.stk");

    stk::Store newStore;
    newStore.ReadFromFile("quandle.stk");
    std::cout << "Retrieved child store string: " << newStore.Get<std::string>("child.string") << std::endl;
    
    return 0;
}
