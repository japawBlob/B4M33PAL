#include <iostream>
#include <vector>

struct smuggler {
    std::vector<struct smuggler> neighours;
};



std::vector<struct smuggler> smugglers;

int numberOfSmugglers, numberOfConnections, packSize, numberOfConnectionsInPack;

int main(){

    scanf("%i %i %i %i", &numberOfSmugglers, &numberOfConnections, &packSize, &numberOfConnectionsInPack);

    

    for (int i = 0; i < numberOfConnections; ++i) {
        int smug1, smug2;
        scanf("%i %i", &smug1, &smug2);

    }

    return 0;
}