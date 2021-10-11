#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
//int map [numberOfFarms][numberOfFarms];

std::vector<std::vector<int>> map;


struct farm {
	int distToHub;
	int homeHub;
	int name;
	bool isConnected;
	std::vector<int> neighbours;
};

std::vector<struct farm> farms;

int disconnectedFarms = 0;

void printMap();
void printNeighbours(int name);

int main(int argc, char const *argv[]) {
    int numberOfFarms, numberOfPipes;
    std::cout << "Hello this is my first PAL Program\n";
    scanf("%i %i", &numberOfFarms, &numberOfPipes);

    //struct farm farms [numberOfFarms];

    /*map.reserve(numberOfFarms);
    for (std::vector<int> line : map){
        line.reserve(numberOfFarms);
    }*/

    //int map [numberOfFarms][numberOfFarms];
    farms.reserve(numberOfFarms);
    struct farm temp_farm = {99999, -1, -1, false};
    for (int i = 0; i < numberOfFarms; ++i) {
        temp_farm.name = i;
        farms.push_back(temp_farm);
    }

    map.assign(numberOfFarms, std::vector<int>(numberOfFarms, 0));

    for (int i = 0; i < numberOfPipes; i++) {
        int from, to, cost;
        scanf("%i %i %i", &from, &to, &cost);
        //std::cin << temp1 << temp2 << temp3;
        map[from][to] = cost;
        map[to][from] = cost;
        farms[from].neighbours.push_back(to);
        farms[to].neighbours.push_back(from);
    }
    int numberOfHubs;
    scanf("%i", &numberOfHubs);
    std::vector<int> hubs;
    for (int i = 0; i < numberOfHubs; i++) {
        int newHub;
        scanf("%i", &newHub);
        farms[newHub].distToHub = 0;
        farms[newHub].homeHub = newHub;
        farms[newHub].isConnected = true;
        hubs.push_back(newHub);
    }
    /*for (int i = 0; i < numberOfHubs; ++i) {
        std::cout << hubs[i] << " " ;
    }
    std::cout << "\n";

    for (int i = 0; i < numberOfFarms; ++i) {
        std::cout << farms[i].distToHub << " ";
    }
    std::cout << "\n";*/

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> prioQueue;
    for(int currentHub : hubs){
        prioQueue.push(std::make_pair(farms[currentHub].distToHub, currentHub));
        //printNeighbours(hubs[currentHub]);
        while (!prioQueue.empty()) {
            auto currentFarm = prioQueue.top();
            prioQueue.pop();
            //std::cout << "pop " << currentNode.first << " " << currentNode.second << "\n";
            for (int neighbour: farms[currentFarm.second].neighbours) {
                if (farms[neighbour].distToHub > currentFarm.first + map[neighbour][currentFarm.second]) {
                    /*if (farms[neighbour].homeHub == -2) {
                        disconnectedFarms--;
                    }*/
                    farms[neighbour].homeHub = currentHub;
                    farms[neighbour].isConnected = true;
                    farms[neighbour].distToHub = currentFarm.first + map[neighbour][currentFarm.second];
                    prioQueue.push(std::make_pair(farms[neighbour].distToHub, neighbour));
                    continue;
                }
                if (farms[neighbour].distToHub == currentFarm.first + map[neighbour][currentFarm.second]) {
                    /*if (farms[neighbour].homeHub != -2) {
                        disconnectedFarms++;
                    }*/
                    farms[neighbour].homeHub = -2;
                    farms[neighbour].isConnected = false;
                    prioQueue.push(std::make_pair(farms[neighbour].distToHub, neighbour));
                }
            }
        }
    }
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << std::setw(2) << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << std::setw(2) << farms[i].distToHub << " ";
	}
    std::cout << "\n";
    for (int i = 0; i < numberOfFarms; ++i){
        std::cout << std::setw(2) << farms[i].homeHub << " ";
    }
	std::cout << "\n";
    std::cout << disconnectedFarms << "\n";
    int numberOfDisconections = 0;
    for(struct farm farmm : farms){
        if(farmm.homeHub == -2){
            numberOfDisconections++;
        }
    }
    std::cout << numberOfDisconections << "\n";


/*
	printMap();
	
	printNeighbours(5);
	printNeighbours(6);
	printNeighbours(19);
	printNeighbours(14);
*/

	return 0;
}

void printNeighbours(int name){
	std::cout << "Hello my name is " << name << " and my neighbours are:\n";
	for (int neighbour : farms[name].neighbours){
		std::cout << "neighbour\'s name: " << neighbour << " | distance: " << map[name][neighbour] << "\n";
	}
}

void printMap(){
	std::cout << "   ";
	int numberOfFarms = map.size();
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << std::setw(2) << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << std::setw(2) << i << " ";
		for (int j = 0; j < numberOfFarms; ++j){
			std::cout << std::setw(2) << map[i][j] << " ";
		}
		std::cout << "\n";

	}
}