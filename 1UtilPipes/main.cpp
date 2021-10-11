#include <iostream>
#include <vector>

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

int main(int argc, char const *argv[])
{
	int numberOfFarms, numberOfPipes;
	std::cout << "Hello this is my first PAL Program\n";
	scanf("%i %i", &numberOfFarms, &numberOfPipes);

	//struct farm farms [numberOfFarms];

	/*map.reserve(numberOfFarms);
	for (std::vector<int> line : map){
		line.reserve(numberOfFarms);
	}*/

	//int map [numberOfFarms][numberOfFarms];

	// !!!!!!! farms.assign(numberOfFarms, static_cast<struct farm>(0));
	map.assign(numberOfFarms, std::vector<int> (numberOfFarms, 0));

	for (int i = 0; i < numberOfPipes; i++){
		int from, to, cost;
		scanf("%i %i %i", &from, &to, &cost);
		//std::cin << temp1 << temp2 << temp3;
		map[from][to] = cost;
		map[to][from] = cost;
	}
	int numberOfHubs;
	scanf("%i", &numberOfHubs);

	for (int i = 0; i < numberOfFarms; ++i){
		farms[i].distToHub = 99999999;
		farms[i].isConnected = false;

	}

	for(int i = 0; i < numberOfHubs; i++){
		int temp1;
		scanf("%i", &temp1);
		farms[temp1].distToHub = 0;
	}

	//"DRONI KOKOTE"






	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << farms[i].distToHub << " ";
	}
	std::cout << "\n";




	std::cout << "  ";
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < numberOfFarms; ++i){
		std::cout << i << " ";
		for (int j = 0; j < numberOfFarms; ++j){
			std::cout << map[i][j] << " ";
		}
		std::cout << "\n";

	}
	

	return 0;
}